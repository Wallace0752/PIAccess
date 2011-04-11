package pitest;


import piaccess.PiDb;
import piaccess.Tag;
import piaccess.PIvaluetype;
import junit.framework.TestCase;

import java.util.*;
import java.text.*;


public class PiDbTest extends TestCase {
	public PiDbTest()
	{
		super();
	}
	
	public void test() {
		PiDb piDb = new PiDb();
//		int a = piDb.Get();
//		assertEquals(2, a);
/*		Tag tg;
		tg = piDb.GetSnapShot(13);
//		piDb.Set();
//		piDb.Get();
		System.out.println(tg.getValue());
		System.out.println(tg.getStat());*/
		
//		Tag tgEx = new Tag();
//		tgEx.tagname = "CDT158";
//		piDb.GetSingleSNData(tgEx);
////		System.out.println(tgEx.engunit);
////		System.out.println(tgEx.pt_typex);
//		System.out.println(tgEx.rval);
//		System.out.println(tgEx.ival);
//		System.out.println(tgEx.ts.get(Calendar.YEAR));
//		System.out.println(tgEx.ts.get(Calendar.MONTH));
//		System.out.println(tgEx.ts.get(Calendar.DAY_OF_MONTH));
//		System.out.println(tgEx.ts.get(Calendar.HOUR_OF_DAY));
//		System.out.println(tgEx.ts.get(Calendar.MINUTE));
//		System.out.println(tgEx.ts.get(Calendar.SECOND));
//		
		//SnapShot类测试
//		Calendar ca1 = Calendar.getInstance();
//		Calendar ca2 = Calendar.getInstance();
//		ca1.set(2011,4,7,0,0,0);
//		ca2.set(2011,4,7,10,10,0);
//		int count = piDb.GetARCount(ca1, ca2, 3);
//		Tag[] tg =new Tag[count];
//		for(int i=0;i<count;i++)
//		{
//			tg[i] = new Tag();
//		}
		
//		tg[0].tagname = "CDM158";
//		tg[1].tagname = "CDT158";
//		tg[2].tagname = "SINUSOID";
//		piDb.GetARData(ca2, ca1, 3, tg);
//		for(int i=0;i<count;i++)
//		{
//			Date tasktime=tg[i].ts.getTime();   
//			//设置日期输出的格式   
//			SimpleDateFormat df=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//			System.out.println(df.format(tasktime)); 
//			System.out.println(tg[i].rval);
//			System.out.println(tg[i].ival);
//			System.out.println();
//			 
//		}
//		Date tasktime=ca1.getTime();   
//		//设置日期输出的格式   
//		SimpleDateFormat df=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//		System.out.println(df.format(tasktime)); 
		//SnapShot类测试结束
		
/*		int pt = 0;
		piDb.FindPointNumber("SINUSOIDU", pt);
		System.out.println(pt);*/
//		Calendar ca1 = Calendar.getInstance();
//		Calendar ca2 = Calendar.getInstance();
//		ca1.set(2011,4,7,0,0,0);
//		ca2.set(2011,4,7,10,10,0);
//		
//		int count = piDb.GetARCount(ca1, ca2, 3);
//		System.out.println(count);
		//piDb.DateTest(ca, ca);
//		System.out.println(ca.get(1));
//		System.out.println(ca.get(Calendar.MONTH));
//		System.out.println(ca.get(Calendar.DAY_OF_MONTH));
//		System.out.println(ca.get(Calendar.HOUR_OF_DAY));
//		System.out.println(ca.get(Calendar.MINUTE));
//		System.out.println(ca.get(Calendar.SECOND));
		//获取一串时间测试
		Calendar ca1 = Calendar.getInstance();
		Calendar ca2 = Calendar.getInstance();
		Calendar ca3 = Calendar.getInstance();
		ca1.set(2011,4,7,2,0,0);
		ca2.set(2011,4,7,3,0,0);
		ca3.set(2011,4,7,4,0,0);
		Calendar[] carray = new Calendar[3];
		carray[0] = ca1;
		carray[1] = ca2;
		carray[2] = ca3;
		Tag[] tg =new Tag[3];
		for(int i=0;i<3;i++)
		{
			tg[i] = new Tag();
		}
		piDb.GetArrayARData(carray, 3, tg);
		for(int i=0;i<3;i++)
		{
			System.out.println(tg[i].rval);
		}
		System.out.println(piDb.FindPointNumber("CDT158"));
		PIvaluetype enu ;//PI_Type_char
//		enu = PIvaluetype.PI_Type_bad;
//		System.out.println(enu);
		enu = piDb.EnumTest();
		System.out.println(enu);
		
		
	}
	
	public static void mani(String[] args)
	{
		junit.textui.TestRunner.run(PiDbTest.class);
	}
}
