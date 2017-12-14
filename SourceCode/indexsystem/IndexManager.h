#ifndef INDEX_MANAGER_H_
#define INDEX_MANAGER_H_

#include <iostream>

#include "../tablesystem/TableManager.h"
#include "IndexTree/IndexTree.h"

/*
 *  �������ࡣ
 *  һ������������һ���ļ����档
 */
class IndexBase {

protected:
    //�ļ����
    int fileId;
    //ҳ��ͳ��
    int pageCount;

    //��
    TableManager * table;
    //����
    char * colName;

public:
    //�鹹�캯��
    virtual IndexBase(TableManager * table_, char * colName_) {
        table = table_;
        colName = colName_;
        //�����ļ�
        static char fileName[256];
        sprintf(fileName, "%s__%s.ind", table->getName(), colName);
        FileManager * fileManager = new FileManager();
        fileManager.createFile(fileName);   //TODO �쳣����
        fileManager.openFile(fileName, fileId); //TODO �쳣����
        pageCount = 0;
    }

};


/*
 *  B+��������
 */
template <typename KeyType>
class IndexTree
    : public IndexBase {
    
protected:
    

protected:
    IndexTree(TableManager * table_, char * colName_)
        : IndexBase(table_, colName_) {
        
        
    }

public:



};




/*
 *  һ����ֻ��һ��������������һ���������������Թ������е�������
 */
class IndexManager {

private:
    //������Եı�
    TableManager * table;
    //��������
    int n;
    //�����б�
    IndexBase * index;

public:



};

#endif // INDEX_MANAGER_H_
