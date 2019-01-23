#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "md5c.h"
#ifdef __cplusplus
}
#endif

class CMD5
{
public:
	CMD5(){};
	~CMD5(){};

public:
	QString GetMD5HexString(char* pCharSrc)
	{
		unsigned char digest[16];
		MDString(pCharSrc, digest);
		QString strRtn = "", strTemp;
		for (int nIdx = 0; nIdx < 16; nIdx++)
		{
			char buffer[10];
			sprintf(buffer, "%02x", digest[nIdx]);
			strRtn += buffer;
		}
		return strRtn;
	}
};