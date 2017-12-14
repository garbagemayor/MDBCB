#ifndef TABLE_H_
#define TABLE_H_

#include "../../filesystem/OneFileManager.h"
#include "../Page/TablePage.h"
#include "TableHeader.h"

/**
 *  �������ݱ������ݱ������TableManager����
 *  һ�����ݱ��Ӧһ���ļ����� <����> + ".table"������
 *  ������½����ݱ���Ҫ��֤ԭ��û��ͬ�������ݱ�
 *  ���ļ��ĵ�0ҳ���洢��ͷ�Ȼ�����Ϣ���������ݡ�
 */
class Table {
    
public:
    //���ļ�������
    OneFileManager * oneFileManager;
    //��ͷ�ͱ�Ļ�����Ϣ
    TableHeader * tableHeader;
    //����������
    //IndexManager indexManager;
    
public:
    /*
     *  @���캯��
     *  @����bufPageManager_:����ҳ������
     *  @����tableHeader_:�����ݱ�ı�ͷ
     *  ����:�½�һ�����ݱ�Ҫ3�����裺(1)������0ҳ��ҳͷ��ҳ��(2)�½���0ҳ(3)д���ͷ
     */
    Table(BufPageManager * bufPageManager_, TableHeader * tableHeader_) {
        oneFileManager = new OneFileManager(bufPageManager_, (tableHeader_ -> getName() + ".table").c_str());
        tableHeader = tableHeader_;
        //������0ҳ��ҳͷ��ҳ��
        //�½���0ҳ��д��ҳͷҳ��
        TablePage * page0 = new TablePage(oneFileManager);
        //�½��ۣ�д���ͷ;
        page0 -> addSlot(tableHeader -> getSizeInSlot(), tableHeader -> toByteBuffer());
    }
    
    /*
     *  @���캯��
     *  @����bufPageManager_:����ҳ������
     *  @����tableName_:���ݱ������
     *  ����:��һ��ԭ�����ݱ�ֻ��Ҫ��ȡ��0ҳ�ı�ͷ��Ϣ
     */
    Table(BufPageManager * bufPageManager_, std::string tableName_) {
        oneFileManager = new OneFileManager(bufPageManager_, (tableName_ + ".table").c_str());
        TablePage * page0 = new TablePage(oneFileManager, 0);
        tableHeader = new TableHeader(page0 -> getSlot(0));
    }
    
public:
    /*
     *  @������:getName
     *  ����:��ȡ���ݱ�����
     */
    std::string getName() {
        return tableHeader -> getName();
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLE_H_
