#ifndef PAGE_DEF
#define PAGE_DEF

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

///文件管理器
/*
 *  最大文件数量
 */
#define MAX_FILE_NUM 128

///文件页
/*
 *  一个页面中的字节数
 */
#define PAGE_SIZE 8192

/*
 *  页头的字节数
 */
#define PAGE_HEADER_SIZE 60

/*
 *  一个页面中的整数个数
 */
#define PAGE_INT_NUM 2048

/*
 *  页面字节数以2为底的指数
 */
#define PAGE_SIZE_IDX 13

/*
 *
 */
#define MAX_FMT_INT_NUM 128

///数据表
/*
 *  数据库中表的个数上限
 */
#define MAX_TB_NUM 31

/*
 *  
 */
#define MAX_TYPE_NUM 256

/*
 *  数据表的名字、列的名字的长度限制
 */
#define MAX_NAME_LENGTH 128

/*
 *  一个表中列的上限
 */
#define MAX_COL_NUM 31

///索引
/*
 *  B+树最多子节点数
 */
#define MAX_SON_NUM 400

/*
 *  B+树最少子节点数
 */
#define MIN_SON_NUM 200

///缓存页管理器
/*
 *  缓存中页面个数上限
 */
#define CAP 60000

/*
 *  hash算法的模
 */
 
///Debug, Release
#define MOD 60000

/*
 *  Debug, Release
 */
#define IN_DEBUG 0
#define DEBUG_DELETE 0
#define DEBUG_ERASE 1
#define DEBUG_NEXT 1
#define RELEASE 1

typedef unsigned int* BufType;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long long ull;
typedef long long ll;
typedef double db;
typedef int INT;
typedef int(cf)(uchar*, uchar*);
int current = 0;
int tt = 0;

#endif // PAGE_DEF
