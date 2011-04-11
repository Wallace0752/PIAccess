/*-----------------------------------------------------------------------------

$Archive: /PI/freeze/intel/piapi/pidefs.h $

-------------------------------------------------------------------------------

Copyright (c) 1994-2001 OSI Software, Inc. All rights reserved.
Unpublished - rights reserved under the copyright law of the United States.

USE OF A COPYRIGHT NOTICE IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
OR DISCLOSURE.

THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF
OSI SOFTWARE, INC.  USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED WITHOUT
THE PRIOR EXPRESS WRITTEN PERMISSION OF OSI SOFTWARE, INC.

RESTRICTED RIGHTS LEGEND
Use, duplication, or disclosure by the Government is subject to restrictions
as set forth in subparagraph (c)(1)(ii) of the Rights in Technical Data and
Computer Software clause at DFARS 252.227.7013

OSI Software, Inc.
777 Davis Street, Suite 250, San Leandro CA 94577

-------------------------------------------------------------------------------

Description:
    General PI System data type definitions.

-------------------------------------------------------------------------------

History:

$Log: /PI/freeze/intel/piapi/pidefs.h $

23    11/12/03 2:07p Ssortland
Copied over to freeze from PI-API 1.3.9.1 

8     9/09/02 9:58a Ray
Comment out ENABLESTACKPROTECTION.

7     8/12/02 1:17p Ray
Enable ENABLESTACKPROTECTION.

6     8/12/02 11:26a Jon
Protocol trace work. Stack protection macros.

5     8/09/02 5:48p Jon
Crash debug tools.

4     02-04-22 10:07 Charlie
For WIN32 also need to include time.h for time_t definition in
PIGetCurrenttime.

3     4/21/02 11:12a Jon
Replaced C++ '//' comment with c comment.

2     4/19/02 3:20p Jon
Punchlist 2019OSI8

38    1/17/02 4:36p Jon
Punchlist 1705OSI8 parameterize license limits.

37    11/16/01 1:34p Etam
remove "long long" for Solaris definition; otherwise, compiling with
-Xc fails

36    11/07/01 4:55p Jon
Audit work.

35    11/02/01 4:05p Etam
put #ifndef aix around inline void* operator new (size_t, void *p) to
satisfy new compiler

34    11/01/01 10:11p Rulik
Changed enumeration to 0x40000000 to appease Dec-Unix (Maybe...)

33    10/31/01 9:07a Rulik
Added Enumerations for snap/arch Auditing

32    10/25/01 12:02p Rulik
Reordered DB enumeration by DB type and added DBsecurity

31    10/18/01 11:32p Rulik
PIdb enumeration as powers of 2 - to allow auditing specification for
individual DB

30    10/17/01 6:35p Jon
Audits.

29    9/28/01 1:58p Jon
Unix port. Punchlist 1200OSI8

28    9/14/01 4:35p Jon

27    6/07/01 11:08a Jon
Unix Builds. Punchlist 12000OSI8

26    5/23/01 2:31p Jon
Unix port. Punch list 1200OSI8.

25    5/22/01 2:10p Jon
Unix port. Punchlist 1200OSI8

24    5/21/01 4:43p Jon
Unix port. Punchlist 1200OSI8

23    8/09/00 16:54 Rulik
added summary codes for pctgood by time and values

22    3/06/00 9:24a Ken
Added boundary condition enumeration for ModuleDB values calls

21    2/29/00 2:40p Ken
Added enum support for Module Database Value calls: eventprevious,
eventnext

20    2/04/:0 3:36p Charlie
MAXUINT32 needs UL type, not L.

19    1/31/00 2:53p Richard
Migration to Standard Library Iostreams.

18    12/10/99 11:40a Richard
Added enum support for Mode 4 piar_value calls.

17    10/07/99 2:10p Richard
Merge from 3.2.357.17.

15    5/19/99 10:44a Richard
Removed Intellution as default build option.

14    3/25/99 12:30p Richard
Added support for Intellution specific requirements.

16    8/23/99 11:14a Piadmin
v15 comment changed to use words, not comment characters.

15    8/23/99 8:16a Piadmin
Changed header comments from C++ to C style.

14    6/13/99 1:09p Richard
Merge from 3.2.357.9.

15    5/19/99 10:44a Richard
Removed Intellution as default build option.

14    3/25/99 12:30p Richard
Added support for Intellution specific requirements.

12    10/05/98 1:40p Richard
Added pragma to disable warning about new operator and exception
handling.

11    9/21/98 11:48a Bgallardo

10    8/07/98 1:04p Charlie
changed second int64 def to uint64

9     8/07/98 12:18p Charlie
Added check to see if MAXINT32/MAXUINT16 were already defined.

8     7/30/98 9:36a Ray
add definition of typdef "bool" for vms.

   18 Jan 93 BV  Original version.
   25 Jun 93 RAB Added pistatus.
   02 Jul 93 RAB Changed pistatus to an enum and moved into pistatus.h
   26 Jul 93 MDH removed "signed" from int8, removed "long double" -
                                       warnings from H-P C++ compiler
   27 Jul 93 MDH add MIN* and MAX* #define's for 8,16,32 bit typedefs
   10 Sep 93 BV  add global operator new for specific object placement
   14 Sep 93 BV  include <stdlib.h>
   15 Sep 93 BV  bugfix: include <stddef.h> instead of <stdlib.h>
   15 Sep 93 ET  put #ifdef around #include <stddef.h>
   01 Nov 93 MDH moved pistatus.h include after typedef for bool
   08 Aug 94 RP  added PI_Data_Type enumeration
   16 Aug 94 RP  added MAX_LONG_NAME_LEN (from VAX)
   24 Aug 94 RP  moved type definitions to pitypes.h
   14 Sep 94 jhp removed ET fix of 15 sep 93--not sure why ET did this
   10 Nov 94 RAB modified MININT32 to accomodate HP-UX CC bug.
   06 Dec 94 jhp typedef bool rather than #define, breaks some Microsoft NT
                 header files.
   23 Jan 94 RAB added endian defines.
   22 May 95 JY  added PATHSEPARATOR, DEFDATAPATH, PIPARAMSPATH, PIPARAMSFILE
    5 Oct 95 RP  Added PIsleep macro
   17 Oct 95 RCV Moved PIsleep macros to left margin, changed VAX to vax
   10 Nov 95 HKS Declared PIPROC on WIN32 to include WINAPI for _stdcall
   14 Nov 95 HKS Added PIsleep definition (NULL) for Windows to avoid inclusion
                 of unistd.h
    1 Dec 95 HKS Conditionally include new(size_t,void *) implementation.
    4 Dec 95 RAB Previous Change Breaks PI 3.0 on NT since we don't use
		 MFC - #defined check is changed to use _MFC_VER as a basis
   18 Mar 96 jhp Replace bool with pibool--compatability problem with some
                 compilers.
   29-Mar-96 RP Added PIcompoper and PIarcoper
   21-Feb-97 jhp Define _BIG_ENDIAN and _LITTLE_ENDIAN on appropriate machines
                 if not already defined. This fixes a piut_passivate ( float64 )
                 and a piut_activate ( float64 ) bug on AIX. The passivates were
                 relying on the built in _BIG_ENDIAN and this is not defined on AIX.

-----------------------------------------------------------------------------*/
#ifndef PI__DEFINITIONS
#define PI__DEFINITIONS


/*----------------------------------------------- includes ------------------*/
#include <stddef.h>          /* for size_t */
/*----------------------------------------------- typedefs ------------------*/

#ifdef UNICODE
typedef wchar_t TCHAR;                        /* text characters */
#else
typedef char TCHAR;
#endif

#if defined( hppa ) || defined( sparc ) || defined( rs6000 ) || defined(aix) || defined (__HHW_BIG_ENDIAN__)
#define PI_BIGENDIAN
#ifndef _BIG_ENDIAN
#define _BIG_ENDIAN
#endif
#else
#define PI_LITTLEENDIAN
#ifndef _LITTLE_ENDIAN
#define _LITTLE_ENDIAN
#endif
#endif

#ifdef WIN32

   typedef char             int8;                  /* integers */
   typedef short            int16;
   typedef long             int32;
   typedef __int64          int64;

   typedef unsigned char    uint8;                  /* unsigned */
   typedef unsigned short   uint16;
   typedef unsigned long    uint32;
   typedef unsigned __int64 uint64;

#elif defined (aix)  /* aix defines int8, etc. */

#include <sys/inttypes.h>
   typedef u_int8 uint8;                  /* unsigned */
   typedef u_int16 uint16;
   typedef u_int32 uint32;
   typedef u_int64 uint64;

   typedef unsigned int     DWORD;

#elif defined(osf1) || defined(hp64)

   typedef char             int8;                  /* integers */
   typedef short            int16;
   typedef int              int32;
   typedef long             int64;

   typedef unsigned char    uint8;                  /* unsigned */
   typedef unsigned short   uint16;
   typedef unsigned int     uint32;
   typedef unsigned long    uint64;

   typedef unsigned int     DWORD;

#else  /* other Unix */

   typedef char               int8;                  /* integers */
   typedef short              int16;
   typedef long               int32;
#ifdef solaris
   typedef long               int64;
#else
   typedef long long          int64;
#endif

   typedef unsigned char      uint8;                  /* unsigned */
   typedef unsigned short     uint16;
   typedef unsigned long      uint32;
#ifdef solaris
   typedef unsigned long      uint64;
#else
   typedef unsigned long long uint64;
#endif
   typedef unsigned long      DWORD;

#endif


typedef float          float32;               /* floats */
typedef double         float64;


/* typedef long double    float80; */

/*  18 mar 96 jhp following definition obsoletes bool typedef  */
typedef char pibool;
/* Following is to support MFC Version 4.2 Delivered with Visual C++ 4.2 */
#if !defined(_MFC_VER) || (_MFC_VER < 0x420)
#define true           ((pibool)1)
#define false          ((pibool)0)
#endif

/* 29-jan-98 lfm    add typedef bool for vms */
#if defined(vms)
typedef char bool;
#endif

/* these definitions are consistent with the adopted ANSI/ISO C++
   definition of the new type bool
   */
/* #ifndef __GNUG__ bool is defined in gnu c++ */
/* typedef char bool;   jhp  6dec94  */
/*#define true           ((bool)1)
#define false          ((bool)0)*/
/* following typedef has been replaced by defines above. */
/* typedef int            bool; */                 /* boolean */
/*#endif */


/* Changed to _WINDOWS from _DOS below to avoid MFC problem 30aug95 hks */
#if defined (_WINDOWS) && (!defined (WIN32) && !defined(_WIN32))
#include <windows.h>     /*  WINAPI definition  */
#define PIPTR _far
#define PIPROC WINAPI   /* WINAPI = far pascal */
#elif (defined(WIN32) || defined(_WIN32))
#include <windows.h>     /*  WINAPI definition  */
#define PIPTR
#define PIPROC WINAPI   /* WINAPI = _stdcall */
#else
#define PIPTR
#define PIPROC
#endif

/* general file descriptor definition */
#ifdef WIN32
#define PIFILEHANDLE int /* soon to be HANDLE with true WIN32 API */
#else
#define PIFILEHANDLE int
#endif

#define MININT8 -128
#define MAXINT8 127
#define MININT16 -32768
#define MAXINT16 32767
#define MININT32 (-2147483647L - 1)
#ifndef MAXINT32  /* 98/08/07 */
#define MAXINT32 2147483647L
#endif
#define MAXUINT8 255
#ifndef MAXUINT16  /* 98/08/07 */
#define MAXUINT16 65535
#endif
#if defined(osf1) || defined(hp64)
#define MAXUINT32 4294967295U
#else
#define MAXUINT32 4294967295UL
#endif

#define MAX_LONG_NAME_LEN (80)

#ifdef WIN32
#define PATHSEPARATOR (TCHAR) '\\'
#define PIPARAMSPATH "\\system\\"
#define PIPARAMSFILE "\\system\\piparams.default"
#define DEFDATAPATH "c:\\PI\\dat\\"
#else
#define PATHSEPARATOR (TCHAR) '/'
#define PIPARAMSPATH "/etc/"
#define PIPARAMSFILE "/etc/piparams.default"
#define DEFDATAPATH "/usr/PI/dat/"
#endif

#define VP_ROOT 0
#define VP_PIADMIN 1

/*----- PIarcmode -------------------------------------------------------------
   Archive Data Access Modes
-----------------------------------------------------------------------------*/
enum PIarcmode
{
   eventprevious = -3,     /* previous value, not including query date */
   eventinterpbefore = -2, /* equivalent to PI 2.x - Mode 4 */
   eventbefore = -1,       /* equivalent to PI 2.x - Mode 1 */
   eventinterp = 0,        /* equivalent to PI 2.x - Mode 3 */
   eventafter = 1,         /* equivalent to PI 2.x - Mode 2 */
   eventnext = 3           /* next value, not including query date */
};

/*----- PIsummarycode ---------------------------------------------------------
   Archive summary method modes.
-----------------------------------------------------------------------------*/
enum PIsummarycode
{
   PIarctotal,
   PIarcminimum,
   PIarcmaximum,
   PIarcstdev,
   PIarcrange,
   PIarcaverage,
   PIarcmean,
   PIarcPctTimeGood,
   PIarcPctValGood
};
enum PIarcflag
{
   ARCflag_all=1,
   ARCflag_numb=2,
   ARCflag_time=4,
   ARCflag_even=8,
   ARCflag_filter=16,
   ARCflag_mark=32,
   ARCflag_comp=64
};

/* archive and general purpose enums */
enum PIcompoper {EQ, NE, GT, GE, LT, LE};
enum PIarcoper {ARC_read, ARC_write, ARC_delete, ARC_create, ARC_shift};
/*
 BoundaryTypeConstants for SDK
*/
enum PIarcBoundaryTypeConstants{
   piarcbtInside     = 0,          /* values inside the start and end times */
   piarcbtOutside    = 1,          /* values outside the start and end times (error if none) */
   piarcbtInterp     = 2,          /* values interpolated at the start and times */
   piarcbtAuto       = 3           /* values inside of step tag, else interpolated */
};


/*  Database enum  */
enum PIDBNAMES {
   PIdb_Null=0,
   PIdb_Point=1,
   PIdb_Digital=2,
   PIdb_Attribset=4,
   PIdb_Context=8,
   PIdb_PointClass=0x10,
   PIdb_User=0x20,
   PIdb_Group=0x40,
   PIdb_Trust=0x80,
   PIdb_Module=0x100,
   PIdb_Heading=0x200,
   PIdb_TransferRecord=0x400,
   PIdb_Campaign=0x800,
   PIdb_Batch=0x1000,
   PIdb_Unit=0x2000,
   PIdb_Snapshot=0x10000000,
   PIdb_Archive=0x20000000,
   PIdb_DBsecurity=0x40000000
};
enum AuditAction {
   AUDITADD,
   AUDITEDIT,
   AUDITREMOVE,
   AUDITEDITATTEMPT,
   AUDITREMOVEATTEMPT
};


/*----------------------------------------------- macros and inlines ---------*/
#ifdef vms
#define PIsleep(x) {float wait_time = 0.10 * x; lib$wait ( &wait_time );}
#elif defined( WIN32 )
#define PIsleep(x) {Sleep ( x*1000 );}
#elif defined( _WINDOWS )
#define PIsleep(x)
#else
#include <unistd.h>
#define PIsleep(x) {sleep ( x );}
#endif
/*
 get time_t current utc time. Uses CRT on Unix
 WIN32 calls on NT to avoid inconsistencies with NT
 and the CRT. For exaple, when tz is set, WIN32 CRT calls
 have different behavior. This function also avoids dependency
 on pitime.hxx
*/
#ifdef __cplusplus
#ifdef WIN32
#include <time.h>
inline time_t PIGetCurrentTime( time_t *pretVal )
{
   double dTime;
   time_t val;
   SYSTEMTIME st;
   GetSystemTime( &st );
   if ( st.wMonth <= 2 )
      dTime = ( (1461L * (st.wYear - 1L)/4L) + (153L * (st.wMonth + 13L) / 5L) + st.wDay ) - 719606L;
   else
      dTime = ( (1461L * (int32) st.wYear / 4L) +          (153L * ((int32) st.wMonth +1L) / 5L) + (int32) st.wDay ) - 719606L;
   dTime = ((dTime * 24 + st.wHour) * 60 + st.wMinute) * 60 + st.wSecond;
   val = (time_t)(dTime);
   if ( pretVal )
      *pretVal = val;
   return val;
}
#else
#include <time.h>
inline time_t PIGetCurrentTime( time_t *pretVal )
{
   time_t val = time(0);
   if ( pretVal ) *pretVal=val;
   return val;
}
#endif
#endif
#ifdef __cplusplus
#if(!defined(_MFC_VER) || (_MFC_VER < 0x400))
#ifndef __PLACEMENT_NEW_INLINE
/*----- placement operator new ----------------------------------------
 * This operator new places the object allocated at the passed address.
 * 10 Sep 93 BV  See C++ ARM page 279.
 *---------------------------------------------------------------------*/
#define __PLACEMENT_NEW_INLINE
#ifdef WIN32
#pragma warning(disable:4291)  /* get rid of the Microsoft heave */
#endif

#ifndef aix   /* otherwise, new compiler complains about declaration conflict */
inline void* operator new (size_t, void *p) {
   return p;
}
#endif

#endif /* __PLACEMENT_NEW_INLINE */
#endif /* _MFC_VER */
#endif /* __cplusplus */



#ifdef WIN32

// #define ENABLESTACKPROTECTION

#ifdef ENABLESTACKPROTECTION

#define PAGEMASK 0xFFFFF000
#define PAGESIZE 0x00001000

#define PROTECTSTACK() __asm  \
{ \
_asm mov ebx,esp                 /* keep track of the current esp*/ \
_asm and esp,PAGEMASK            /* round down to nearest pageboundary     */ \
_asm sub esp,PAGESIZE            /* move down one more page*/ \
_asm mov [esp],ebx               /* store the old esp (it is in ebx)here   */ \
_asm mov ebx,esp                 /* store this address to protectlater     */ \
_asm sub esp,4                   /* move esp to now point to thenext page  */ \
\
\
_asm push esp                    /* Dummy location for the 4th "out" param  */ \
_asm push PAGE_NOACCESS          /* allow NOACCESS*/ \
_asm push 1                      /* 1 byte (which gets the wholepage)      */ \
_asm push ebx                    /* the stored page to change access*/ \
_asm call dword ptr [VirtualProtect]  /* make the call to change the access */ \
}


#define UNPROTECTSTACK() _asm \
{ \
/* if all is ok, esp should now be just below the protected page*/ \
_asm mov ebx,esp                 /* start here*/ \
_asm add ebx,4                   /* protected page is 4 bytes up*/ \
\
/* make the function call to VirtualProtect.*/ \
_asm push esp                    /* Dummy location for the 4th "out"param  */ \
_asm push PAGE_READWRITE         /* allow NOACCESS*/ \
_asm push 1                      /* 1 byte (which gets the whole page)      */ \
_asm push ebx                    /* the previous page to change access      */ \
_asm call dword ptr [VirtualProtect]  /* make the call to change theaccess */ \
\
_asm mov esp,[ebx]               /* restore the old esp (storedearlier)    */ \
}
#else
#define PROTECTSTACK() {}
#define UNPROTECTSTACK() {}
#endif
#else
#define PROTECTSTACK() {}
#define UNPROTECTSTACK() {}
#endif



#endif /* PI__DEFINITIONS */
/*===== end of include file PIDEFS.H =========================================*/
