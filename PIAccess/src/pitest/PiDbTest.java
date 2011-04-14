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
		//FindPointNumber@
		System.out.println("FindPointTest:");
		System.out.println("CDT158 Number:"+piDb.FindPointNumber("CDT158"));
		System.out.println();
		//~
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
				"strstat:"+tg.istat+"\n"+
				"strstat:"+tg.strstat+"\n"+
				"flags:"+tg.flags+"\n"+
				"timedate:"+tg.timedate+"\n"+
				"Calendar:"+tg.ts.get(Calendar.YEAR)+"-"+
				tg.ts.get(Calendar.MONTH)+"-"+
				tg.ts.get(Calendar.DAY_OF_MONTH)+" "+
				tg.ts.get(Calendar.HOUR_OF_DAY)+":"+
				tg.ts.get(Calendar.MINUTE)+":"+
				tg.ts.get(Calendar.SECOND)+";");
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
					"Calendar:"+tgarray[i].ts.get(Calendar.YEAR)+"-"+
					tgarray[i].ts.get(Calendar.MONTH)+"-"+
					tgarray[i].ts.get(Calendar.DAY_OF_MONTH)+" "+
					tgarray[i].ts.get(Calendar.HOUR_OF_DAY)+":"+
					tgarray[i].ts.get(Calendar.MINUTE)+":"+
					tgarray[i].ts.get(Calendar.SECOND)+";");
		}
		tgarray = null;
		System.out.println();
		//~
		//GetARCount,GetARData@
		System.out.println("GetARCount,GetARData:");
		Calendar ca1 = Calendar.getInstance();
		Calendar ca2 = Calendar.getInstance();
		ca1.set(2011,4,7,0,20,0);
		ca2.set(2011,4,7,0,40,0);
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
					"rval:"+tgARarray[i].rval+"\n"+
					"ival:"+tgARarray[i].ival+"\n"+
					"bval:"+tgARarray[i].bval+"\n"+
					"istat:"+tgARarray[i].istat+"\n"+
					"strstat:"+tgARarray[i].strstat+"\n"+
					"flags:"+tgARarray[i].flags+"\n"+
					"timedate:"+tgARarray[i].timedate+"\n"+
					"Calendar:"+tgARarray[i].ts.get(Calendar.YEAR)+"-"+
					tgARarray[i].ts.get(Calendar.MONTH)+"-"+
					tgARarray[i].ts.get(Calendar.DAY_OF_MONTH)+" "+
					tgARarray[i].ts.get(Calendar.HOUR_OF_DAY)+":"+
					tgARarray[i].ts.get(Calendar.MINUTE)+":"+
					tgARarray[i].ts.get(Calendar.SECOND)+";");
		}
		System.out.println();
		//~
		//GetArrayARData@
		System.out.println("GetArrayARData:");
		Calendar caa1 = Calendar.getInstance();
		Calendar caa2 = Calendar.getInstance();
		Calendar caa3 = Calendar.getInstance();
		caa1.set(2011,4,7,2,0,0);
		caa2.set(2011,4,7,3,0,0);
		caa3.set(2011,4,7,4,0,0);
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
					"Calendar:"+tgtimeTest[i].ts.get(Calendar.YEAR)+"-"+
					tgtimeTest[i].ts.get(Calendar.MONTH)+"-"+
					tgtimeTest[i].ts.get(Calendar.DAY_OF_MONTH)+" "+
					tgtimeTest[i].ts.get(Calendar.HOUR_OF_DAY)+":"+
					tgtimeTest[i].ts.get(Calendar.MINUTE)+":"+
					tgtimeTest[i].ts.get(Calendar.SECOND)+";");
		}
		System.out.println();
		//~
//		System.out.println("GetState:");
//		String strState = new String();
//		piDb.GetState(tgtimeTest[1].istat, strState);
//		System.out.println("State:"+strState);
	}
	
	public void testGet()
	{
		
	}
	
	public static void main(String[] args)
	{
		junit.textui.TestRunner.run(PiDbTest.class);
	}
}
