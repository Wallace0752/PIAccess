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
//	public Tag TagPoint;

//	public int iTest;
	
//	public native int Get();
//	public native int Set();
//	public native Tag GetSnapShot(int PointNumber);
	//通过标签点的名称获得标签点的编号,返回值为标签点编号。若没有找到，则返回-1
	public native int FindPointNumber(/*i*/String TagName);
/*	//通过标签点的编号获取标签点的单个快照数据，该数据位实数类型，返回值1表示成功
	public native int GetSNRealByNumber(iint PointNumber, oTag TagPoint);
	//通过标签点的名称获取标签点的单个快照数据，该数据为实数类型，返回值1表示成功
	public native int GetSNRealByName(iString TagName, oTag TagPoint);*/
	//获取传入TagPoint的数据。传入时需要制定Tag名称或者Tag编号。若同时指定，则Tag名称优先
	public native int GetSingleSNData(/*i,o*/Tag TagPoint);
	//获取传入的TagPtArray的数据，传入时需要制定Tag名称或者Tag编号。若同时指定，则Tag名称优先
	public native int GetArraySNData(/*i,o*/Tag[] TagPtArray);
	//日期传入与传出测试
	public native void DateTest(Calendar inCal, Calendar outCal);
	//测试JNI对于枚举类型的读取
	public native PIvaluetype EnumTest();
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
	
	
	
	static {
		System.loadLibrary("PIInterface");
	}
/*	public static void main(String[] args)
	{
//		HelloWorld CCall = new HelloWorld();
		PiDb pb = new PiDb();
		Tag tg = pb.GetSnapShot();
		System.out.println(tg.getValue());
		
	}*/
}
