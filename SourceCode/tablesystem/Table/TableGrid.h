#ifndef TABLE_GRID_H
#define TABLE_GRID_H

#include "../../filesystem/ByteBufBase.h"
#include "TableColumn.h"

/**
 *  ���ݸ��࣬���ڴ��д洢һ�����ӵ����ݣ���TableRow������
 *  ������Զ���޸ģ���Ҫ��¼�Ƿ���
 */
class TableGrid {

private:
    //��һ�����ڵ��е���Ϣ
    TableColumn * tableColumn;
    //�Ƿ���NULL
    bool nullFlag;
    //��������ʽ�����ݵĳ���
    int length;
    //��������ʽ�µ���������
    ByteBufType data;
    //�Ƿ���
    bool dirtyFlag;

public:
    /*
     *  @���캯��
     *  @����tableColumn_:�����е���Ϣ
     *  ����:�½�һ���յĸ��ӣ�������NULL
     */
    TableGrid(TableColumn * tableColumn_) {
        //��ָ�뱨��
        if (tableColumn_ == NULL) {
            std::cout << "TableGrid(NULL) error" << std::endl;
            return;
        }
        tableColumn = tableColumn_;
        nullFlag = true;
        length = 0;
        data = NULL;
        dirtyFlag = true;
    }
    
    ~TableGrid() {
        if (dirtyFlag) {
            std::cout << "~TableGrid() error" << std::endl;
        }
        if (data != NULL) {
            delete [] data;
        }
    }

public:
    ///����get����
    /*
     *  @������:getTableColumn
     *  ����:��������Ϣָ��
     */
    TableColumn * getTableColumn() {
        return tableColumn;
    }
    
    /*
     *  @������:isNull
     *  ����:�����Ƿ��ǿ�ֵ
     */
    bool isNull() {
        return nullFlag;
    }
    
    /*
     *  @������:getDataLength
     *  ����:�������ݳ���
     */
    int getDataLength() {
        return length;
    }
    
    /*
     *  @������:getDataPointer
     *  ����:����ָ�����ݸ��ڵ����ݵ�ָ��
     */
    ByteBufType getDataPointer() {
        return data;
    }
    
    /*
     *  @������:isDirty
     *  ����:�����Ƿ���
     */
    bool isDirty() {
        return dirtyFlag;
    }
    
public:
    ///����set����    
    /*
     *  @������:setNull
     *  ����:����ΪNULL�������
     */
    void setNull() {
        dirtyFlag = true;
        nullFlag = true;
    }
    
    /*
     *  @������:setDataValueNumber
     *  @����data_:Ҫд�����ֵ
     *  @����length_:Ҫд����ֵ�ĳ���
     *  ����:����bool, char, short, int, long�Լ���Ӧ��unsigned������lob���͵ĸ��ӵ�ֵ���������
     */
    void setDataValueNumber(uint64 num, int length_) {
        //�������ʹ��󱨴�
        if (tableColumn -> getDataType() != TableDataType::t_bool &&
            tableColumn -> getDataType() != TableDataType::t_char &&
            tableColumn -> getDataType() != TableDataType::t_short &&
            tableColumn -> getDataType() != TableDataType::t_int &&
            tableColumn -> getDataType() != TableDataType::t_long &&
            tableColumn -> getDataType() != TableDataType::t_lob) {
            std::cout << "TableGrid.setDataValueNumber(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        //���ݳ��ȱ���
        if (tableColumn -> getDataLength() != length_) {
            std::cout << "TableGrid.setDataValueNumber(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        dirtyFlag = true;
        nullFlag = false;
        length = length_;
        if (data == NULL ) {
            data = new Byte [length];
        }
        memset(data, 0, sizeof(Byte) * length);
        ByteBufType data_ = data;
        writeNumberToByte(data_, length, num);
    }
    
    /*
     *  @������:setDataValueFloat
     *  @����data_:Ҫд�����ֵ
     *  @����length_:Ҫд����ֵ�ĳ���
     *  ����:����float, double���͵ĸ��ӵ�ֵ���������
     */
    void setDataValueFloat(double num, int length_) {
        //�������ʹ��󱨴�
        if (tableColumn -> getDataType() != TableDataType::t_float &&
            tableColumn -> getDataType() != TableDataType::t_double) {
            std::cout << "TableGrid.setDataValueFloat(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        //���ݳ��ȱ���
        if (tableColumn -> getDataLength() != length_) {
            std::cout << "TableGrid.setDataValueFloat(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        dirtyFlag = true;
        nullFlag = false;
        length = length_;
        if (data == NULL ) {
            data = new Byte [length];
        }
        memset(data, 0, sizeof(Byte) * length);
        ByteBufType data_ = data;
        writeFloatToByte(data_, length, num);
    }
    
    /*
     *  @������:setDataValueArray
     *  ����:����string���ӵ�ֵ�������
     */
    void setDataValueArray(ByteBufType string_, int length_) {
        //�������ʹ��󱨴�
        if (tableColumn -> getDataType() != TableDataType::t_string) {
            std::cout << "TableGrid.setDataValueArray(..., " << length_ << ") error" << std::endl;
            return;
        }
        //���ݳ��ȱ���
        if (length_ < 0 || length >= MAX_STRING_LENGTH) {
            std::cout << "TableGrid.setDataValueArray(..., " << length_ << ") error" << std::endl;
            return;
        }
        dirtyFlag = true;
        nullFlag = false;
        length = length_;
        if (data == NULL ) {
            data = new Byte [MAX_STRING_LENGTH];
        }
        memset(data, 0, sizeof(Byte) * MAX_STRING_LENGTH);
        ByteBufType data_ = data;
        writeArrayToByte(data_, length, string_, length_);
    }
    
public:
    ///��ͨ����
    /*
     *  @������:isEqualTo
     *  ����:�ж�������������������
     *       �ر�ģ����������ӵ������Ͳ�ͬʱ��������false�����������Ӷ���NULLʱ����true��һ����NULL��һ������ʱ����false
     *       lob���ܱȴ�С������
     */
    bool isEqualTo(TableGrid * grid) {
        //���Ͳ�ͬ��LOB���ͱ���
        if (tableColumn -> getDataType() != grid -> tableColumn -> getDataType() ||
            tableColumn -> getDataType() == TableDataType::t_lob) {
            std::cout << "TableGrid.isEqualTo(...) error" << std::endl;
            return false;
        }
        //NULL���
        if (nullFlag && grid -> nullFlag) {
            return true;
        }
        if (nullFlag || grid -> nullFlag) {
            return false;
        }
        //һ�����
        for (int i = 0; i < length; i ++) {
            if (data[i] != grid -> data[i]) {
                return false;
            }
        }
        return true;
    }
    
    /*
     *  @������:isLessThan
     *  ����:�ж��Ƿ�С����һ�������������
     *       �ر�ģ����������ӵ������Ͳ�ͬʱ��������false��NULLС���κ���ֵ����ͬ���͵�����NULL���
     *       bool, char, short, int, long, float, double��ȡ��ֱ�ӱȴ�С��������uint64����������double
     *       string���ֽڴ����ұȴ�С��lob���ܱȴ�С������
     *  ע��:���е������ȴ�С�����޷��űȴ�С���ӵ�һƥ
     */
    bool isLessThan(TableGrid * grid) {
        //���Ͳ�ͬ��LOB���ͱ���
        if (tableColumn -> getDataType() != grid -> tableColumn -> getDataType() ||
            tableColumn -> getDataType() == TableDataType::t_lob) {
            std::cout << "TableGrid.isLessThan(...) error" << std::endl;
            return false;
        }
        //NULL���
        if (nullFlag && grid -> nullFlag) {
            return false;
        }
        if (nullFlag || grid -> nullFlag) {
            return nullFlag;
        }
        //��ȻNULL����
        if (data == NULL || grid -> data == NULL) {
            std::cout << "TableGrid.isLessThan(...) error" << std::endl;
            return false;
        }
        //�������
        if (tableColumn -> getDataType() == TableDataType::t_bool ||
            tableColumn -> getDataType() == TableDataType::t_char ||
            tableColumn -> getDataType() == TableDataType::t_short ||
            tableColumn -> getDataType() == TableDataType::t_int ||
            tableColumn -> getDataType() == TableDataType::t_long) {
            ByteBufType data_;
            uint64 num_1 = readByteToNumber(data_ = data, tableColumn -> getDataLength());
            uint64 num_2 = readByteToNumber(data_ = data, grid -> tableColumn -> getDataLength());
            return num_1 < num_2;
        }
        //���������
        if (tableColumn -> getDataType() == TableDataType::t_float ||
            tableColumn -> getDataType() == TableDataType::t_double) {
            ByteBufType data_;
            double num_1 = readByteToNumber(data_ = data, tableColumn -> getDataLength());
            double num_2 = readByteToNumber(data_ = data, grid -> tableColumn -> getDataLength());
            return num_1 < num_2;
        }
        //�ַ������
        if (tableColumn -> getDataType() == TableDataType::t_string) {
            for (int i = 0; i < length && i < grid -> length; i ++) {
                if (data[i] != grid -> data[i]) {
                    return data[i] < grid -> data[i];
                }
            }
            return false;
        }
    }
    
    /*
     *  @������:isGreaterThan
     *  ����:�ж��Ƿ������һ������������ݣ���ʵ�Ƿ������isLessThan
     */
    void isGreaterThan(TableGrid * grid) {
        return grid -> isLessThan(this);
    }
};

#endif // TABLE_GRID_H