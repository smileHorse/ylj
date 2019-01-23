/* POINTER defines a generic pointer type */
typedef unsigned char * POINTER;

/* UINT2 defines a two byte word */
//typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;


/* MD5 context. */
typedef struct {
	UINT4 state[4];                                   /* state (ABCD) */
	UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

void MD5Init (MD5_CTX *context);
void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen);
void MD5UpdaterString(MD5_CTX *context,const char *string);
int MD5FileUpdateFile (MD5_CTX *context,char *filename);
void MD5Final (unsigned char digest[16], MD5_CTX *context);
void MDString (char *string,unsigned char digest[16]);
int MD5File (char *filename,unsigned char digest[16]);


//////////////////////////////////////////////////////////////////////////
/*
void main(void)
{
	unsigned char digest[16];  //存放结果

	//第一种用法:

	MD5_CTX md5c;
	MD5Init(&md5c); //初始化
	MD5UpdaterString(&md5c,"你要测试的字符串");
	MD5FileUpdateFile(&md5c,"你要测试的文件路径");
	MD5Final(digest,&md5c);

	//第二种用法:
	MDString("你要测试的字符串",digest); //直接输入字符串并得出结果

	//第三种用法:
	MD5File("你要测试的文件路径",digest); //直接输入文件路径并得出结果
}

// c++ 引用
#ifdef __cplusplus
EXTERN_C {
#endif

#include "MD5/md5c.h"
#ifdef __cplusplus
}
#endif
*/
//////////////////////////////////////////////////////////////////////////