//__declspec(dllimport) int __stdcall add(int a,int b);
//__declspec(dllimport) __stdcall BOOL PIUT_GetApiVersion(LPTSTR /*in*/ version);

// #define ITEM_COUNT 5   //m_listPoints列表中item的数量
// #define TAG_LEN 80

// #include "piapi.h"
// #include "piapix.h"
// typedef struct
// {
// 	char tagname[TAG_LEN+1];
// 	int32 point;
// 	char descriptor[27];   
// 	char engunit[32];
// 	char itag[33];
// 	char pt_type;
// 	PIvaluetype pt_typex;
// 	float64 rval, arcrval;
// 	int32  ival, arcival;
// 	void  *bval, *arcbval;
// 	uint32 bsize, arcbsize;
// 	int32  istat, arcistat;
// 	int16  flags, arcflags;
// 	PITIMESTAMP ts, arcts;
// } TAG;

int WINAPI add(int a, int b)
{
    return a + b;
}