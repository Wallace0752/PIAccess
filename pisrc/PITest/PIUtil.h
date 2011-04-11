#define TAG_LEN 80

typedef struct
{
    char tagname[TAG_LEN + 1];
    int32 point;
    char descriptor[27];
    char engunit[32];
    char itag[33];
    char pt_type;
    PIvaluetype pt_typex;
    float64 rval, arcrval;
    int32 ival, arcival;
    void *bval, *arcbval;
    uint32 bsize, arcbsize;
    int32  istat, arcistat;
    int16 flags, arcflags;
    PITIMESTAMP ts, arcts;
} TAG;

PIINT32 PrintServerInfo(char PIPTR *namestr, int32 namelen,
    char PIPTR *addrstr, int32 addrlen, int32 PIPTR *connected)
{
    int32 rVal = piut_netserverinfo(namestr, namelen, addrstr, addrlen, connected);
    printf("name(len = %d) %s\n", sizeof(namestr), namestr);
    printf("addr(len = %d) %s\n", sizeof(addrstr), addrstr);
    return rVal;
}

int32 PrintServerInfo()
{
    char name[32];
    char address[32];
    int32 connection;
    PrintServerInfo(name, 32, address, 32, &connection);
    
    return connection;
}

