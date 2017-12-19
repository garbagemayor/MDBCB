#ifndef TABLE_H_
#define TABLE_H_

#include "../../filesystem/OneFileManager.h"
#include "../Page/TablePage.h"
#include "../Page/TablePageAssistant.h"
#include "TableHeader.h"
#include "TableRow.h"

/**
 *  �������ݱ������ݱ������TableManager����
 *  һ�����ݱ��Ӧһ���ļ����� <����> + ".table"������
 *  ������½����ݱ���Ҫ��֤ԭ��û��ͬ�������ݱ�
 *  ���ļ��ĵ�0ҳ���洢��ͷ�Ȼ�����Ϣ���������ݡ�
 *  ���˻�����Ϣ֮��ʣ�µĲ��ִ��ÿһҳ�Ŀ����ֽ����������þͿ���ҳ
 */
class Table {
    
private:
    //���ļ�������
    OneFileManager * oneFileManager;
    //��ͷ�ͱ�Ļ�����Ϣ
    TableHeader * tableHeader;
    //��ҳ����
    TablePageAssistant * tablePageAssistant;
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
        //�½���0ҳ��������д���ͷ
        TablePage * page0 = new TablePage(oneFileManager);
        int headerSlotId = page0 -> createSlot(tableHeader -> getSizeInSlot());
        ByteBufType headerSlot = page0 -> getSlot(headerSlotId);
        tableHeader -> writeAsByte(headerSlot);
        delete page0;
        //������ҳ���֣�д������
        tablePageAssistant = new TablePageAssistant(oneFileManager);
        //���������������������С�����Ҫ������ͬ���У�������Щ�д�������
        ///TODO
    }
    
    /*
     *  @���캯��
     *  @����bufPageManager_:����ҳ������
     *  @����tableName_:���ݱ������
     *  ����:��һ��ԭ�����ݱ�ֻ��Ҫ��ȡ��0ҳ�ı�ͷ��Ϣ
     */
    Table(BufPageManager * bufPageManager_, std::string tableName_) {
        oneFileManager = new OneFileManager(bufPageManager_, (tableName_ + ".table").c_str());
        //ȥ��0ҳ��ȡ��ͷ��Ϣ
        TablePage * page0 = new TablePage(oneFileManager, 0);
        tableHeader = new TableHeader(page0 -> getSlot(0));
        delete page0;
        //������ҳ���֣���ȡ����
        tablePageAssistant = new TablePageAssistant(oneFileManager);
        //����������������ȡ��Щ����
        ///TODO
    }
    
    ~Table() {
        delete oneFileManager;
        delete tablePageAssistant
    }
    
public:
    ///����get����
    /*
     *  @������:getOneFileManager
     *  ����:��ȡ���ݱ�ĵ��ļ�������
     */
    OneFileManager * getOneFileManager() {
        return oneFileManager;
    }
    
    /*
     *  @������:getTableHeader
     *  ����:��ȡ���ݱ�ı�ͷ
     */
    TableHeader * getTableHeader() {
        return tableHeader;
    }
    
    /*
     *  @������:getName
     *  ����:��ȡ���ݱ�����
     */
    std::string getName() {
        return tableHeader -> getName();
    }
    
    /*
     *  @������:getNCol
     *  ����:��ȡ���ݱ�����
     */
    int getNCol() {
        return tableHeader -> getNCol();
    }
    
    /*
     *  @������:getNRow
     *  ����:��ȡ���ݱ�����
     */
    int getNRow() {
        return tableHeader -> getNRow();
    }
    
public:
    ///��ͨ����
    /*
     *  @������:addRow
     *  @����tableRow:Ҫ������У����ᱻ����֮����룬���������ﶨ��ľ��������ͷ��ڴ�
     *  @����pageId:���ڷ��ز���λ�õ�ҳ���
     *  @����slotId:���ڷ��ز���λ�õĲ۱��
     *  ����:���һ�����ݣ�ȥÿһҳ������һ���ܼ����λ�ð����ӽ�ȥ
     */
    void addRow(TableRow * tableRow, int & pageId, int & slotId) {
        //��ͷ��ͬ����
        if (!tableHeader -> isEqualTo(tableRow -> getTableHeader())) {
            std::cout << "Table.addRow(...) error" << std::endl;
            return;
        }
        //���в�����NULL��������
        if (!tableRow -> canMeetNullRequirement()) {
            std::cout << "Table.addRow(...) error" << std::endl;
            return;
        }
        //���в��������ݻ�����ͬ��������
        ///TODO
        //�ڱ�ҳ����������һ�����ʵ�ҳ
        int slotLen = tableRow -> getSizeInSlot();
        pageId = tablePageAssistant -> findPageForSlot(slotLen);
        //����һҳ�л�ȡ�۵ı��
        TablePage * page;
        if (pageId < oneFileManager -> getPageCnt()) {
            page = new TablePage(oneFileManager, pageId);   //�����е�ҳ�������
        } else {
            page = new TablePage(oneFileManager);           //���¿���ҳ�������
        }
        //д��ȥ
        slotId = page -> createSlot(slotLen);
        ByteBufType buf = page -> getSlot(slotId);
        tableRow -> writeAsByte(buf);
        //�ı�ҳ����
        tablePageAssistant -> setFreeCnt(pageId, page -> getPageHeader() -> getFreeCnt());
    }
    
    
    
};

#endif // TABLE_H_
