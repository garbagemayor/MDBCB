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
    
public:
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
    //���캯����Ĭ���Ǵ��Ѵ��ڵ��ļ�
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
            std::cout << "OneFileManager() error" << std::endl;
            return;
        }
        std::cout << "OneFileManager() fildId = " << fileId << std::endl;
    }
    
protected:
    //��ҳ��Ż�ȡ����ҳ�������еı�ţ�������˳��ɾ��
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
    
public:
    ///���ļ��ڵ�ҳ���в���
    //��ҳ��Ż�ȡҳ����
    ByteBufType getPage(int pageId) {
        int index;
        BufType data = bufPageManager -> getPage(fileId, pageId, index);
        indexMap[pageId] = index;
        return (ByteBufType) data;
    }
    
    //����һ���µ�ҳ����ȡҳ��ź�ҳ����
    ByteBufType getNewPage(int & pageId) {
        pageId = pageCnt;
        pageCnt ++;
        int index;
        BufType data = bufPageManager -> getPage(fileId, pageId, index);
        indexMap[pageId] = index;
        return (ByteBufType) data;
    }
    
    //����һ���µ�ҳ��������ҳ��ţ���ȡҳ����
    ByteBufType getNewPage() {
        int pageId;
        return getNewPage(pageId);
    }
    
    //��ҳ��ű��һ��ҳ�����ʹ������滻�㷨������Ҫ�滻��
    void access(int pageId) {
        int index = getPageIndex(pageId, false);
        if (index == -1) {
            std::cout << "OneFileManager.access() error" << std::endl;
            return;
        }
        bufPageManager -> access(index);
    }
    
    //��ҳ��ű����ҳ
    void markDirty(int pageId) {
        int index = getPageIndex(pageId, false);
        if (index == -1) {
            std::cout << "OneFileManager.markDirty() error" << std::endl;
            return;
        }
        bufPageManager -> markDirty(index);
    }
    
    //��ҳ����ͷ�һ��ҳ�棬���ҳ������Ǹɾ���
    void release(int pageId) {
        int index = getPageIndex(pageId, true);
        if (index == -1) {
            std::cout << "OneFileManagerwriteBack.release() error" << std::endl;
            return;
        }
        bufPageManager -> release(index);
    }
    
    //��ҳ�����д��һ���޸���ɵ�ҳ�棬�Զ�ѡ����ֱ���ͷŻ���д�����ͷ�
    void writeBack(int pageId) {
        int index = getPageIndex(pageId, true);
        if (index == -1) {
            std::cout << "OneFileManager.writeBack() error" << std::endl;
            return;
        }
        bufPageManager -> writeBack(index);
    }
    
    //�ر�����ļ����Ѵ򿪵�����ҳ��д��
    void close() {
        for (std::map<int, int>::iterator ite = indexMap.begin(); ite != indexMap.end(); ite ++) {
            bufPageManager -> writeBack(ite -> first);
        }
        indexMap.clear();
    }
};


#endif // ONE_FILE_MANAGER_H_
