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
//		//FindPointNumber@
//		System.out.println("FindPointTest:");
//		System.out.println("CDT158 Number:"+piDb.FindPointNumber("CDT158"));
//		System.out.println();
//		//~
		//GetSingleSNData@
		System.out.println("GetSingleSNData:");
		Tag tg = new Tag();
		tg.pointnum = 3;
		piDb.GetSingleSNData(tg);
		System.out.println("CDT158 info:"+
				"name:"+tg.tagname+"\n"+
				"number:"+tg.pointnum+"\n"+
				"unit:"+tg.engunit+"\n"+
				"Pt Type"+tg.pt_typex+"\n"+
				"rval:"+tg.rval+"\n"+
				"ival:"+tg.ival+"\n"+
				"bval:"+tg.bval+"\n"+
				"flags:"+tg.flags+"\n"+
				"timedate:"+tg.timedate+"\n"+
				"Calendar:"+tg.ts.get(Calendar.YEAR)+"-"+
				tg.ts.get(Calendar.MONTH)+"-"+
				tg.ts.get(Calendar.DAY_OF_MONTH)+" "+
				tg.ts.get(Calendar.HOUR_OF_DAY)+":"+
				tg.ts.get(Calendar.MINUTE)+":"+
				tg.ts.get(Calendar.SECOND)+":"+
				tg.ts.get(Calendar.MILLISECOND)+";");
		System.out.println();
		//~
//		//GetArraySNData@
//		System.out.println("GetArraySNData:");
//		Tag[] tgarray =new Tag[3];
//		for(int i=0;i<3;i++)
//		{
//			tgarray[i] = new Tag();
//		}
//		tgarray[0].tagname = "CDM158";
//		tgarray[1].pointnum = 3;
//		tgarray[2].tagname = "SINUSOID";
//		piDb.GetArraySNData(tgarray);
//		for(int i=0;i<3;i++)
//		{
//			System.out.println("CDT158 info:"+
//					"name:"+tgarray[i].tagname+"\n"+
//					"number:"+tgarray[i].pointnum+"\n"+
//					"unit:"+tgarray[i].engunit+"\n"+
//					"Pt Type"+tgarray[i].pt_typex+"\n"+
//					"rval:"+tgarray[i].rval+"\n"+
//					"ival:"+tgarray[i].ival+"\n"+
//					"bval:"+tgarray[i].bval+"\n"+
//					"flags:"+tgarray[i].flags+
//					"timedate:"+tgarray[i].timedate+
//					"Calendar:"+tgarray[i].ts);
//		}
//		tgarray = null;
//		System.out.println();
//		//~
//		//GetARCount,GetARData@
//		System.out.println("GetARCount,GetARData:");
//		Calendar ca1 = Calendar.getInstance();
//		Calendar ca2 = Calendar.getInstance();
//		ca1.set(2011,4,7,0,20,0);
//		ca2.set(2011,4,7,0,40,0);
//		int count = piDb.GetARCount(ca1, ca2, 3);
//		System.out.println("arcive number:"+count);
//		Tag[] tgARarray =new Tag[count];
//		for(int i=0;i<count;i++)
//		{
//			tgARarray[i] = new Tag();
//		}
//		piDb.GetARData(ca1, ca2, 3,tgARarray);
//		for(int i=0;i<count;i++)
//		{
//			System.out.println("CDT158 info:"+
//					"name:"+tgARarray[i].tagname+"\n"+
//					"number:"+tgARarray[i].pointnum+"\n"+
//					"unit:"+tgARarray[i].engunit+"\n"+
//					"Pt Type"+tgARarray[i].pt_typex+"\n"+
//					"rval:"+tgARarray[i].rval+"\n"+
//					"ival:"+tgARarray[i].ival+"\n"+
//					"bval:"+tgARarray[i].bval+"\n"+
//					"flags:"+tgARarray[i].flags+
//					"timedate:"+tgARarray[i].timedate+
//					"Calendar:"+tgARarray[i].ts);
//		}
//		System.out.println();
//		//~
//		//GetArrayARData@
//		System.out.println("GetArrayARData:");
//		Calendar caa1 = Calendar.getInstance();
//		Calendar caa2 = Calendar.getInstance();
//		Calendar caa3 = Calendar.getInstance();
//		caa1.set(2011,4,7,2,0,0);
//		caa2.set(2011,4,7,3,0,0);
//		caa3.set(2011,4,7,4,0,0);
//		Calendar[] carray = new Calendar[3];
//		carray[0] = caa1;
//		carray[1] = caa2;
//		carray[2] = caa3;
//		Tag[] tgtimeTest =new Tag[3];
//		for(int i=0;i<3;i++)
//		{
//			tgtimeTest[i] = new Tag();
//		}
//		piDb.GetArrayARData(carray, 3, tgtimeTest);
//		for(int i=0;i<3;i++)
//		{
//			System.out.println("CDT158 info:"+
//					"name:"+tgtimeTest[i].tagname+"\n"+
//					"number:"+tgtimeTest[i].pointnum+"\n"+
//					"unit:"+tgtimeTest[i].engunit+"\n"+
//					"Pt Type"+tgtimeTest[i].pt_typex+"\n"+
//					"rval:"+tgtimeTest[i].rval+"\n"+
//					"ival:"+tgtimeTest[i].ival+"\n"+
//					"bval:"+tgtimeTest[i].bval+"\n"+
//					"flags:"+tgtimeTest[i].flags+
//					"timedate:"+tgtimeTest[i].timedate+
//					"Calendar:"+tgtimeTest[i].ts);
//		}
//		System.out.println();
//		//~
		
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
//		//获取一串时间测试
//		Calendar ca1 = Calendar.getInstance();
//		Calendar ca2 = Calendar.getInstance();
//		Calendar ca3 = Calendar.getInstance();
//		ca1.set(2011,4,7,2,0,0);
//		ca2.set(2011,4,7,3,0,0);
//		ca3.set(2011,4,7,4,0,0);
//		Calendar[] carray = new Calendar[3];
//		carray[0] = ca1;
//		carray[1] = ca2;
//		carray[2] = ca3;
//		Tag[] tg =new Tag[3];
//		for(int i=0;i<3;i++)
//		{
//			tg[i] = new Tag();
//		}
//		piDb.GetArrayARData(carray, 3, tg);
//		for(int i=0;i<3;i++)
//		{
//			System.out.println(tg[i].rval);
//		}
//		System.out.println(piDb.FindPointNumber("CDT158"));
//		PIvaluetype enu ;//PI_Type_char
////		enu = PIvaluetype.PI_Type_bad;
////		System.out.println(enu);
//		enu = piDb.EnumTest();
//		System.out.println(enu);

//		piDb.GetARCount(tmStart, tmEnd, PtNumber)
		
		
	}
	
	public static void mani(String[] args)
	{
		junit.textui.TestRunner.run(PiDbTest.class);
	}
}
