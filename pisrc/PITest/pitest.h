TEST(piut_funcs, piut_getapiversion)
{
    char version[32];
    int len = sizeof(version);
    printf("define char version[32], the sizeof(version) is %d.\n", len);
    if (!piut_getapiversion(version, len))
    {
        printf ("\nPI-API version %s", version);
    }
    printf("\n");
}

TEST(piut_funcs, piut_netserverinfo)
{
    int32 connection = PrintServerInfo();
    // unconnected if FALSE
    EXPECT_EQ(FALSE, connection);
}

TEST(piut_funcs, piut_connect)
{
    int32 connection = piut_connect("arch");
    // 0 stand for Success
    EXPECT_EQ(FALSE, connection); 
}

TEST(pipt_funcs, pipt_findpoint)
{
    int32 connection = PrintServerInfo();
    if (connection)
    {
        printf("connected\n");
        int32 ptNumb = 0;
        char tagname[TAG_LEN + 1] = "SINUSOID";
        // when calling the function pipt_findpoint, 
        // the argument tagname can't be const string, or throwing exception.
        // the tagname is the buffer for returned tagname.
        // the max length of the tagname is 80, exclude the null charactor.
        int32 rVal = pipt_findpoint(tagname, &ptNumb);
        printf("tag %s pointNumber %d\n", tagname, ptNumb);
        EXPECT_EQ(FALSE, rVal);
        //
        ZeroMemory(tagname, TAG_LEN + 1);
        strcpy_s(tagname, "watervalue");
        rVal = pipt_findpoint(tagname, &ptNumb);
        printf("tag %s pointNumber %d\n", tagname, ptNumb);
        EXPECT_EQ(FALSE, rVal);
    }
    else 
    {
        printf("unconnected");
    }
    printf("\n");
}

TEST(pipt_funcs, pipt_descriptor)
{
    int32 point = 13;
    char descriptor[27] = {0};
    int32 result = pipt_descriptor(point, descriptor, 27);
    EXPECT_EQ(FALSE, result);
    printf ( "\npipt_descriptor result:%ld description: %s\n", result, descriptor);
}

TEST(pipt_funcs, pipt_pointtype)
{
    int32 point = 13;
    char pttype;
    int32 result = pipt_pointtype(point, &pttype);
    EXPECT_EQ(FALSE, result);
    printf ( "\npipt_pointtype result:%ld pointtype: %c\n", result, pttype);
}

TEST(pisn_funcs, pisn_getsnapshot)
{
    printf("\nsystem time is %ld\n", time(NULL));
    int32 point = 13;
    float rval;
    int32 ival;
    int32 timedate;
    int32 result = pisn_getsnapshot(point, &rval, &ival, &timedate);
    EXPECT_EQ(FALSE, result);
    printf("\npoint 13 pisn_getsnapshot result:%ld\n", result);
    printf("rval is %lf; ival is %ld; timedate is %ld\n", rval, ival, timedate);
    
    point = 1;
    result = pisn_getsnapshot(point, &rval, &ival, &timedate);
    EXPECT_EQ(FALSE, result);
    printf("\npoint 1  pisn_getsnapshot result:%ld\n", result);
    printf("rval is %lf; ival is %ld; timedate is %ld\n", rval, ival, timedate);
}

TEST(piar_funcs, piar_value)
{
    int32 point = 13;
    float rval;
    int32 ival;
    int32 timedate;
    int32 result = piar_value(point, &timedate, ARCVALUEBEFORE, &rval, &ival);
    EXPECT_EQ(FALSE, result);
    printf("\npoint 13 piar_value result:%ld\n", result);
    printf("rval is %lf; ival is %ld; timedate is %ld\n", rval, ival, timedate);
    
    point = 1;
    result = piar_value(point, &timedate, ARCVALUEBEFORE, &rval, &ival);
    EXPECT_EQ(FALSE, result);
    printf("\npoint 1  piar_value result:%ld\n", result);
    printf("rval is %lf; ival is %ld; timedate is %ld\n", rval, ival, timedate);
}

TEST(pisn_funcs_ex, pisn_getsnapshotsx)
{
    int32 point = 13;
    int32 pt_count = 1;
    float64 rval, arcrval;
    int32 ival, arcival;
    void *bval, *arcbval;
    uint32 bsize, arcbsize;
    int32  istat, arcistat;
    int16 flags, arcflags;
    PITIMESTAMP ts, arcts;
    int32 error;
    bval = NULL;
    int32 result = pisn_getsnapshotsx(&point, &pt_count, &rval, &ival, 
        bval, &bsize, &istat, &flags, &ts, &error, GETFIRST);
    EXPECT_EQ(FALSE, result);
    printf ( "\npisn_getsnapshotsx result:%ld\n", result);
}

TEST(piar_funcs_ex, piar_getarcvaluex)
{
    int32 point = 13;
    int32 pt_count = 1;
    float64 rval, arcrval;
    int32 ival, arcival;
    void *bval, *arcbval;
    uint32 bsize, arcbsize;
    int32  istat, arcistat;
    int16 flags, arcflags;
    PITIMESTAMP ts, arcts;
    int32 error;
    int32 result = piar_getarcvaluex(point, ARCVALUEBEFORE, 0, 
        0, 0, 0, 0, 0, &arcts);
    EXPECT_EQ(FALSE, result);
    printf ( "\npiar_getarcvaluex result:%ld\n", result);
}

TEST(piar_funcs_ex, piar_getarcvaluesx)
{
    int32 point = 13;
    int32 pt_count = 1;
    float64 rval, arcrval;
    int32 ival, arcival;
    void *bval, *arcbval;
    uint32 bsize, arcbsize;
    int32  istat, arcistat;
    int16 flags, arcflags;
    PITIMESTAMP ts, arcts;
    int32 error;
    arcbval = NULL;
    int32 result = piar_getarcvaluesx(point, ARCflag_comp, &pt_count, 
        &arcrval, &arcival, arcbval, &arcbsize, &arcistat, &arcflags, 
        &ts, &arcts, GETFIRST);
    EXPECT_EQ(FALSE, result);
    printf ( "\npiar_getarcvaluesx result:%ld\n", result);
}

TEST(piut_funcs, piut_disconnect)
{
    int32 r = piut_disconnect();
    // 0 Success.
    EXPECT_EQ(FALSE, r);
}

TEST(pilg_funcs, pilg_login)
{
    int32 r = pilg_login();
}