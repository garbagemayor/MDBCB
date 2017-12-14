#ifndef BASE_INDEX_H_
#define BASE_INDEX_H_

#include "../../filesystem/OneFileManager.h"
#include "../../tablesystem/TableManager.h"

/*
 *  �������ࡣ
 *  һ������������һ���ļ����档
 */
class BaseIndex {
    
public:
    enum IndexType {
        baseIndex = 0,
        treeIndex = 1,
        hashIndex = 2,
    };
    
protected:
    //������Ӧ�ı������
    TableManager * tableManager;
    //�����ļ��ĵ��ļ�������
    OneFileManager * oneFileManager;
    //��������
    IndexType indexType;
    

public:
    //���캯��
    IndexBase(TableManager * tableManager_, char * colName) {
        tableManager = tableManager_;
        indexType = IndexType.baseIndex;
        static char fileName[256];
        sprintf(fileName, "%s__%s.ind", table->getName(), colName);
        oneFileManager = new OneFileManager(tableManager->bpm, fileName);
    }
};

#endif // BASE_INDEX_H_
