#ifndef ONE_FILE_MANAGER_H_
#define ONE_FILE_MANAGER_H_

#include "fileio/FileManager.h"
#include "bufmanager/BufPageManager.h"
#include "ByteBufBase.h"

#include <string>
#include <map>

/**
 *  ���ļ���������
 *  ԭ�е��ļ��������ͻ���ҳ��������û�м�¼ĳ���ļ���һ���ж���ҳ���Լ�һЩ������Ϣ�������Ҫ��װ��
 *  ����������ʱ�򣬶�ҳ�Ĳ�����ʹ��ҳ��š�
 *  ÿ�ε���bufPageManager��hashȥ��ȡҳ�ڻ������������ı�ŷǳ����������������������΢�Ż���һ�¡�
 */
class OneFileManager {
    
private:
    //�ļ���
    std::string fileName;
    //�ļ����
    int fileId;
    //ҳ��ͳ��
    int pageCnt;
    //����ҳ������
    BufPageManager * bufPageManager;
    
protected:
    //ҳ���ڻ���ҳ����������ı�ţ�Ҫ��hash�����ͬ����Ӻ�ɾ��
    std::map<int, int> indexMap;
    
public:
    /*
     *  @���캯��
     *  ����:����һ�����ļ���������ָ���ļ���
     */
    OneFileManager(BufPageManager * bufPageManager_, std::string fileName_, bool isNewFile = false) {
        fileName = fileName_;
        bufPageManager = bufPageManager_;
        if (isNewFile) {
            bufPageManager -> fileManager -> createFile(fileName.c_str());
            pageCnt = 0;
        } else {
            pageCnt = bufPageManager -> fileManager -> getFileSize(fileName.c_str()) / PAGE_SIZE;
        }
        if (bufPageManager -> fileManager -> openFile(fileName.c_str(), fileId) == false) {
            std::cout << "OneFileManager(bufPageManager, " << fileName_ << ", " << isNewFile << ") error" << std::endl;
            return;
        }
    }
    
    /*
     *  @��������
     *  ����:�Ѵ򿪹���ҳȫ���ص�
     */
    ~OneFileManager() {
        close();
    }
public:
    ///����get����
    /*
     *  @������:getPageCnt
     *  ����:��������ļ���ҳ��
     */
    int getPageCnt() {
        return pageCnt;
    }
    
public:
    ///��ͨ���������ļ��ڵ�ҳ���в����ĺ�����
    /*
     *  @������:getPageCount
     *  ����:��ȡ��ǰ�ļ����ж���ҳ
     */
    int getPageCount() {
        return pageCnt;
    }
    
    /*
     *  @������:getPage
     *  ����:����ҳ��ţ�����ҳ����
     */
    ByteBufType getPage(int pageId) {
        int index;
        BufType data = bufPageManager -> getPage(fileId, pageId, index);
        indexMap[pageId] = index;
        return (ByteBufType) data;
    }
    
    /*
     *  @������:getNewPage
     *  ����:����һ���µ�ҳ������ҳ���ݣ���ͬʱ��ȡҳ���
     */
    ByteBufType getNewPage(int & pageId) {
        pageId = pageCnt;
        pageCnt ++;
        int index;
        BufType data = bufPageManager -> getPage(fileId, pageId, index);
        indexMap[pageId] = index;
        return (ByteBufType) data;
    }
    
    /*
     *  @������getNewPage
     *  ����:����һ���µ�ҳ������ҳ����
     */
    ByteBufType getNewPage() {
        int pageId;
        return getNewPage(pageId);
    }
    
    /*
     *  @������:access
     *  ����:��ҳ��ű��һ��ҳ�����ʹ������滻�㷨������Ҫ�滻��
     */
    void access(int pageId) {
        int index = getPageIndex(pageId, false);
        if (index == -1) {
            std::cout << "OneFileManager.access() error" << std::endl;
            return;
        }
        bufPageManager -> access(index);
    }
    
    /*
     *  @������:markDirty
     *  ����:�����ҳ
     */
    void markDirty(int pageId) {
        int index = getPageIndex(pageId, false);
        if (index == -1) {
            std::cout << "OneFileManager.markDirty() error" << std::endl;
            return;
        }
        bufPageManager -> markDirty(index);
    }
    
    /*
     *  @������:release
     *  ����:��ҳ����ͷ�һ��ҳ�棬���ҳ������Ǹɾ���
     */
    void release(int pageId) {
        int index = getPageIndex(pageId, true);
        if (index == -1) {
            std::cout << "OneFileManagerwriteBack.release() error" << std::endl;
            return;
        }
        bufPageManager -> release(index);
    }
    
    /*
     *  @������:writeBack
     *  ����:��ҳ�����д��һ���޸���ɵ�ҳ�棬�Զ�ѡ����ֱ���ͷŻ���д�����ͷ�
     */
    void writeBack(int pageId) {
        int index = getPageIndex(pageId, true);
        if (index == -1) {
            std::cout << "OneFileManager.writeBack() error" << std::endl;
            return;
        }
        bufPageManager -> writeBack(index);
    }
    
    /*
     *  @������:close
     *  ����:�ر�����ļ����Ѵ򿪵�����ҳ��д��
     */
    void close() {
        for (std::map<int, int>::iterator ite = indexMap.begin(); ite != indexMap.end(); ite ++) {
            bufPageManager -> writeBack(ite -> first);
        }
        indexMap.clear();
    }
    
protected:
    ///��������
    /*
     *  @������:
     *  ����:��ҳ��Ż�ȡ����ҳ�������еı�ţ�������˳��ɾ��
     */
    int getPageIndex(int pageId, bool eraseFlag) {
        int index = -1;
        if (indexMap.find(pageId) == indexMap.end()) {
            index = bufPageManager -> hash -> findIndex(fileId, pageId);
        } else {
            index = indexMap[pageId];
            if (eraseFlag) {
                indexMap.erase(pageId);
            }
        }
        return index;
    }
};


#endif // ONE_FILE_MANAGER_H_
