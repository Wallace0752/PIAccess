// #include "piaccess_PiDb.h"
// #include "PIInterface.h"
//#include <jni.h>
// #include "piaccess_PiDb.h"
// #include "piapix.h"
#include "PIInterface.h"

/*
* Class:     piaccess_PiDb
* Method:    FindPointNumber
* Signature: (Ljava/lang/String;I)I
*/
JNIEXPORT jint JNICALL Java_piaccess_PiDb_FindPointNumber(JNIEnv *env, jobject obj, jstring strName)
{
	//通过标签点的名称取得点的编号
	int32 iNumber;
	char* cName = (char*)env->GetStringUTFChars(strName,NULL);
	int result = pipt_findpoint(cName,&iNumber);
	if(result)
	{
		env->ReleaseStringUTFChars(strName,cName);
		if(result>0)
		{
			printf("System Error!");
			return -2;
		}
		if(-2==result)
		{
			printf("Passed tag is all spaces");
			return -3;
		}
			
		if(-5==result)
		{
			printf("Tag not found, or not yet connected to a server");
			return -1;
		}
	}
	env->ReleaseStringUTFChars(strName,cName);
	return iNumber;
}

/*
* Class:     piaccess_PiDb
* Method:    GetSingleSNData
* Signature: (Lpiaccess/Tag;)I
*/
JNIEXPORT jint JNICALL Java_piaccess_PiDb_GetSingleSNData
(JNIEnv *env, jobject obj, jobject objTag)
{
	//printf("Start!\n");
	TAG tag = {'\0',0,'\0','\0','\0',PI_Type_bad,0,0,NULL,0,0,0,NULL};
	//tag.pointnum = 0;
	//printf("pointnum:%d\n",tag.pointnum);
	int result;
	result = GetTAGFromjTag(env,objTag,tag);
	//printf("GetTAGFromjTag succeed!");
	if(!result)
	{
		printf("Error in InitTagFromjTag code:%d",result);
		return 0;
	}
	//printf("point num:%d",tag.pointnum);
	result = InitTAGFromPI(tag);
	
	pisn_getsnapshotx(tag.pointnum,&tag.rval,&tag.ival,tag.bval,&tag.bsize,
		&tag.istat,&tag.flags,&tag.ts);
	//printf("iNumber:%d,dValue:%f,iValue:%d \n",iNumber,pSnapDval,pSnapIval);
	//printf("time:%f",tag.ts.second);
	result = SetjTagFromTAG(env,tag,objTag);
	if(!result)
	{
		printf("Error in SetjTagFromTAG code:%d",result);
		return 0;
	}
	return 1;
}

/*
* Class:     piaccess_PiDb
* Method:    GetArraySNData
* Signature: ([Lpiaccess/Tag;)I
*/
JNIEXPORT jint JNICALL Java_piaccess_PiDb_GetArraySNData
(JNIEnv *env, jobject obj, jobjectArray arrTag)
{
	//printf("start!");
	jsize length = env->GetArrayLength((jarray)arrTag);
	//printf("Length:%d",length);
	for (int i = 0;i<length;i++)
	{
		//printf("getting array element");
		jobject objTag = env->GetObjectArrayElement(arrTag,i);
		jint result = Java_piaccess_PiDb_GetSingleSNData(env, 
			obj,objTag);
		if(!result)
		{
			printf("Error in Getting Array Element %d",i);
			continue;
		}
	}

	return 1;
}
JNIEXPORT void JNICALL Java_piaccess_PiDb_DateTest
(JNIEnv *env, jobject obj, jobject objCalIn, jobject objCalOut)
{
	jclass jclsobjCal = env->GetObjectClass(objCalIn);
	if(!jclsobjCal)
	{
		printf("Error in GetObjectClass!\n");
		return;
	}
	jmethodID jmGetID = env->GetMethodID(jclsobjCal,"get","(I)I");
	if(!jmGetID)
	{
		printf("Error in GetMethodID!\n");
		return;
	}
	jfieldID jfYEARID = env->GetStaticFieldID(jclsobjCal,"YEAR","I");
	if(!jfYEARID)
	{
		printf("Error in GetStaticFieldID!\n");
		return;
	}
	jint jYearCode = env->GetStaticIntField(jclsobjCal,jfYEARID);
	jint jYear = env->CallIntMethod(objCalIn,jmGetID,(int)jYearCode);
	//printf("Year Code is %d,Year is %d",jYearCode,jYear);
}
/*
* Class:     piaccess_PiDb
* Method:    GetARCount
* Signature: (Ljava/util/Calendar;Ljava/util/Calendar;I)I
*/
JNIEXPORT jint JNICALL Java_piaccess_PiDb_GetARCount(JNIEnv *env, 
jobject obj, jobject objCalStart, jobject objCalEnd, jint iPtNumber)
{
	PITIMESTAMP tmStart = CalendarToPITIMESTAMP(env,objCalStart);
	PITIMESTAMP tmEnd = CalendarToPITIMESTAMP(env,objCalEnd);
	int count=0;
	int32 Num = MAXLONG;
	int result = piar_getarcvaluesx(iPtNumber,ARCflag_comp,&Num,NULL,
		NULL,NULL,NULL,NULL,NULL,&tmStart,&tmEnd,GETFIRST);
	while(!result)
	{
		count++;
		result = piar_getarcvaluesx(iPtNumber,ARCflag_comp,&Num,NULL,
			NULL,NULL,NULL,NULL,NULL,&tmStart,&tmEnd,GETNEXT);
	}
	return count;
}

/*
* Class:     piaccess_PiDb
* Method:    GetARData
* Signature: (Ljava/util/Calendar;Ljava/util/Calendar;I[Lpiaccess/Tag;)I
*/
JNIEXPORT jint JNICALL Java_piaccess_PiDb_GetARData(JNIEnv *env,
jobject obj, jobject objCalStart, jobject objCalEnd, jint iPtNumber, 
jobjectArray objarTag)
{
	//TAG tag;
	TAG tag = {'\0',0,'\0','\0','\0',PI_Type_bad,0,0,NULL,0,0,0,NULL};
	tag.pointnum = iPtNumber;
	//printf("ptnumber:%d",tag.pointnum);
	InitTAGFromPI(tag);
	PITIMESTAMP tmStart = CalendarToPITIMESTAMP(env,objCalStart);
	tag.ts = CalendarToPITIMESTAMP(env,objCalEnd);
	int32 count = env->GetArrayLength((jarray)objarTag);
	int result = piar_getarcvaluesx(tag.pointnum,ARCflag_comp,&count,&tag.rval,
		&tag.ival,&tag.bval,&tag.bsize,&tag.istat,&tag.flags,&tmStart,&tag.ts,GETFIRST);
	int i = 0;
	while(!result)
	{
		//printf("Month:%d\n",tmEnd.month);
		jobject objTag = env->GetObjectArrayElement(objarTag,i++);
		SetjTagFromTAG(env,tag,objTag);
//		SetObject(env,objTag,rval,ival,istat,iflag,tmEnd);
// 		result = piar_getarcvaluesx(iPtNumber,ARCflag_comp,&count,&rval,
// 			&ival,NULL,NULL,&istat,&iflag,&tmStart,&tmEnd,GETNEXT);
		result = piar_getarcvaluesx(tag.pointnum,ARCflag_comp,&count,&tag.rval,
			&tag.ival,&tag.bval,&tag.bsize,&tag.istat,&tag.flags,&tmStart,&tag.ts,GETNEXT);
	}
	return 1;
}

/*
* Class:     piaccess_PiDb
* Method:    GetArrayARData
* Signature: ([Ljava/util/Calendar;I[Lpiaccess/Tag;)I
*/
JNIEXPORT jint JNICALL Java_piaccess_PiDb_GetArrayARData(JNIEnv *env, 
jobject obj, jobjectArray objarCal, jint iPtNumber, jobjectArray objarTag)

{
	TAG tag = {'\0',0,'\0','\0','\0',PI_Type_bad,0,0,NULL,0,0,0,NULL};
	tag.pointnum = iPtNumber;
	printf("pt number:%d",tag.pointnum);
	InitTAGFromPI(tag);
// 	float64 rval;
// 	int32 ival,istat;
// 	int16 iflag;
	printf("initialize finished!");
	int32 tmCount = env->GetArrayLength((jarray)objarCal);
	printf("count:%d",tmCount);
	PITIMESTAMP *tm =new PITIMESTAMP[tmCount];
	//PITIMESTAMP tmStamp;
	for(int i=0;i<tmCount;i++)
	{
		jobject objCal = env->GetObjectArrayElement(objarCal,i);
		tm[i] = CalendarToPITIMESTAMP(env,objCal);
	}
	int result = piar_getarcvaluesx(tag.pointnum,ARCflag_time,&tmCount,&tag.rval,
		&tag.ival,&tag.bval,&tag.bsize,&tag.istat,&tag.flags,tm,&tag.ts,GETFIRST);
	int i = 0;
	while(!result)
	{
		jobject objTag = env->GetObjectArrayElement(objarTag,i++);
//		SetObject(env,objTag,rval,ival,istat,iflag,tmStamp);
		SetjTagFromTAG(env,tag,objTag);
// 		result = piar_getarcvaluesx(iPtNumber,ARCflag_time,&tmCount,&rval,
// 			&ival,NULL,NULL,&istat,&iflag,tm,&tmStamp,GETNEXT);
		int result = piar_getarcvaluesx(tag.pointnum,ARCflag_time,&tmCount,&tag.rval,
			&tag.ival,&tag.bval,&tag.bsize,&tag.istat,&tag.flags,tm,&tag.ts,GETNEXT);
	}
	delete[] tm;
	return 1;
}
JNIEXPORT jobject JNICALL Java_piaccess_PiDb_EnumTest
(JNIEnv *env, jobject obj)
{
// 	jclass jclsValType = env->FindClass("piaccess/PIvaluetype");
// 	if(!jclsValType)
// 	{
// 		printf("Error find PIValueType");
// 		return NULL;
// 	}
// 	jobject jobjEnum = env->AllocObject(jclsValType);
// 	if(!jobjEnum)
// 	{
// 		printf("Error in AllocObject!");
// 		return NULL;
// 	}
// 	jfieldID jidPtType = env->GetStaticFieldID(jclsValType,"PI_Type_char","Lpiaccess/PIvaluetype;");
// 	if(!jidPtType)
// 	{
// 		printf("Error in GetStaticFieldID");
// 		return NULL;
// 	}
// 	jobjEnum = env->GetStaticObjectField(jclsValType,jidPtType);
// 	jobject objPtType = env->GetStaticObjectField(jclsValType,jidPtType);
// 	env->SetStaticObjectField(jclsValType,jidPtType,jidPtType);
// 	return jobjEnum;
	return NULL;
}
