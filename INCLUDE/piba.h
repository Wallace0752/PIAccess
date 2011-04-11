/*-----------------------------------------------------------------------------

@(#)piba.h	1.3 03/19/96

-------------------------------------------------------------------------------

Copyright (c) 1995 Oil Systems, Inc. All rights reserved. Unpublished - rights
reserved under the copyright law of the United States.

USE OF A COPYRIGHT NOTICE IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION 
OR DISCLOSURE.

THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF 
OIL SYSTEMS, INC.  USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED WITHOUT 
THE PRIOR EXPRESS WRITTEN PERMISSION OF OIL SYSTEMS, INC.

RESTRICTED RIGHTS LEGEND
Use, duplication, or disclosure by the Government is subject to restrictions 
as set forth in subparagraph (c)(1)(ii) of the Rights in Technical Data and 
Computer Software clause at DFARS 252.227.7013

Oil Systems, Inc.
545 Estudillo Ave., San Leandro CA 94577

-------------------------------------------------------------------------------

Description:


-------------------------------------------------------------------------------

History:


-----------------------------------------------------------------------------*/ 
/*  PI Batch API Header File   */
#ifndef _PIBA_H
#define _PIBA_H
#include "pidefs.h"
#ifdef __cplusplus
extern "C"
{
#endif

int32 PIPROC piba_findaliaspoint ( char PIPTR *unit, char PIPTR *alias, 
   int32 PIPTR *point, char PIPTR *tagname, int32 len );  
int32 PIPROC piba_getunit ( char PIPTR *unit, int32 len, int32 index, 
   int32 PIPTR *number );
int32 PIPROC piba_getunitswalias ( char PIPTR *alias, char PIPTR *unit, int32 len, 
   int32 index, int32 PIPTR *number );
int32 PIPROC piba_getaliaswunit ( char PIPTR *unit, char PIPTR *alias, int32 len, 
   int32 index, int32 PIPTR *number );
int32 PIPROC piba_search ( char PIPTR *batchid, int32 len0, char PIPTR *unit, int32 len1,
   char PIPTR *product, int32 len2, int32 PIPTR *startime, int32 PIPTR *endtime, 
      int32 searchflag, int32 timeout );
      
#ifdef __cplusplus
}
#endif


#endif



