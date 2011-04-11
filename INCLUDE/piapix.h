/*-----------------------------------------------------------------------------

$Archive: /PI/clients/piapi/piapix.h $

-------------------------------------------------------------------------------

Copyright ©1995-2001 OSI Software, Inc. All rights reserved. 
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

This is the header file for the extended PI-API, which supports the new data
types of the PI 3 system and subsecond timestamps.

-------------------------------------------------------------------------------

$Log: /PI/clients/piapi/piapix.h $

24    4/04/01 10:21a Etam
changed copyright; add explanation for ARCAPPEND and ARCAPPENDX

23    3/16/:0 2:07p Charlie
 Made copyright date to 2000 

22    3/09/:0 7:48a Charlie
Added const to filter in piut_strerror 

21    2/07/00 10:17a Charlie
Added pitm_getutctime

20    12/17/99 6:19p Charlie
Added PI_Type_PItimestamp

19    5/05/99 10:36a Charlie
piut_strerror

18    4/29/99 2:59p Charlie
Added piut_errormsgfilter

17    1/29/99 2:46p Charlie
Added piut_errormsg

16    8/17/98 1:51p Charlie
PIvaluetype enum had comma after last type.  removed.

15    8/13/98 5:08p Ray
PITIMESTAMP: renamed member 'reserved' to 'tzinfo'. New routines:
pitm_setdst, pitm_isdst.

14    8/07/98 6:24p Charlie
Removed unused PIvaluetype enumerations to prevent problems w/ user
input.  Moved piar_putvalue functions to alphabetical location.

13    7/14/98 5:44p Ray
Added #define constants for extended archive put/edit/delete mode
codes. Removed piar_timedvaluesx. Added piar_putarcvaluesx,
piar_putarcvaluex.

12    7/13/98 2:15p Charlie
Added PIvaluetype to PI_EVENT structure.  added funccode to
pisn_evmexceptionsx function.

11    4/30/98 9:37a Charlie
Deleted PI_VAL structure; unneeded in C/C++.

10    4/29/98 10:47a Charlie
Changed pisn_putsnapshotqx queueing flag to pibool; Added
pisn_evmexceptions call with PI_EVENT structure for returned values. Added
piar_timedvaluesx prototype.

9     3/20/98 3:03p Charlie
Added pisn_sendexceptqx for VB compatibility and PI_VAL structure.
Changed long value list in pisn_sendexceptionqx to use PI_EVENT
structures.
    

History:

960521 RCV   New file.
960521 hks   Change C++ comments to C style.
960603 RCV   Replace 'double' in function prototypes with 'float64'
             Added new routine piar_getarcvaluex
960617 RCV   Added pipt_pointtypex, PIvaluetype typedef.
960723 RCV   Added pisn_putsnapshotsx
960731 RCV   pitm_setcurtime: changed second arg to 'pibool'
             pitm_setpitime: changed void return to int32
             pitm_settime: changed void return to int32
960906 RCV   added reserved member to PItimestruc to correct alignment
960918 RCV   pisn_getsnapshotsx: added error to argument list
970507 RCV   Added piut_syscommand, piut_putfile.
980220 cah   Added pisn_flushputsnapq, pisn_sendexceptionqx, pisn_sendexceptionsx
             PI_EVENT, and PI_EXCEPTSTRU structures.
-----------------------------------------------------------------------------*/ 
#ifndef _PIAPIX_H
#define _PIAPIX_H

#include "piapi.h"

#ifndef GETFIRST    /* caller may include 'pilogex.h' */
#define GETFIRST (0)
#define GETNEXT  (1)
#endif
#define GETSAME  (2)
#define PI_NOMOREVALUES (100)

#define PI_M_AFLAG ((int16)0x0001)
#define PI_M_QFLAG ((int16)0x0002)
#define PI_M_SFLAG ((int16)0x0004)

/* piar_putarcvaluesx defines */
#define ARCNOREPLACE 3     /* add unless event(s) exist at same time (PI 2.x) */
#define ARCAPPEND    4     /* add event regardless of existing events; this will create 
                            * a duplicate if there is an event at the same time already 
                            * in the archive. If ARCAPPEND is called with a value newer 
                            * than the snapshot, however, this value will be subject to 
                            * compression.
                            */
#define ARCREPLACE   5     /* add event, replace if event at same time */
#define ARCREPLACEX  6     /* replace existing event (fail if no event at time) */
#define ARCDELETE    7     /* remove existing event */
#define ARCAPPENDX   8     /* add event regardless of existing events, no compression; 
                            * this means that a value newer than the snapshot is not 
                            * subject to compression. In this case, the snapshot will be 
                            * forced to the archive and the new value will become the 
                            * snapshot.
                            */
#ifdef __cplusplus
extern "C" {
#endif

/*=== PI-API-X Definitions ============================================================*/
typedef struct _PITIMESTAMP {
   int32 month;    /* 1-12 */
   int32 year;     /* four digit */
   int32 day;      /* 1-31 */
   int32 hour;     /* 0-23 */
   int32 minute;   /* 0-59 */
   int32 tzinfo;   /* timezone information */
   double second; /* 0-59.99999999.... */
} PITIMESTAMP;

/*=======================================================================================
NOTE: this PIvaluetype typedef must be kept current with the definition in PIVALUE.HXX
=======================================================================================*/
typedef enum _PIvaluetype {
   PI_Type_null = 0,
   PI_Type_bool,
   PI_Type_uint8,
   PI_Type_int8,
   PI_Type_char,
   PI_Type_uint16,
   PI_Type_int16,
   PI_Type_uint32,
   PI_Type_int32,
   PI_Type_uint64,
   PI_Type_int64,
   PI_Type_float16,
   PI_Type_float32,
   PI_Type_float64,
   PI_Type_PI2,
   PI_Type_digital = 101,
   PI_Type_blob,
   PI_Type_PItimestamp = 104,
   PI_Type_PIstring,
   PI_Type_bad = 255
} PIvaluetype;

typedef struct
{
   PIvaluetype typex;
   float64  drval;
   int32    ival;
   void     *bval;  /* Set to NULL if not used. */
   uint32   bsize;
   int32    istat;
   int16    flags;
   PITIMESTAMP timestamp;
} PI_EVENT;

typedef struct
{
   PI_EVENT *newvalue;  /* Must be allocated */
   PI_EVENT *prevvalue; /* Must be set to NULL if not allocated */
   PI_EVENT *oldvalue;  /* Must be set to NULL if not allocated */
   float64   excdeveng;
   float64   excmin;
   float64   excmax;
} PI_EXCEPTSTRU;

/*=== PI-API-X Function Prototypes ====================================================*/
int32 PIPROC piar_getarcvaluesx( int32 ptnum, int32 arcmode, int32 PIPTR *count,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp0,
   PITIMESTAMP PIPTR *timestamp, int32 funccode);
int32 PIPROC piar_getarcvaluesfilterx(int32 ptnum, int32 arcmode, int32 PIPTR *count,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp0,
   PITIMESTAMP PIPTR *timestamp, char PIPTR *expression, int32 funccode);
int32 PIPROC piar_getarcvaluex( int32 ptnum, int32 mode, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp);
int32 PIPROC piar_putarcvaluesx(int32 count, int32 mode, int32 PIPTR *ptnum,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR **bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp,
   int32 PIPTR *errors);
int32 PIPROC piar_putarcvaluex(int32 ptnum, int32 mode, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp);

int32 PIPROC pipt_pointtypex( int32 ptnum, PIvaluetype PIPTR *typex);

int32 PIPROC pisn_evmexceptionsx( int32 PIPTR *count, int32 PIPTR *ptnum,
   PI_EVENT PIPTR *values, int32 funccode);
int32 PIPROC pisn_flushputsnapqx( int32 PIPTR *numbpterrs, QERROR PIPTR *qerrs);
int32 PIPROC pisn_getsnapshotsx( int32 PIPTR *ptnum, int32 PIPTR *count_ptnum,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp,
   int32 PIPTR *error, int32 funccode);
int32 PIPROC pisn_getsnapshotx( int32 ptnum, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp);
int32 PIPROC pisn_putsnapshotqx( int32 ptnum, float64 PIPTR *rval, int32 PIPTR *ival,
   void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,  int16 PIPTR *flags,
   PITIMESTAMP PIPTR *timestamp, pibool queueing, int32 PIPTR *numbpterrs,
   QERROR PIPTR *qerrs );
int32 PIPROC pisn_putsnapshotsx( int32 count, int32 PIPTR *ptnum, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR **bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp, int32 PIPTR *errors);
int32 PIPROC pisn_putsnapshotx(int32 ptnum, float64 PIPTR *rval, int32 PIPTR *ival,
   void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat, int16 PIPTR *flags,
   PITIMESTAMP PIPTR *timestamp);
int32 PIPROC pisn_sendexceptionqx( int32 pt,
      PI_EVENT PIPTR *oldvalue, PI_EVENT PIPTR *prevvalue, PI_EVENT newvalue,
      float64 excdeveng, float64 excmin, float64 excmax, int32 PIPTR *count,
      pibool queueing, int32 PIPTR *numbpterrs, QERROR PIPTR *qerrs );
int32 PIPROC pisn_sendexceptionsx( int32 num_pts, int32 PIPTR *pt,
   PI_EXCEPTSTRU PIPTR **except, int32 PIPTR *errors, int32 PIPTR *count);

int32 PIPROC pitm_isdst(PITIMESTAMP PIPTR *timestamp);
int32 PIPROC pitm_getpitime(PITIMESTAMP PIPTR *timestamp, float64 PIPTR *frac);
double PIPROC pitm_getutctime(PITIMESTAMP PIPTR *timestamp);
void PIPROC pitm_setcurtime(PITIMESTAMP PIPTR *timestamp, pibool incl_subsec);
int32 PIPROC pitm_setpitime(PITIMESTAMP PIPTR *timestamp, int32 pitime, float64 frac);
int32 PIPROC pitm_settime(PITIMESTAMP PIPTR *timestamp, int32 year, int32 month,
   int32 day, int32 hour, int32 minute, float64 second);
void PIPROC pitm_setdst(PITIMESTAMP PIPTR *timestamp, int32 tm_isdst);

int32 PIPROC piut_errormsg(int32 stat, TCHAR PIPTR *msg, size_t PIPTR *msglen);
int32 PIPROC piut_strerror(int32 stat, TCHAR PIPTR *msg, size_t PIPTR *msglen,
                           const TCHAR PIPTR *filter);
PIINT32 piut_syscommand(char PIPTR *command, char PIPTR *outfilename,
                        int32 PIPTR *sysstatus);
PIINT32 piut_putfile(char PIPTR *localfilename, char PIPTR *remotefilename,
                     int32 len);

#ifdef __cplusplus
}
#endif

#endif /* ifdef _PIAPIX_H */
