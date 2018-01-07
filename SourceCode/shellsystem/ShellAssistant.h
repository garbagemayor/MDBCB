#ifndef SHELL_ASSISTANT_H_
#define SHELL_ASSISTANT_H_

#include "ShellClass.h"
#include "ShellLexerAssistant.h"

/**
 *  ����ʱ��Ҫ�����ݣ�д�����������������Զ�������������
 */
class RunningData {
    
public:
    //����ҳ������
    BufPageManager * bufPageManager;
    //�����ﾳ�����ݿ�
    TableManager * database;
    //�����ﾳ������������ݱ�����Ҫ����
    Table * table;
    //�״����б�ǣ���������">>>"
    bool firstRoundFlag;
    
    RunningData() {
        bufPageManager = NULL;
        database = NULL;
        table = NULL;
        firstRoundFlag = true;
    }
    ~RunningData() {
        if (database != NULL) {
            delete database;
            database = NULL;
        }
        if (bufPageManager != NULL) {
            delete bufPageManager;
            bufPageManager = NULL;
        }
    }
};

/**
 *  ��Ҫ�ĺ���
 */
RunningData cur;

/*
 *  ɾ�����ļ��У������������е��ļ����ļ��У����������·��Ҳ�����Ǿ���·��
 */
int removeDir(const char*  dirPath) {
    struct _finddata_t fb;
    char path[256 + 4];
    strcpy(path, dirPath);
    strcat(path, "/*");
    int handle = _findfirst(path, &fb);
    if (handle != 0) {
        while (0 == _findnext(handle, &fb)) {
            int noFile = strcmp(fb.name, "..");
            if (0 != noFile) {
                memset(path, 0, sizeof(path));
                strcpy(path, dirPath);
                strcat(path, "/");
                strcat(path, fb.name);
                if (fb.attrib == 16) {
                    removeDir(path);
                } else {
                    remove(path);
                }
            }
        }
        _findclose(handle);
    }
    return rmdir(dirPath);
}

/*
 *  ��ȡ����������SQL�����е�����
 */
std::string getTypeNameInSQL(TableDataType type) {
    std::string typeName;
    switch (type) {
    case TableDataType::t_bool:
        typeName = "BOOL";
        break;
    case TableDataType::t_char:
        typeName = "CHAR";
        break;
    case TableDataType::t_short:
        typeName = "SHORT";
        break;
    case TableDataType::t_int:
        typeName = "INT";
        break;
    case TableDataType::t_long:
        typeName = "LONG";
        break;
    case TableDataType::t_float:
        typeName = "FLOAT";
        break;
    case TableDataType::t_double:
        typeName = "DOUBLE";
        break;
    case TableDataType::t_string:
        typeName = "VARCHAR";
        break;
    case TableDataType::t_lob:
        typeName = "LOB";
        break;
    default:
        typeName = "ERROR";
    }
    return typeName;
}

/*
 *  ����ǰ���SQL���ȷ�������ݱ�
 */
void loadCurTable(std::string * tbName) {
    //���û�д����ݿ⣬����
    if (cur.database == NULL) {
        std::cout << "Parser.INSERT INTO: error" << std::endl;
        std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
    } else if (!cur.database -> hasOpenedTable(* tbName)) {
        //���û��������ݱ�����
        std::cout << "Parser.INSERT INTO: error" << std::endl;
        std::cout << "û�����ݱ�:" << * tbName << std::endl;
    } else {
        //��ǰSQL������������ݱ�
        cur.table = cur.database -> getTableByName(* tbName);
    }
}

/*
 *  ���ķ�������������ת��Ϊ���ݱ��е������У�����ת���ͷ���NULL
 */
TableRow * genTableRow(UnionValueList * sqlRow, Table * table, std::string & errorMessage) {
    std::stringstream ssbuf;
    TableHeader * tableHeader = table -> getTableHeader();
    /*
    std::cout << "genTableRow(...) {" << std::endl;
    std::cout << "    tableHeader = {" << std::endl;
    std::cout << "        name = " << tableHeader -> getName() << std::endl;
    std::cout << "        nCol = " << tableHeader -> getNCol() << std::endl;
    std::cout << "        nRow = " << tableHeader -> getNRow() << std::endl;
    for (int i = 0; i < tableHeader -> getNCol(); i ++) {
    std::cout << "        columnList[" << i << "] = {" << std::endl;
    std::cout << "            name = " << tableHeader -> getColumnById(i) -> getName() << std::endl;
    std::cout << "            type = " << tableHeader -> getColumnById(i) -> getDataType() << std::endl;
    std::cout << "            length = " << tableHeader -> getColumnById(i) -> getDataLength() << std::endl;
    std::cout << "        }" << std::endl;
    }
    std::cout << "    }" << std::endl;
    std::cout << "}" << std::endl;
    */
    //�����һ�е����ݸ�����
    if ((int) sqlRow -> size() != tableHeader -> getNCol()) {
        ssbuf << "��ȡ��" << (int) sqlRow -> size() << "�����ݣ������õ�" << tableHeader -> getNCol() << "��";
        ssbuf >> errorMessage;
        return NULL;
    }
    TableRow * tableRow = new TableRow(tableHeader);
    IndexManager * indexManager = table -> getIndexManager();
    for (int i = 0; i < tableHeader -> getNCol(); i ++) {
        //�����һ����������ͺ�NULL���
        UnionValue * sqlValue = sqlRow -> at(i);
        TableColumn * tableColumn = tableHeader -> getColumnById(i);
        TableGrid * tableGrid = tableRow -> getGridById(i);
        TableDataType superType = getSuperType(tableColumn -> getDataType());
        int typeLen = getDataTypeLength(tableColumn -> getDataType());
        if (sqlValue -> ty == 0) {
            //SQL����NULL
            if (!tableColumn -> allowNull()) {
                ssbuf << "����ĵ�" << i << "�����ݸ�" << "������ΪNULLֵ";
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            tableGrid -> setNull();
        } else if (sqlValue -> ty == 1) {
            //SQL����UINT64
            if (superType != TableDataType::t_long &&
                superType != TableDataType::t_double) {
                ssbuf << "����ĵ�" << i << "�����ݸ�" << "���������Ͳ����ݣ�";
                ssbuf << "��ȡ��" << "UINT64" << "�޷�ת��Ϊ" << getTypeNameInSQL(tableColumn -> getDataType());
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            tableGrid -> setDataValueNumber(sqlValue -> dt.u, typeLen);
        } else if (sqlValue -> ty == 2) {
            //SQL����DOUBLE
            if (superType != TableDataType::t_double) {
                ssbuf << "����ĵ�" << i << "�����ݸ�" << "���������Ͳ����ݣ�";
                ssbuf << "��ȡ��" << "DOUBLE" << "�޷�ת��Ϊ" << getTypeNameInSQL(tableColumn -> getDataType());
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            std::cout << "sqlValue -> dt.d = " << sqlValue -> dt.d << std::endl;
            tableGrid -> setDataValueFloat(sqlValue -> dt.d, typeLen);
        } else if (sqlValue -> ty == 3) {
            //SQL����STRING
            if (superType != TableDataType::t_string) {
                ssbuf << "����ĵ�" << i << "�����ݸ�" << "���������Ͳ����ݣ�";
                ssbuf << "��ȡ��" << "VARCHAR" << "�޷�ת��Ϊ" << getTypeNameInSQL(tableColumn -> getDataType());
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            std::string * s = sqlValue -> dt.s;
            tableGrid -> setDataValueArray((ByteBufType) s -> c_str(), s -> length());
        }
        //���ݲ������ظ����м��
        if (tableColumn -> isUnique()) {
            if (tableColumn -> hasTreeIndex() ||
                tableColumn -> hasHashIndex()) {
                //B+������
                TreeIndex * treeIndex = (TreeIndex *) indexManager -> getIndexById(i);
                if (treeIndex -> containKey(tableGrid -> getDataValueNumber())) {
                    ssbuf << "����ĵ�" << i << "�����ݸ�" << "�����ݱ����ظ����֣������в������ظ�����";
                    ssbuf >> errorMessage;
                    delete tableRow;
                    return NULL;
                }
            }
            /*
             else if (tableColumn -> hasHashIndex()) {
                //Hash����
                HashIndex * hashIndex = (HashIndex *) indexManager -> getIndexById(i);
                if (hashIndex -> containKey(tableGrid -> getDataPointer(), tableGrid -> getDataLength()) {
                    ssbuf << "����ĵ�" << i "�����ݸ�" << "�����ݱ����ظ����֣������в������ظ�����";
                    ssbuf >> errorMessage;
                    delete tableRow;
                    return NULL;
                }
            }
            */
        }
    }
    return tableRow;
}

bool checkTableNameList(StringList * & tbNameList, UnionWhereClause * whList, std::string & errorMessage) {
    std::stringstream ssbuf;
    //������ݱ��Ƿ����
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        if (!cur.database -> hasOpenedTable(* tbNameList -> at(i))) {
            ssbuf << "��WHERE��������������ݱ�" << * tbNameList -> at(i) << "������";
            ssbuf >> errorMessage;
            return false;
        }
    }
    //ȥ���ظ����ݱ�
    bool errorFlag = false;
    StringList * tbNameList2 = new StringList();
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        std::string * tbName = tbNameList -> at(i);
        int cnt = 0;
        for (int j = 0; j < (int) tbNameList2 -> size(); j ++) {
            if (* tbNameList2 -> at(j) == * tbName) {
                cnt ++;
            }
        }
        if (cnt == 0) {
            tbNameList2 -> push_back(tbName);
        } else {
            if (cnt == 1) {
                ssbuf << * tbNameList -> at(i) << ", ";
            }
            errorFlag = true;
            delete tbNameList -> at(i);
            tbNameList -> at(i) = NULL;
        }
    }
    delete tbNameList;
    tbNameList = tbNameList2;
    if (errorFlag) {
        ssbuf >> errorMessage;
        errorMessage = std::string("��FROM��������ظ������ݱ�:") + errorMessage;
        return false;
    }
    /*
    std::cout << "ʣ�����ݱ�: ";
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        std::cout << * tbNameList -> at(i) << ", ";
    }
    std::cout << std::endl;
    */
    //����õ������ݱ��Ƿ��г�
    for (int j = 0; j < (int) whList -> size(); j ++) {
        /*
        std::cout << "whList[" << j << "] = {";
        std::cout << * whList -> at(j) -> left -> tb << "." << * whList -> at(j) -> left -> col << ", ";
        std::cout << (int) whList -> at(j) -> op << ", " << whList -> at(j) -> ty << ", ";
        if (whList -> at(j) -> ty == 2) {
        std::cout << * whList -> at(j) -> right.uc -> tb << "." << * whList -> at(j) -> right.uc -> col << "}" << std::endl;
        } else {
        std::cout << "continue" << std::endl;
        }
        */
        std::string * tbName = whList -> at(j) -> left -> tb;
        int i;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                break;
            }
        }
        if (i == (int) tbNameList -> size()) {
            ssbuf << "��WHERE�������Ҫ�õ����ݱ�" << * tbName << "����FROM�����δ����";
            ssbuf >> errorMessage;
            return false;
        }
        if (whList -> at(j) -> ty != 2) {
            continue;
        }
        tbName = whList -> at(j) -> right.uc -> tb;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                break;
            }
        }
        if (i == (int) tbNameList -> size()) {
            ssbuf << "��WHERE�������Ҫ�õ����ݱ�" << * tbName << "����FROM�����δ����";
            ssbuf >> errorMessage;
            return false;
        }
    }
    //���û���õ������ݱ�
    if ((int) tbNameList -> size() == 1) {
        return true;
    }
    std::vector < bool > useful;
    useful.resize(tbNameList -> size());
    for (int i = 0; i < (int) useful.size(); i ++) {
        useful[i] = false;
    }
    for (int j = 0; j < (int) whList -> size(); j ++) {
        std::string * tbName = whList -> at(j) -> left -> tb;
        int i;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                useful[i] = true;
                break;
            }
        }
        if (whList -> at(j) -> ty != 2) {
            continue;
        }
        tbName = whList -> at(j) -> right.uc -> tb;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                useful[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        if (useful[i] == false) {
            ssbuf << "��FROM��������������ݱ�" << * tbNameList -> at(i) << "����WHERE�����δʹ��";
            ssbuf >> errorMessage;
            return false;
        }
    }
    return true;
}

bool checkSelector(UnionColList * sColList, StringList * tbNameList, std::string & errorMessage) {
    std::stringstream ssbuf;
    //������ݱ��Ѿ����ֹ�
    //std::cout << "whList -> size() = " << whList -> size() << std::endl;
    for (int i = 0; i < (int) sColList -> size(); i ++) {
        std::string * tbName = sColList -> at(i) -> tb;
        int j;
        for (j = 0; j < (int) tbNameList -> size(); j ++) {
            if (* tbNameList -> at(j) == * tbName) {
                break;
            }
        }
        if (j == (int) tbNameList -> size()) {
            ssbuf << "��SELECT�������Ҫ�õ����ݱ�" << * tbName << "����FROM�����δ����";
            ssbuf >> errorMessage;
            return false;
        }
    }   
    return true;
}

bool cmpUnionValue(UnionValue * uvL, UnionWhereItem::OpTag op, UnionValue * uvR) {
    bool satisfy = false;
    if (uvL -> ty == 0) {
        //�����NULL
        if (uvR -> ty == 0) {
            //�ұ���NULL
            satisfy = (op == UnionWhereItem::OpTag::OP_EQ);
        } else {
            //�ұ������������������ַ���
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    } else if (uvL -> ty == 1) {
        //���������
        uint64 vl = uvL -> dt.u;
        if (uvR -> ty == 1) {
            //�ұ�������
            uint64 vr = uvR -> dt.u;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else if (uvR -> ty == 2) {
            //�ұ��Ǹ�����
            double vr = uvR -> dt.d;
            //std::cout << "vL = " << vl << ", vr = " << vr << std::endl;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else {
            //�ұ���NULL���ַ���
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    } else if (uvL -> ty == 2) {
        //����Ǹ�����
        double vl = uvL -> dt.d;
        if (uvR -> ty == 1) {
            //�ұ�������
            uint64 vr = uvR -> dt.u;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else if (uvR -> ty == 2) {
            //�ұ��Ǹ�����
            double vr = uvR -> dt.d;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else {
            //�ұ���NULL���ַ���
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    } else if (uvL -> ty == 3) {
        //������ַ���
        std::string vl(* uvL -> dt.s);
        if (uvR -> ty == 3) {
            //�ұ�������
            std::string vr(* uvR -> dt.s);
            //std::cout << "vl = '" << vl << "', vr = '" << vr << "'" << std::endl;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else {
            //�ұ���NULL��������������
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    }
    return satisfy;
}

void runSelect(UnionColList * sColList, StringList * tbNameList, UnionWhereClause * whList) {
    int printCnt = 0;
    bool iteFlag = true;
    std::vector < Table * > tbList;
    std::vector < TableIterator * > iteList;
    //��ȡ���ݱ��б�͵���������
    //std::cout << "runSelect() flag 1" << std::endl;
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        std::string * tbName = tbNameList -> at(i);
        Table * table = cur.database -> getTableByName(* tbName);
        tbList.push_back(table);
        iteList.push_back(table -> beginIte());
        if (iteList.back() -> isEnd()) {
            iteFlag = false;
        }
    }
    //std::cout << "runSelect() flag 2" << std::endl;
    //ѭ��ֱ��ȫ��ö�����
    while (iteFlag) {
        //���μ��ÿһ��WHERE����Ƿ�����
        bool satisfy = true;
        int i1;
        for (i1 = 0; i1 < (int) whList -> size() && satisfy; i1 ++) {
            UnionWhereItem * wh = whList -> at(i1);
            //�ҳ���ֵ���������ݱ������ݱ��б�͵�����������ı�ţ������ֵҲ�����ݱ��Ҳ˳���ҳ���
            int iL = 0, iR = 0;
            for (int i = 0; i < (int) tbList.size(); i ++) {
                std::string tbName = tbList[i] -> getName();
                if (tbName == * wh -> left -> tb) {
                    iL = i;
                }
                if (wh -> ty == 2 && tbName == * wh -> right.uc -> tb) {
                    iR = i;
                }
            }
            //��ߵ�UnionValue
            UnionValue uvL;
            TableDataType suL = getSuperType(wh -> left -> tc -> getDataType());
            if (iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> isNull()) {
                //�����NULL
                uvL.ty = 0;
            } else {
                switch (suL) {
                case TableDataType::t_long:
                    //���������
                    uvL.ty = 1;
                    uvL.dt.u = iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataValueNumber();
                    break;
                case TableDataType::t_double:
                    //����Ǹ�����
                    uvL.ty = 2;
                    uvL.dt.d = iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataValueFloat();
                    break;
                case TableDataType::t_string:
                    //������ַ���
                    uvL.ty = 3;
                    ByteBufType dpL = iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataPointer();
                    uvL.dt.s = new std::string((char *) dpL);
                    break;
                }
            }
            //�ұߵ�UnionValue
            UnionValue uvR;
            switch (wh -> ty) {
            case 0:
                //�ұ���NULL
                uvR.ty = 0;
                break;
            case 1:
                //�ұ��ǳ���
                uvR = * wh -> right.uv;
                break;
            case 2:
                //�ұ������ݸ�
                TableDataType suR = getSuperType(wh -> right.uc -> tc -> getDataType());
                if (iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> isNull()) {
                    //�ұ���NULL
                    uvR.ty = 0;
                } else {
                    switch (suR) {
                    case TableDataType::t_long:
                        //�ұ�������
                        uvR.ty = 1;
                        uvR.dt.u = iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataValueNumber();
                        break;
                    case TableDataType::t_double:
                        //�ұ��Ǹ�����
                        uvR.ty = 2;
                        uvR.dt.d = iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataValueFloat();
                        break;
                    case TableDataType::t_string:
                        //�ұ����ַ���
                        uvR.ty = 3;
                        ByteBufType dpR = iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataPointer();
                        uvR.dt.s = new std::string((char *) dpR);
                        break;
                    }
                }
                break;
            }
            //����
            satisfy = satisfy && cmpUnionValue(& uvL, wh -> op, & uvR);
        }
        //��������������Ͱ���SELECT����ӡһ��
        //std::cout << "runSelect() flag 3 satisfy = " << satisfy << std::endl;
        if (satisfy) {
            printCnt ++;
            for (int i = 0; i < (int) sColList -> size(); i ++) {
                UnionCol * uc = sColList -> at(i);
                //�ҵ������ĸ���
                int iT = 0;
                for (int i = 0; i < (int) tbNameList -> size(); i ++) {
                    if (* tbNameList -> at(i) == * uc -> tb) {
                        iT = i;
                        break;
                    }
                }
                //�������Ļ
                //std::cout << "runSelect() flag 3 iT = " << iT << std::endl;
                iteList[iT] -> getTableRow() -> getGridByName(* uc -> col) -> stdCout();
                std::cout << (i < (int) sColList -> size() - 1 ? ", " : ".");
            }
            std::cout << std::endl;
        }
        //ǰ������һ����������
        //std::cout << "runSelect() flag 3-5" << std::endl;
        int i2;
        for (i2 = 0; i2 < (int) iteList.size(); i2 ++) {
            //std::cout << "runSelect() flag 3-5  i2 = " << i2 << std::endl;
            iteList[i2] -> next();
            if (! iteList[i2] -> isEnd()) {
                break;
            }
        }
        //std::cout << "runSelect() flag 4" << std::endl;
        //û����һ����������
        if (i2 == (int) iteList.size()) {
            iteFlag = false;
        } else {
            for (int j = 0; j < i2; j ++) {
                delete iteList[j];
                iteList[j] = tbList[j] -> beginIte();
            }
        }
        //std::cout << "runSelect() flag 5" << std::endl;
        //for (int i = 0; i < (int) iteList.size(); i ++) {
            //std::cout << "    iteList[" << i << "]: pageId = " << iteList[i] -> pageId << ", slotId = " << iteList[i] -> slotId << std::endl;
        //}
    }
    std::cout << "���ҵ�" << printCnt << "�����������ļ�¼" << std::endl;
    for (int i = 0; i < (int) iteList.size(); i ++) {
        delete iteList[i];
    }
}
















#endif // SHELL_ASSISTANT_H_
