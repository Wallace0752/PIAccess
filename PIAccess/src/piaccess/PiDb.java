package piaccess;
import piaccess.Tag;
import java.util.Calendar;
//SN   SnapShot
//AR   Archive

//函数参数前注释所表示的意思：
///*i*/：传入参数；
///*o*/：传出参数；
///*i,o*/：先传入后传出

public class PiDb {
	//通过标签点的名称获得标签点的编号,返回值为标签点编号。若没有找到，则返回-1
	public native int FindPointNumber(/*i*/String TagName);
	//获取传入TagPoint的数据。传入时需要制定Tag名称或者Tag编号。若同时指定，则Tag名称优先
	public native int GetSingleSNData(/*i,o*/Tag TagPoint);
	//获取传入的TagPtArray的数据，传入时需要制定Tag名称或者Tag编号。若同时指定，则Tag名称优先
	public native int GetArraySNData(/*i,o*/Tag[] TagPtArray);
	//获得一个时间范围内记录的数量,返回值为记录的个数
	public native int GetARCount(/*i*/Calendar tmStart, /*i*/Calendar tmEnd, 
			/*i*/int PtNumber);
	//读取一个时间范围内的所有历史记录,注意TagArray所存储数据为PtNumber在不同时间的值
	//TagArray的大小需要由用户指定,可以通过GetARCount获取。
	public native int GetARData(/*i*/Calendar tmStart, /*i*/Calendar tmEnd,
			/*i*/int PtNumber, /*o*/Tag[] TagArray);
	//根据所提供的时间序列，获取一列对应的值，该值是通过插值算法计算出
	public native int GetArrayARData(/*i*/Calendar[] arrayTime,/*i*/int PtNumber,
			/*o*/Tag[] TagArray);
	//根据iStateCode获取状态代码在PI中所代表的意思
	//public native int GetState(/*i*/int iStateCode, /*o*/String strState);
	
	//根据服务器名称连接服务器,1表示连接成功，0表示连接失败，其中SvrName一般为服务器端IP地址,ProcName为自定义的服务器Process名称，为四个字符长度
	public native int ConnectServer(/*i*/String SvrName, /*i*/String ProcName/*四个字符长度*/);
	//将名称为strSvrName的服务器设置为默认服务器，成功返回1，否则返回0；
	public native int SetDefaultServer(/*i*/String strSvrName);
	//获取默认的服务器信息，strSvrName为服务器名称，strAddr为服务器地址，bConnected表示是否有连接
	public native int GetDefaultServerInfo(/*o*/String strSvrName, /*o*/String strAddr, /*o*/Boolean iConnected);
	//获取指定的名称为strSvrName的服务器的地址和连接状态，成功返回1，否则返回0
	public native int GetServerInfo(/*i*/String strSvrName, /*o*/String strAddr, /*o*/Boolean iConnected);
	
	static {
		System.loadLibrary("PIInterface");
	}

}
