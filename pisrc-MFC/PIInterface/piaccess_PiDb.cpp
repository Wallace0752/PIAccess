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
	TAG tag = {'\0',0,'\0','\0','\0',PI_Type_bad,0,0,NULL,0,0,0,NULL};
	int result;
	result = GetTAGFromjTag(env,objTag,tag);
	if(!result)
	{
		printf("Error in InitTagFromjTag code:%d",result);
		return 0;
	}
	result = InitTAGFromPI(tag);
	
	result = pisn_getsnapshotx(tag.pointnum,&tag.rval,&tag.ival,tag.bval,&tag.bsize,
		&tag.istat,&tag.flags,&tag.ts);
	if(result)
	{
		tag.istat = 0xffffffff;
		printf("Error in pisn_getsnapshotx!");
	}
	result = GetStateCode(tag);
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
	jsize length = env->GetArrayLength((jarray)arrTag);

	for (int i = 0;i<length;i++)
	{
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
	TAG tag = {'\0',0,'\0','\0','\0',PI_Type_bad,0,0,NULL,0,0,0,NULL};
	tag.pointnum = iPtNumber;

	InitTAGFromPI(tag);
	PITIMESTAMP tmStart = CalendarToPITIMESTAMP(env,objCalStart);
	tag.ts = CalendarToPITIMESTAMP(env,objCalEnd);
	int32 count = env->GetArrayLength((jarray)objarTag);
	int result = piar_getarcvaluesx(tag.pointnum,ARCflag_comp,&count,&tag.rval,
		&tag.ival,&tag.bval,&tag.bsize,&tag.istat,&tag.flags,&tmStart,&tag.ts,GETFIRST);
	int i = 0;
	while(!result)
	{
		result = GetStateCode(tag);
		jobject objTag = env->GetObjectArrayElement(objarTag,i++);
		SetjTagFromTAG(env,tag,objTag);
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
	InitTAGFromPI(tag);
	int32 tmCount = env->GetArrayLength((jarray)objarCal);
	PITIMESTAMP *tm =new PITIMESTAMP[tmCount];
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
		result = GetStateCode(tag);
		//printf("strState:%s",tag.strstat);
		jobject objTag = env->GetObjectArrayElement(objarTag,i++);
		SetjTagFromTAG(env,tag,objTag);
		result = piar_getarcvaluesx(tag.pointnum,ARCflag_time,&tmCount,&tag.rval,
			&tag.ival,&tag.bval,&tag.bsize,&tag.istat,&tag.flags,tm,&tag.ts,GETNEXT);
	}
	delete[] tm;
	return 1;
}

JNIEXPORT jint JNICALL Java_piaccess_PiDb_GetState
(JNIEnv *env, jobject obj, jint iStat, jstring strStat)
{
	printf("start!");
	char bufStat[80];
	int result = pipt_digstate((int32)iStat,bufStat,sizeof(bufStat));
	if(result)
		strncpy ( bufStat, "-----", sizeof(bufStat));
	bufStat[79] = '\0';
	printf("bufStat:%s",bufStat);
	jclass jclsStr = env->GetObjectClass((jobject)strStat);
	jmethodID jmValueOfID = env->GetStaticMethodID(jclsStr,"valueOf","([C)Ljava/lang/String;");
	strStat = (jstring)env->CallStaticObjectMethod(jclsStr,jmValueOfID,bufStat);
	//strStat = env->NewStringUTF(bufStat);
	return 1;
}