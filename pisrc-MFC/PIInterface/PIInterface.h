
#pragma once

#include "piapix.h"
#include "piaccess_PiDb.h"
#define TAG_LEN 80

typedef struct _TAG
{
	char tagname[TAG_LEN+1];
	int32 pointnum;
	char descriptor[27];   
	char engunit[32];
	char instrumenttag[33];
	PIvaluetype pt_typex;
	float64 rval;
	int32  ival;
	void  *bval;
	uint32 bsize;
	int32  istat;
	int16  flags;
	PITIMESTAMP ts;
} TAG;
//InitTAGFromjTag说明：
//根据java中的Tag对象jobjTag初始化C中的TAG结构体tag，将jobjTag中有tagname或者pointnum
//赋值到tag的相应字段
int GetTAGFromjTag(JNIEnv *env,jobject jobjTag, TAG &tag);
//SetjTagFromTAG说明：
//与InitTAGFromjTag相反，将TAG结构体tag的各个属性值赋值给jobjTag各个字段
int SetjTagFromTAG(JNIEnv *env,TAG &tag,jobject jobjTag);
//根据PI的值初始化一个TAG类型的对象,tag传入时需要指定tagname或者pointnum，
//返回一个已经初始化的TAG，其中TAG的单位、描述、点的类型等信息均已经读出
//返回值信息：0：系统错误；-1：标签点没有找到或者未连接到服务器；1：获取成功
//            -2：jobjTag的tagname或者pointnum均为空（0），tag各字段为默认值
int InitTAGFromPI(TAG &tag);
//将Calendar转换成PITIMESTAMP类型，其中objCal必须为Calendar类的对象
PITIMESTAMP CalendarToPITIMESTAMP(JNIEnv *env,jobject objCal);
//讲PITIMESTAMP类型转换成Calendar类型
jobject PITIMESTAMPToCalendar(JNIEnv *env, PITIMESTAMP tmStamp);
//将java中Tag类的对象jobjTag中的ts字段设置为jobjCal，jobjCal必须为Calendar类的对象
void SetTagCalendar(JNIEnv *env,jobject jobjTag, jobject jobjCal);
//设置java中的Tag类的对象objTag的各个字段的值
void SetObject(JNIEnv *env,jobject objTag,double rval, int ival, int istat, short iflag,PITIMESTAMP tmStp);
//将jobjTag的pt_typex字段设置为valType
void SetTagPIvaluetype(JNIEnv *env, jobject jobjTag, PIvaluetype valType);
//将枚举类型pttype的值转换成字符串类型
const char *GetTypeStr ( PIvaluetype pttype);
