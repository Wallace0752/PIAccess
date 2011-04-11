// PITest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <piapix.h>
#include "piutil.h"
#include "pitest.h"

int start_gtest(int *pInt, _TCHAR** ppChar)
{
    // start googleTest.
    testing::InitGoogleTest(pInt, ppChar);
    return RUN_ALL_TESTS();
}

void pi()
{
    piut_setprocname("snap");
    printf("Attempting connection to pi\n");
    //int result = piut_setservernode("localhost");
    
    int result = piut_connect("snap");
    if (result)
    {
        printf("\n Error %d, connecting to localhost", result);
    }
    else
    {
        printf("done\n");
        PrintServerInfo();        
    }
    
    TAG tag;
    strcpy_s(tag.tagname, "SINUSOID");
    int32 rVal = pipt_findpoint(tag.tagname, &tag.point);
    printf("pointname %s pointNumber %d\n", tag.tagname, tag.point);
    
    int32 pt_count = 1;
    int32 error = 0;
    float rval;
    int32 ival;
    int32 timedate;
    rVal = pisn_getsnapshot(tag.point, &rval, &ival, &timedate);
    tm* ptd = gmtime((const time_t*)&timedate);
    time_t tNow;
    time(&tNow);
    //tm* ptm = localtime(&tNow);
    //rVal = pisn_getsnapshotsx(&tag.point, &pt_count, &tag.rval, &tag.ival, 
    //    tag.bval, &tag.bsize, &tag.istat, &tag.flags, &tag.ts, &error, GETFIRST);
    //rVal = piar_getarcvaluex(

    int r = piut_disconnect();
}

int _tmain(int argc, _TCHAR* argv[])
{
    int i = start_gtest(&argc, argv);
    //////////////////////////////////////

    //pi();
	return 0;
}