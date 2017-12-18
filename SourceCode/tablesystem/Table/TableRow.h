#ifndef TABLE_ROW_H
#define TABLE_ROW_H

#include "../../filesystem/ByteBufBase.h"
#include "TableHeader.h"
#include "TableGrid.h"

#include <string>
#include <vector>

/**
 *  �������࣬���ڴ��д洢һ�е����ݣ��ɵ������ݱ���Table����
 *  ������Զ���޸ģ���Ҫ��¼�Ƿ���
 *  ���ļ��еĴ洢�������¸�ʽ��
 *  �۳���slotLen(2B) ״̬λtagAB(2B) 
 *  �������ִ�СfSize(2B) ������������fNCol(2B) ��������(fsize-4B) NULLλͼ(ceil(fNCol/8)B)
 *  �䳤����vNCol(2B) ƫ������vOffset(vNCol*2B) �䳤����(����B)
 */
class TableRow {
    
public:
    //��ͷ��ʽ
    TableHeader * tableHeader;
    //״̬λflagAB
    int flagAB;
    //��������
    std::vector<TableGrid *> gridList;
    //�Ƿ���
    bool dirtyFlag;
    
public:
    /*
     *  @���캯��
     *  @����tableHeader_:���ݱ�ı�ͷ�������������е��߼���ʽ
     *  ����:����һ����������
     */
    TableRow(TableHeader * tableHeader_) {
        //��ָ�뱨��
        if (tableHeader_ == NULL) {
            std::cout << "TableRow(NULL) error" << std::endl;
            return;
        }
        //��������Ȼ�����޸ı���
        if (tableHeader_ -> isModifiable()) {
            std::cout << "TableRow(...) error" << std::endl;
            tableHeader = NULL;
            return;
        }
        //���ݱ�ͷ�ĸ�ʽ������һ������ȫ��NULL����
        tableHeader = tableHeader_;
        dirtyFlag = true;
        gridList.resize(tableHeader -> getNCol());
        for (int i = 0; i < gridList.size(); i ++) {
            gridList[i] = new TableGrid(tableHeader -> getColumnById(i));
        }
    }
    
    /*
     *  @���캯��
     *  @����tableHeader_:���ݱ�ı�ͷ�������������е��߼���ʽ
     *  @����slotData_:��ͷ�Ĳ����ݣ����ж�ȡ��ͷ
     *  ����:�Ӳ��ж�ȡһ��������
     */
    TableRow(TableHeader * tableHeader_, ByteBufType slotData_) {
        readFromByteBuffer(slotData_);
        dirtyFlag = false;
    }
    
    /*
     *  ��������
     *  ����:�ͷ��ڴ�ռ�ǰ�����������д��
     */
    ~TableRow() {
        writeBackToBuffer();
        if (rowData != NULL) {
            delete rowData;
        }
    }
    
public:
    ///����get����
    
    
    
    
    
    
public:
    ///����set����
    
    
    
    
    
    
    
    
    

public:
    ///��ͨ����
    /*
     *  @������:writeBackToBuffer
     *  ����:������д�ص������������ȥ
     */
    void writeBackToBuffer() {
        //���Ǻϲ�
        for (int i = 0; i < (int) gridList.size(); i ++) {
            if (gridList[i] -> isDirty()) {
                dirtyFlag = true;
                break;
            }
        }
        //���෵��
        if (!dirtyFlag) {
            return;
        }
        //д��
        
        
        
        
        
        
        
        
    }
    
    
public:
    ///��������
    /*
     *  @������:getPossibleSize
     *  @����tableHeader:һ����ͷ��
     *  @����flag:�����0��������С����1���������
     *  ����:���������е����/��С�Ĵ�С��
     */
    static int getPossibleSize(TableHeader * tableHeader, int flag) {
        
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLE_ROW_H
