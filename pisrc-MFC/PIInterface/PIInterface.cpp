#include "PIInterface.h"
#include <tchar.h>


int GetTAGFromjTag(JNIEnv *env,jobject jobjTag, TAG &tag)
{
	//获取类
	jclass jclsTag = env->GetObjectClass(jobjTag);
	if(!jclsTag)
	{
		printf("Error in GetSnapShot GetObjectClass(Tag)\n");
		return 0;
	}
	//先取出标签名
	jfieldID idName = env->GetFieldID(jclsTag,"tagname","Ljava/lang/String;");
	jstring jstrName = (jstring)env->GetObjectField(jobjTag,idName);
	if(jstrName)
	{
		const char* strConName = env->GetStringUTFChars(jstrName,NULL);
		strcpy(tag.tagname,strConName);
		env->ReleaseStringUTFChars(jstrName,strConName);
		return 1;
	}
	jfieldID  idPtNum =env->GetFieldID(jclsTag,"pointnum","I");
	tag.pointnum = env->GetIntField(jobjTag,idPtNum);
	
	return 1;
	
}
int SetjTagFromTAG(JNIEnv *env,TAG &tag,jobject jobjTag)
{
	//获取类
	jclass clsTag = env->GetObjectClass(jobjTag);
	if(!clsTag)
	{
		printf("Error in GetSnapShot GetObjectClass(Tag)");
		return 0;
	}
	jfieldID jfID = env->GetFieldID(clsTag,"rval","D");
	env->SetDoubleField(jobjTag,jfID,tag.rval);
	jfID = env->GetFieldID(clsTag,"ival","I");
	env->SetIntField(jobjTag,jfID,tag.ival);
	jfID = env->GetFieldID(clsTag,"istat","I");
	env->SetIntField(jobjTag,jfID,tag.istat);
	jfID = env->GetFieldID(clsTag,"flags","S");
	env->SetShortField(jobjTag,jfID,tag.flags);
	jfID = env->GetFieldID(clsTag,"pointnum","I");
	env->SetIntField(jobjTag,jfID,tag.pointnum);
	jobject jobjCal = PITIMESTAMPToCalendar(env,tag.ts);
	SetTagCalendar(env,jobjTag,jobjCal);
	SetTagPIvaluetype(env,jobjTag,tag.pt_typex);

	//处理String类型的字段
	jfID = env->GetFieldID(clsTag,"strstat","Ljava/lang/String;");
	//jstring jstr = env->NewStringUTF(tag.strstat);
	jstring jstr = char2jstring(env,(const char*)tag.strstat);
	env->SetObjectField(jobjTag,jfID,jstr);

	jfID = env->GetFieldID(clsTag,"tagname","Ljava/lang/String;");
	//jstr = env->NewStringUTF(tag.tagname);
	jstr = char2jstring(env,(const char*)tag.tagname);
	env->SetObjectField(jobjTag,jfID,jstr);

	jfID = env->GetFieldID(clsTag,"descriptor","Ljava/lang/String;");
	//jstr = env->NewStringUTF(tag.descriptor);
	jstr = char2jstring(env,(const char*)tag.descriptor);
	env->SetObjectField(jobjTag,jfID,jstr);

	jfID = env->GetFieldID(clsTag,"engunit","Ljava/lang/String;");
	//jstr = env->NewStringUTF(tag.engunit);
	jstr = char2jstring(env,(const char*)tag.engunit);
	env->SetObjectField(jobjTag,jfID,jstr);
	
	env->DeleteLocalRef(jstr);
	return 1;
}
int InitTAGFromPI(TAG &tag)//!!使用之前必须对tag进行初始化
{
	int result;
	if('\0'!=tag.tagname[0])
	{
		result = pipt_findpoint(tag.tagname,&tag.pointnum);
		if(result)
		{
			if(result>0)
			{
				printf("System Error!");
				return 0;
			}
			if(-2==result)
			{
				printf("Passed tag is all spaces");
				return 0;
			}
			if(-5==result)
			{
				printf("Tag not found, or not yet connected to a server");
				return -1;
			}
		}
	}
	else//若没有标签名，则直接根据标签编号
	{
		if(!tag.pointnum)
		{
			//简单初始化，tag各个字段均为默认值
			printf("未指定标签名或者标签编号");
			return -2;
		}
		result = pipt_ptexist(tag.pointnum);
		if(!result)
		{
			printf("Point do not exist");
			return -1;
		}	
		pipt_tag(tag.pointnum,tag.tagname,81);
	}

	//读取单位信息，保存到tag中
	result = pipt_engunitstring ( tag.pointnum, tag.engunit, 32 );
	if ( result )
	{
		//printf ( "\npipt_engunitstring %ld", result );
		tag.engunit[0] = '\0';
	}

	//读取描述信息，保存到tag中
	result = pipt_descriptor ( tag.pointnum, tag.descriptor, 27 );
	if ( result )
	{
		//printf ( "\npipt_descriptor %ld", result );
		tag.descriptor[0] = '\0';
	}
	//读取标签点的类型信息，保存到tag中
	result = pipt_pointtypex ( tag.pointnum, &tag.pt_typex );
	if ( result )
	{
		//printf ( "\npipt_pointtypex %ld", result );
		tag.pt_typex = PI_Type_bad;
	}
	//读取标签点的设备标签信息，保存到tag中
	result = pipt_instrumenttag ( tag.pointnum, tag.instrumenttag,33);
	if(result)
	{
		//printf("\npipt_instrumenttag %ld",result);
		tag.instrumenttag[0] = '\0';
	}
	//根据标签点的类型，对接收数值的几个变量进行赋值
	switch (tag.pt_typex ) {
			case PI_Type_PIstring:
			case PI_Type_blob:
			case PI_Type_PItimestamp:
				//以上三种类型暂时有问题
				break;
			case PI_Type_int16:
			case PI_Type_int32:
				tag.rval = NULL;
				tag.bval = NULL;
				tag.bsize = 0;
				break;
			case PI_Type_digital:
				tag.rval = NULL;
				tag.bval = NULL;
				tag.ival = NULL;
				tag.bsize = 0;
				break;
			default:/* floats, PI2 */
				tag.ival = NULL;
				tag.bval = NULL;
				tag.bsize = 0;
				break;
	}
	return 1;
}
void PIValueTypeToChar(PIvaluetype PtType,char* cType)
{
	char *PIValueTab[] ={
		"PI_Type_null", //= 0,
		"PI_Type_bool",
		"PI_Type_uint8",
		"PI_Type_int8",
		"PI_Type_char",
		"PI_Type_uint16",
		"PI_Type_int16",
		"PI_Type_uint32",
		"PI_Type_int32",
		"PI_Type_uint64",
		"PI_Type_int64",
		"PI_Type_float16",
		"PI_Type_float32",
		"PI_Type_float64",
		"PI_Type_PI2",
		"PI_Type_digital", //= 101,
		"PI_Type_blob",
		"PI_Type_PItimestamp", //= 104,
		"PI_Type_PIstring",
		"PI_Type_bad" //= 255
	};
	if(PtType<15)
	{
		cType = PIValueTab[PtType];
		return;
	}
	switch(PtType)
	{
	case 101:
		cType ="PI_Type_digital";
		break;
	case 102:
		cType ="PI_Type_blob";
		break;
	case 104:
		cType ="PI_Type_PItimestamp";
		break;
	case 105:
		cType ="PI_Type_PIstring";
		break;
	case 255:
		cType ="PI_Type_bad";
		break;
	default:
		break;
	}


}
//将Calendar转换成PITIMESTAMP
PITIMESTAMP CalendarToPITIMESTAMP(JNIEnv *env,jobject objCal)
{
	PITIMESTAMP tmStamp;
	//读取Calendar的数据
	jclass jclsCal = env->GetObjectClass(objCal);
	jmethodID jmGetID = env->GetMethodID(jclsCal,"get","(I)I");
	
	//年
	jfieldID jfID = env->GetStaticFieldID(jclsCal,"YEAR","I");
	jint jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.year = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);
	
	jfID = env->GetStaticFieldID(jclsCal,"MONTH","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.month = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode)+1;//Calendar中的月份是0到11月，此处加1转换成timestamp中的月份

	jfID = env->GetStaticFieldID(jclsCal,"DAY_OF_MONTH","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.day = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	jfID = env->GetStaticFieldID(jclsCal,"HOUR_OF_DAY","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.hour = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	jfID = env->GetStaticFieldID(jclsCal,"MINUTE","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.minute= (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	jfID = env->GetStaticFieldID(jclsCal,"SECOND","I");
	jCode = env->GetStaticIntField(jclsCal,jfID);
	tmStamp.second = (int32)env->CallIntMethod(objCal,jmGetID,(int)jCode);

	env->DeleteLocalRef(jclsCal);
	return tmStamp;
}
//设置jobject的属性
void SetObject(JNIEnv *env,jobject objTag,double rval, int ival, 
			   int istat, short iflag,PITIMESTAMP tmStp)
{
	//获取类
	jclass clsTag = env->GetObjectClass(objTag);
	if(!clsTag)
	{
		printf("Error in GetSnapShot GetObjectClass(Tag)");
		return ;
	}
	jfieldID jRValID = env->GetFieldID(clsTag,"rval","D");
	env->SetDoubleField(objTag,jRValID,rval);
	jfieldID jIValID = env->GetFieldID(clsTag,"ival","I");
	env->SetIntField(objTag,jIValID,ival);
	jfieldID jIStatID = env->GetFieldID(clsTag,"istat","I");
	env->SetIntField(objTag,jIStatID,istat);
	jfieldID jFlagsID = env->GetFieldID(clsTag,"flags","S");
	env->SetShortField(objTag,jFlagsID,iflag);
	jobject jobjCal = PITIMESTAMPToCalendar(env,tmStp);
	SetTagCalendar(env,objTag,jobjCal);
}

jobject PITIMESTAMPToCalendar(JNIEnv *env, PITIMESTAMP tmStamp)
{
	jclass jclsCal = env->FindClass("java/util/Calendar");
	if(!jclsCal)
	{
		printf("Error in FindClass!");
		return NULL;
	}
	jmethodID jmGetInsID = env->GetStaticMethodID(jclsCal,"getInstance","()Ljava/util/Calendar;");
	if(!jmGetInsID)
	{
		printf("Error in GetStaticMethodID!");
		return NULL;
	}
	jobject jobjCal = env->CallStaticObjectMethod(jclsCal,jmGetInsID);
	if(!jobjCal)
	{
		printf("Error in CallStaticObjectMethod!");
		return NULL;
	}
	jmethodID jmSetID = env->GetMethodID(jclsCal,"set","(IIIIII)V");
	if(!jmSetID)
	{
		printf("Error in GetMethodID!");
		return NULL;
	}

	env->CallVoidMethod(jobjCal,jmSetID,tmStamp.year,tmStamp.month-1,//日期转换，Calendar中的月份是从0到11月，因此此处应该减1
		tmStamp.day,tmStamp.hour,tmStamp.minute,(int)tmStamp.second);
	
	return jobjCal;
}
//设置标签点的Calendar值
void SetTagCalendar(JNIEnv *env,jobject jobjTag, jobject jobjCal)
{
	jclass jclsTag = env->GetObjectClass(jobjTag);
	jfieldID jfCalID = env->GetFieldID(jclsTag,"ts","Ljava/util/Calendar;");
	env->SetObjectField(jobjTag,jfCalID,jobjCal);
}
void SetTagPIvaluetype(JNIEnv *env, jobject jobjTag, PIvaluetype valType)
{
	const char* strValType = GetTypeStr(valType);
	//获取枚举类型的jobject对象
	jclass jclsValType = env->FindClass("piaccess/PIvaluetype");
	if(!jclsValType)
	{
		printf("Error find PIValueType");
		return ;
	}
	jfieldID jidPtType = env->GetStaticFieldID(jclsValType,strValType,"Lpiaccess/PIvaluetype;");
	if(!jidPtType)
	{
		printf("Error in GetStaticFieldID");
		return ;
	}
	jobject jobjEnum = env->GetStaticObjectField(jclsValType,jidPtType);
	//对jobjTag的pt_typex对象进行赋值操作
	jclass jclsTag = env->GetObjectClass(jobjTag);
	jfieldID jfValTypeID = env->GetFieldID(jclsTag,"pt_typex","Lpiaccess/PIvaluetype;");
	env->SetObjectField(jobjTag,jfValTypeID,jobjEnum);

}
const char *GetTypeStr ( PIvaluetype pttype)
{
	switch (pttype)
	{
	case PI_Type_null:
		return "PI_Type_null";
	case PI_Type_bool:
		return "PI_Type_bool";
	case PI_Type_char:
		return "PI_Type_char";
	case PI_Type_uint8:
		return "PI_Type_uint8";
	case PI_Type_int8:
		return "Integer-8";
	case PI_Type_uint16:
		return "PI_Type_uint16";
	case PI_Type_int16:
		return "PI_Type_int16";
	case PI_Type_uint32:
		return "PI_Type_uint32";
	case PI_Type_int32:
		return "PI_Type_int32";
	case PI_Type_uint64:
		return "PI_Type_uint64";
	case PI_Type_int64:
		return "PI_Type_int64";
	case PI_Type_digital:
		return "PI_Type_digital";
	case PI_Type_PIstring:
		return "PI_Type_PIstring";
	case PI_Type_PItimestamp:
		return "PI_Type_PItimestamp";
	case PI_Type_blob:
		return "PI_Type_blob";
	case PI_Type_float32:
		return "PI_Type_float32";
	case PI_Type_float16:
		return "PI_Type_float16";
	case PI_Type_float64:
		return "PI_Type_float64";
	case PI_Type_PI2:
		return "PI_Type_PI2";
	default:
		return "PI_Type_bad";
		break;
	}
}
int GetStateCode(TAG &tag)
{
	//printf("istat:%d",tag.istat);
	int result;
	int statlen = sizeof(tag.strstat);
	int localistat = tag.istat;
	if ( tag.istat == 0xffffffff )
	{
		strncpy ( tag.strstat, "ERROR", statlen );

		tag.strstat[statlen-1] = '\0';
		return 0;
	}
	else if ( tag.istat != 0 )//
	{
		localistat = tag.istat;
		if (tag.pt_typex == PI_Type_digital)
		{
			int32 digcode,dignumb;
			result = pipt_digpointers ( tag.pointnum, &digcode, &dignumb );
			if (!result && tag.istat >= 0 && tag.istat <= dignumb )
				localistat += digcode;
		}
		result = pipt_digstate ( localistat, tag.strstat, statlen );
		if ( result )
			strncpy ( tag.strstat, "-----", statlen );

		tag.strstat[statlen-1] = '\0';
		return 1;
	}
	else{
		strncpy ( tag.strstat, "Good", statlen );
		return 2;
	}
	
}
void SetjstringFromchar(char* cName, JNIEnv *env, jstring &jstrName)
{
	jclass jclsStr = env->FindClass("java/lang/String");
	jstring jstrBuf = env->NewStringUTF(cName);
	jmethodID jmInitID = env->GetMethodID(jclsStr,"<init>","(Ljava/lang/String;)V");
	env->CallObjectMethod(jstrName,jmInitID,jstrBuf);
}
void SetjBooleanFromBOOL(BOOL bval, JNIEnv *env, jobject &jBoolean)
{
	jclass jclsBoolean = env->GetObjectClass(jBoolean);
	//jboolean jbval = bval;
	jmethodID jmInitID = env->GetMethodID(jclsBoolean,"<init>","(Z)V");
	jBoolean = env->CallObjectMethod(jBoolean,jmInitID,(jboolean)bval);
	
}
jstring char2jstring(JNIEnv *env, const char* str)
{
	jstring jstr = 0;
	int lengthofstr = strlen(str);
	//int lengthofstr = sizeof(str)+1;
	//printf("length:%d",lengthofstr);
	int lengthofwstr = MultiByteToWideChar(CP_ACP,0,(LPCSTR)str,lengthofstr,NULL,0);
	LPWSTR lpwstr = new WCHAR[lengthofwstr];
	MultiByteToWideChar(CP_ACP,0,(LPCSTR)str,lengthofstr,lpwstr,lengthofwstr);
	jstr = env->NewString((jchar*)lpwstr,lengthofwstr);
	delete[] lpwstr;
	return jstr;
}