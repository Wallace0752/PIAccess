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
		//ConnectServer@
		System.out.println("Connect Test£¡");
		int result = piDb.ConnectServer("127.0.0.1","XJ");
		//System.out.println(result);
		//~
		
		//GetServerInfo@
		String addr = new String();
		Boolean bConn = new Boolean(false);		
		piDb.GetServerInfo("192.168.1.110", addr, bConn);
		System.out.println("\nname:192.168.1.110"+
				"\naddr:"+addr+
				"\nConnected:"+bConn);
		//~
		//SetDefaultServer@
		piDb.SetDefaultServer("127.0.0.1");
		//~
		//GetDefaultServerInfo@
		String name = new String();
		bConn = new Boolean(false);		
		piDb.GetDefaultServerInfo(name, addr, bConn);
		System.out.println("\nname:"+name+
				"\naddr:"+addr+
				"\nConnected:"+bConn);
		//~
		
		if(result==1)
		{
		//FindPointNumber@
		System.out.println("FindPointTest:");
		//System.out.println("CDT158 Number:"+piDb.FindPointNumber("CDT158"));
		System.out.println("String Number:"+piDb.FindPointNumber("bae9cf24-c8b3-46c0-ad5d-a64df2174ed9"));
		System.out.println();
		//~
		//GetSingleSNData@
		System.out.println("GetSingleSNData:");
		Tag tg = new Tag();
		//tg.pointnum = 3;
		tg.tagname = "Test2";
		piDb.GetSingleSNData(tg);
		System.out.println("CDT158 info:"+
				"name:"+tg.tagname+"\n"+
				"number:"+tg.pointnum+"\n"+
				"descriptor:"+tg.descriptor+"\n"+
				"unit:"+tg.engunit+"\n"+
				"Pt Type"+tg.pt_typex+"\n"+
				"rval:"+tg.rval+"\n"+
				"ival:"+tg.ival+"\n"+
				"bval:"+tg.bval+"\n"+
				"istat:"+tg.istat+"\n"+
				"strstat:"+tg.strstat+"\n"+
				"flags:"+tg.flags+"\n"+
				"timedate:"+tg.timedate+"\n"+
				"Calendar:"+String.format("%1$tF %1$tT", tg.ts));
		System.out.println();
		//~
		//GetArraySNData@
		System.out.println("GetArraySNData:");
		Tag[] tgarray =new Tag[3];
		for(int i=0;i<3;i++)
		{
			tgarray[i] = new Tag();
		}
		tgarray[0].tagname = "CDM158";
		tgarray[1].pointnum = 3;
		tgarray[2].tagname = "SINUSOID";
		piDb.GetArraySNData(tgarray);
		for(int i=0;i<3;i++)
		{
			System.out.println("Point info:"+"\n"+
					"name:"+tgarray[i].tagname+"\n"+
					"number:"+tgarray[i].pointnum+"\n"+
					"unit:"+tgarray[i].engunit+"\n"+
					"Pt Type"+tgarray[i].pt_typex+"\n"+
					"rval:"+tgarray[i].rval+"\n"+
					"ival:"+tgarray[i].ival+"\n"+
					"bval:"+tgarray[i].bval+"\n"+
					"istat:"+tgarray[i].istat+"\n"+
					"strstat:"+tgarray[i].strstat+"\n"+
					"flags:"+tgarray[i].flags+"\n"+
					"timedate:"+tgarray[i].timedate+"\n"+
					"Calendar:"+String.format("%1$tF %1$tT", tgarray[i].ts));
		}
		tgarray = null;
		System.out.println();
		//~
		//GetARCount,GetARData@
		System.out.println("GetARCount,GetARData:");
		Calendar ca1 = Calendar.getInstance();
		Calendar ca2 = Calendar.getInstance();
		ca1.set(2011,3,16,16,0,0);
		ca2.set(2011,3,26,17,0,0);
		int count = piDb.GetARCount(ca1, ca2, 3);
		System.out.println("arcive number:"+count);
		Tag[] tgARarray =new Tag[count];
		for(int i=0;i<count;i++)
		{
			tgARarray[i] = new Tag();
		}
		piDb.GetARData(ca1, ca2, 3,tgARarray);
		for(int i=0;i<count;i++)
		{
			System.out.println("CDT158 info:"+
					"name:"+tgARarray[i].tagname+"\n"+
					"number:"+tgARarray[i].pointnum+"\n"+
					"unit:"+tgARarray[i].engunit+"\n"+
					"Pt Type"+tgARarray[i].pt_typex+"\n"+
					"descriptor:"+tgARarray[i].descriptor+"\n"+
					"rval:"+tgARarray[i].rval+"\n"+
					"ival:"+tgARarray[i].ival+"\n"+
					"bval:"+tgARarray[i].bval+"\n"+
					"istat:"+tgARarray[i].istat+"\n"+
					"strstat:"+tgARarray[i].strstat+"\n"+
					"flags:"+tgARarray[i].flags+"\n"+
					"timedate:"+tgARarray[i].timedate+"\n"+
					"Calendar:"+String.format("%1$tF %1$tT", tgARarray[i].ts));
//					"Calendar:"+tgARarray[i].ts.get(Calendar.YEAR)+"-"+
//					tgARarray[i].ts.get(Calendar.MONTH)+"-"+
//					tgARarray[i].ts.get(Calendar.DAY_OF_MONTH)+" "+
//					tgARarray[i].ts.get(Calendar.HOUR_OF_DAY)+":"+
//					tgARarray[i].ts.get(Calendar.MINUTE)+":"+
//					tgARarray[i].ts.get(Calendar.SECOND)+";");
		}
		System.out.println();
		//~
		//GetArrayARData@
		System.out.println("GetArrayARData:");
		Calendar caa1 = Calendar.getInstance();
		Calendar caa2 = Calendar.getInstance();
		Calendar caa3 = Calendar.getInstance();
		caa1.set(2011,3,7,2,0,0);
		caa2.set(2011,3,7,3,0,0);
		caa3.set(2011,3,7,4,0,0);
		Calendar[] carray = new Calendar[3];
		carray[0] = caa1;
		carray[1] = caa2;
		carray[2] = caa3;
		Tag[] tgtimeTest =new Tag[3];
		for(int i=0;i<3;i++)
		{
			tgtimeTest[i] = new Tag();
		}
		piDb.GetArrayARData(carray, 3, tgtimeTest);
		for(int i=0;i<3;i++)
		{
			System.out.println("CDT158 info:"+
					"name:"+tgtimeTest[i].tagname+"\n"+
					"number:"+tgtimeTest[i].pointnum+"\n"+
					"unit:"+tgtimeTest[i].engunit+"\n"+
					"Pt Type"+tgtimeTest[i].pt_typex+"\n"+
					"rval:"+tgtimeTest[i].rval+"\n"+
					"ival:"+tgtimeTest[i].ival+"\n"+
					"bval:"+tgtimeTest[i].bval+"\n"+
					"istat:"+tgtimeTest[i].istat+"\n"+
					"strstat:"+tgtimeTest[i].strstat+"\n"+
					"flags:"+tgtimeTest[i].flags+"\n"+
					"timedate:"+tgtimeTest[i].timedate+"\n"+
					"Calendar:"+String.format("%1$tF %1$tT", tgtimeTest[i].ts));
		}
		System.out.println();
		//~
		}
	}
	
	public void testGet()
	{
		
	}
	
	public static void main(String[] args)
	{
		junit.textui.TestRunner.run(PiDbTest.class);
	}
}
