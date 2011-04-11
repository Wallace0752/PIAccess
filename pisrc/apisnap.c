/*-----------------------------------------------------------------------------

  $Archive: /PI/3.2/utilities/apiutil/apisnap.c $

-------------------------------------------------------------------------------

Copyright (c) 1995-2000 OSI Software, Inc. All rights reserved. 
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

   apisnap.c
   Example PI API program      

-------------------------------------------------------------------------------

History:

$Log: /PI/3.2/utilities/apiutil/apisnap.c $

22    8/01/00 4:22p Ray
Changed retrieval of last archive value to use piar_getarcvaluex to get
a recent value, and then use its timestamps to bound the call to
piar_getarcvaluesx. This fixes a problem in UDA mapped points in which
the foreign system can't handle the wide time constraint.

21    8/01/00 1:36a Ray
Replaced C++ comment with C comment.

20    8/01/00 1:34a Ray
Restored original method of finding previous archive value (using
piar_getvaluex) inside ifdef _ARCVALUE. Technique of finding last two
years of data with value count of 2 tends to break UDA mapped points
when foreign systems cannot honor value count before time range.

19    4/26/:0 9:37a Charlie
Added unix variations of identification strings used with the 'what'
command. 

18    4/06/00 7:29p Charlie
Added VSS id strings for file revision.

17    4/06/00 7:27p Charlie
Fixed printout of archive value timestamp. Made more useful routines
for printing values.

16    3/10/00 1:58p Charlie
Changed time output to check returned PI2time for bad value (-1) and
set to zero if bad. Changed format string to use int cast of fraction. 

15    12/17/99 6:18p Charlie
Added PI_Type_PItimestamp and PI2.

14    11/03/99 4:25p Charlie
Use ifdef hpux_main for HP C compiler.  

13    11/03/99 3:46p Charlie
Added new compiler define of _main for HPUX C/C++ _main. 

12    6/18/99 10:32a Piadmin
Eliminate compiler warnings (HPUX didn't like initializing two
variables  on the same line). 

11    6/08/99 3:29p Charlie
Changed archive retrieval to start from the snapshot time and search
backward in time until the next archive value is found.  This allows
the snapshot and last archive values to have the same timestamp.  Added
multiple tagnames on the command line.

10    5/06/99 1:17p Charlie
Added newline after all output.

9     2/01/99 5:27p Charlie
Remove ANSIC compiler warning for strlen compare.

8     1/25/99 9:23a Charlie
Added option to enter point number instead of tagname.  Leading
backslash is used to indicate point number.

7     9/04/98 1:12p Charlie

6     9/04/98 10:54a Charlie
Added printout of flags if set.

5     8/26/98 5:07p Charlie
Format time string subseconds and type casts in mem-functions.

3     8/26/98 3:22p Charlie
Added support for extended pointtypes and digital strings up to 80
chars. Added option to enter server and tagname arguments which will
retrieve one snapshot, then exit.  Updated copyright.

2     4/25/97 8:49a Harry
Check in Jon's changes on SCCS from Feb 5

-------------------------------------------------------------------------------
24-nov-93  jhp  use pitm_delay for delays
04-may-94  jhp  added reconnection loop
09=may-94  jhp  added version print  
13-jun-96  jhp  exit if cannot connect
17-jun-96  jhp  tagpreferred, added piar_value
05-Feb-97  jhp  better data representation on failed getsnap and arcvalue
-----------------------------------------------------------------------------*/ 

#ifdef WIN32
#pragma comment(exestr, "$Workfile: apisnap.c $ $Revision: 22 $")
#elif defined(aix)
#pragma comment(user, "@(#)$Workfile: apisnap.c $ $Revision: 22 $")
#elif defined(hpux)
#pragma VERSIONID "@(#)$Workfile: apisnap.c $ $Revision: 22 $"
#else/* solaris, osf1 */
#pragma ident "@(#)$Workfile: apisnap.c $ $Revision: 22 $"
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <string.h>

#include "piapix.h"

#define TAG_LEN 80

typedef struct
{
   char tagname[TAG_LEN+1];
   int32 point;
   char descriptor[27];   
   char engunit[32];
   char itag[33];
   char pt_type;
   PIvaluetype pt_typex;
   float64 rval, arcrval;
   int32  ival, arcival;
   void  *bval, *arcbval;
   uint32 bsize, arcbsize;
   int32  istat, arcistat;
   int16  flags, arcflags;
   PITIMESTAMP ts, arcts;
} TAG;

static int dosnap ( char * );
static int32 lastdayofmonth ( int32 month );
static void print_taginfo ( TAG *tag );

#define MAXTRYS 20
#ifndef TRUE
#define TRUE -1
#endif
#ifndef FALSE
#define FALSE 0
#endif

int main ( int argc, char **argv )
{
   int32 result = 1;
   int  i, trys = 0;
   int32 connection = FALSE;
   char name[32], address[32];
   char version[32];
   char tname[TAG_LEN+1];
   
   /* The line below for the HPUX C compiler when linking with C++.  */
#ifdef hpux_main
   _main();
#endif

   if ( !piut_getapiversion ( version, sizeof(version) ) )
   {
      printf ( "\nPI-API version %s", version );
   }
   
   while ( TRUE )
   {
      if ( argc > 1 )
      {  /*  attempt connection to passed node name */
         piut_setprocname ( "snap" );
         printf ( "\n Attempting connection to %s", argv[1] );
         while ( result && trys < MAXTRYS )
         {
            trys++;
            result = piut_setservernode ( argv[1] );
            if ( result )
            {
               printf ( "\n Error %d, connecting to %s", result, argv[1] );
               return result;
            }
            else
            {
               connection = TRUE;
            }
         }
      }
      else  /*  attempt connection to default homenode */
      {   
         printf ( "\n Attempting connection to Default homenode" );
         while ( result && trys < MAXTRYS )
         {
            trys++;
            result = piut_connect ( "snap" );
            if ( result )
            {
               printf ( "\n Error %d, connecting to Default homenode", result );
               return result;
            }
            else      
            {             
               if ( piut_netserverinfo ( name, 32, address, 
                  32, &connection ) )
               {
                  printf ( "\nConnected to DEFAULT pihome node" );
                  connection = TRUE;
               }
               else
               {
                  printf ( "\nConnected to %s (%s)", name, address );
               }
            }
         }  
      }
      if ( !connection )
      {
         printf ( "\nError %ld connecting to PI Server node", result );
         exit (1);
      }
      if (argc > 2)
      {
         /* Cycle through all tags after the host name. */
         for (i=2; i<argc; i++)
         {
            strncpy(tname, argv[i], 80);
            tname[TAG_LEN+1] = '\0';
            if ( dosnap( tname ) )
            {
               trys = 0;
               result = 1;
               connection = FALSE;
               printf ( "\nConnection lost attempting reconnection" );
               break;
            }
         }
         break;
      } else {
         tname[0] = '\0';
         if ( dosnap ( tname ) )
         {
            trys = 0;
            result = 1;
            connection = FALSE;
            printf ( "\nConnection lost attempting reconnection" );
         }
         else    
            break;
      }
   }
   piut_disconnect();
   return 0;
}

#define BUFSIZE  1024
static int dosnap ( char *tname )
{
   int32 result, reterr, pt_count;
   int len, once_len;
   float64 *pSnapDval, *pArcDval;
   int32   *pSnapIval, *pArcIval;
   void    *pSnapBval = NULL;
   void    *pArcBval = NULL;
   uint32  tmp_bsize;
   TAG tag;
   tag.bsize = 0;
   tag.arcbsize = 0;
   tag.bval = NULL;
   tag.arcbval = NULL;
   
   strcpy(tag.tagname, tname);
   once_len = strlen( tag.tagname );
   len = once_len;
   while ( TRUE )
   {
      if ( len > 0 )   
      {
         if (tag.tagname[0] == '\\')
         {
            tag.point = atoi( &tag.tagname[1] );
            result = 0;
         }
         else
            result = pipt_findpoint (tag.tagname, &tag.point );
         switch ( result )
         {
         default:
            printf ( "\npipt_findpoint error %ld, tag %s", 
               result, tag.tagname );
            piut_disconnect();
            return -1;
         case -5:
         case -2:
            printf ( "\nTag %s does not exist", tag.tagname );
            break;               
         case 0:
            result = pipt_tagpreferred ( tag.point, tag.tagname, TAG_LEN+1 );
            if ( result )
            {
               printf ( "\npipt_tag %ld", result );
            }
            result = pipt_descriptor ( tag.point, tag.descriptor, 27 );
            if ( result )
            {
               printf ( "\npipt_descriptor %ld", result );
               tag.descriptor[0] = '\0';
            }
            result = pipt_engunitstring ( tag.point, tag.engunit, 32 );
            if ( result )
            {
               printf ( "\npipt_engunitstring %ld", result );
               tag.engunit[0] = '\0';
            }
            result = pipt_pointtype ( tag.point, &tag.pt_type );
            if ( result )
            {
               printf ( "\npipt_pointtype %ld", result );
               tag.pt_type = '\0';
            }
            result = pipt_pointtypex ( tag.point, &tag.pt_typex );
            if ( result )
            {
               printf ( "\npipt_pointtypex %ld", result );
               tag.pt_typex = PI_Type_bad;
            }
            result = pipt_instrumenttag ( tag.point, tag.itag, sizeof(tag.itag));
            tag.rval = (float) 0.0;
            switch (tag.pt_typex ) {
            case PI_Type_PIstring:
            case PI_Type_blob:
            case PI_Type_PItimestamp:
               pSnapDval = pArcDval = NULL;
               pSnapIval = pArcIval = NULL;
               /*--- Snapshot ---*/
               /* Start with BUFSIZE and reallocate if needed. */
               if (tag.bsize == 0) {/* Skip allocation if a subsequent run. */
                  if ( (tag.bval = (void *)malloc(BUFSIZE))==NULL ) {
                     printf("\nError allocating bval storage");
                     piut_disconnect();
                     exit(1);
                  }
               }
               tag.bsize = (tag.bsize > BUFSIZE - 1) ? tag.bsize : BUFSIZE - 1;
               memset(tag.bval, 0, (size_t)(tag.bsize+1));
               pSnapBval = tag.bval;
               /*--- Archive ---*/
               if (tag.arcbsize == 0) {
                  if ( (tag.arcbval = (void *)malloc(BUFSIZE))==NULL ) {
                     printf("\nError allocating bval storage");
                     exit(1);
                  }
               }
               tag.arcbsize = (tag.arcbsize > BUFSIZE - 1) ? tag.arcbsize : BUFSIZE - 1;
               memset( tag.arcbval, 0, (size_t)(tag.arcbsize+1));
               pArcBval = tag.arcbval;
               break;
            case PI_Type_int16:
            case PI_Type_int32:
               pSnapDval = pArcDval = NULL;
               pSnapBval = pArcBval = NULL;
               tag.bsize = tag.arcbsize = 0;
               pSnapIval = &tag.ival;
               pArcIval  = &tag.arcival;
               break;
            case PI_Type_digital:
               pSnapDval = pArcDval = NULL;
               pSnapIval = pArcIval = NULL;
               pSnapBval = pArcBval = NULL;
               tag.bsize = tag.arcbsize = 0;
               break;
            default:/* floats, PI2 */
               pSnapIval = pArcIval = NULL;
               pSnapBval = pArcBval = NULL;
               tag.bsize = tag.arcbsize = 0;
               pSnapDval = &tag.rval;
               pArcDval  = &tag.arcrval;
               break;
            } /* End switch */

            /*--- Snapshot ---*/
            pt_count = 1;
            result = pisn_getsnapshotsx ( &tag.point, &pt_count, pSnapDval,
               pSnapIval, pSnapBval, &tag.bsize, &tag.istat, &tag.flags,
               &tag.ts, &reterr, GETFIRST);
            if (result == -15010/*PI_OVERFLOW*/) {
               if ( tag.bsize > 4096)
               {
                  printf("\nError %d; returned bsize= %d", 
                     result, tag.bsize);
                  free(tag.bval);
                  free(tag.arcbval);
                  exit(1);
               }
               if ((tag.bval= (void *)realloc(tag.bval,(size_t)(tag.bsize+1)))==
                  NULL ) {
                  printf("\nError allocating bval storage");
                  free(tag.bval);
                  free(tag.arcbval);
                  exit(1);
               }
               memset( tag.bval, 0,(size_t)(tag.bsize+1));
               pSnapBval = tag.bval;
               pt_count = 1;
               result = pisn_getsnapshotsx ( &tag.point, &pt_count, pSnapDval,
                  pSnapIval, pSnapBval, &tag.bsize, &tag.istat, &tag.flags,
                  &tag.ts, &reterr, GETSAME);
            }
            if (result) {
               tag.istat = 0xffffffff;  /* mark as unsuccessful call 5feb97 */
               printf ( "\nError:  pisn_getsnapshotsx %ld", reterr );
               pitm_setcurtime(&tag.ts, FALSE);
            }
            
            /*--- Archive ---*/
            memcpy((void *)&tag.arcts,(void *)&tag.ts, sizeof(tag.ts));
            /* Retrieve timestamp of a recent archive event using piar_getarcvaluex */
            /* Subtract approximately one minute from the snapshot time. The timestamp */
			/* retrieved need not be the previous since the next archive call will allow */
			/* for this. */
            tag.arcts.second = 0.0;
			if (tag.arcts.minute > 0) {
               tag.arcts.minute -= 1;
            } else if (tag.arcts.hour > 0) {
				tag.arcts.hour -= 1;
				tag.arcts.minute = 59;
			} else if (tag.arcts.day > 1) {
				tag.arcts.day -= 1;
				tag.arcts.hour = 23;
				tag.arcts.minute = 59;
			} else if (tag.arcts.month > 1) {
				tag.arcts.month -= 1;
				tag.arcts.day = lastdayofmonth(tag.arcts.month);
				tag.arcts.hour = 23;
				tag.arcts.minute = 59;
			} else {
				tag.arcts.year -= 1;
				tag.arcts.month = 12;
				tag.arcts.day = lastdayofmonth(tag.arcts.month);
				tag.arcts.hour = 23;
				tag.arcts.minute = 59;
			}

            /* Obtain the timestamp alone by passing all other data arguments as null */
			result = piar_getarcvaluex(tag.point, ARCVALUEBEFORE, 0,
               0, 0, 0, 0, 0, &tag.arcts);

            if (result) {
               tag.istat = 0xffffffff;  /* mark as unsuccessful call */
               printf ( "\nError:  piar_getarcvaluex %ld", reterr );
               pitm_setcurtime(&tag.arcts, FALSE);
            }

            /* Retrieve last archive value using piar_getarcvaluesx */
			/* This will allow retrieval of the previous archive event even if */
			/* it has the same timestamp and possibly the same value as the snapshot. */
            /* Use the timestamp retrieved above. It will be sufficient to limit */
			/* the range of time queried. Limiting the range is not an issue for PI, */
            /* but can be damaging for some foreign systems mapped to PI using UDA that */
			/* honor the time range before the requested value count. */
            pt_count = 2;
            tmp_bsize = tag.arcbsize;
            result = piar_getarcvaluesx(tag.point, ARCflag_comp, &pt_count,
               pArcDval, pArcIval, pArcBval, &tag.arcbsize, &tag.arcistat,
               &tag.arcflags, &tag.ts, &tag.arcts, GETFIRST);
            /* Ignore snapshot and go to next value : clear buffer. */
            if (tag.arcbsize > 0 && (result == 0 || result == -15010)) {
               tag.arcbsize = tmp_bsize;
               memset(tag.arcbval, 0, (size_t)tag.arcbsize);
            }
            result = piar_getarcvaluesx(tag.point, ARCflag_comp, &pt_count,
               pArcDval, pArcIval, pArcBval, &tag.arcbsize, &tag.arcistat,
               &tag.arcflags, &tag.ts, &tag.arcts, GETNEXT);
            if (result == -15010 /*PI_OVERFLOW*/) {
               if ( (tag.arcbval = (void *)realloc(tag.arcbval,
                  (size_t)(tag.arcbsize+1)))==NULL ) {
                  printf("\nError allocating bval storage");
                  exit(1);
               }
               memset(tag.arcbval, 0, (size_t)(tag.arcbsize+1));
               pArcBval = tag.arcbval;
               result = piar_getarcvaluesx(tag.point, ARCflag_comp, &pt_count,
                  pArcDval, pArcIval, pArcBval, &tag.arcbsize, &tag.arcistat,
                  &tag.arcflags, &tag.ts, &tag.arcts, GETSAME);
            }
            
            if (result) {
               tag.arcistat = 0xffffffff;  /* mark as unsuccessful call 5feb97 */
               printf ( "\nError:  piar_getarcvaluesx %ld", result );
            }

            print_taginfo ( &tag );
            break;
         }
         if (once_len > 0) break;
      }
      printf ( "\n\nEnter tagname:  " );
      gets ( tag.tagname );
      len = strlen ( tag.tagname );
      if ( len < 1 )
         break;
   }
   if (tag.bval) free(tag.bval);
   if (tag.arcbval) free(tag.arcbval);
   return ( 0 );
}
static char *gettypestr ( PIvaluetype pttype)
{
   static char  tmpstr[8];
   switch (pttype)
   {
   case PI_Type_int16:
      return "Integer-16";
   case PI_Type_int32:
      return "Integer-32";
   case PI_Type_digital:
      return "Digital";
   case PI_Type_PIstring:
      return "String";
   case PI_Type_PItimestamp:
      return "Timestamp";
   case PI_Type_blob:
      return "Blob";
   case PI_Type_float32:
      return "Real-32";
   case PI_Type_float16:
      return "Real-16";
   case PI_Type_float64:
      return "Real-64";
   case PI_Type_PI2:
      return "PI2";
   default:
      sprintf(tmpstr, "%d", pttype);
      break;
   }
   return tmpstr;
}

static char *getvaluestr (char *stat, int32 statlen, int32 *vallen,
                          int32 point, PIvaluetype pt_typex, char *engunit,
                double drval, int32 ival, void * bval, uint32 bsize, int32 istat)
{
   static char  tmpstr[256];
   int32 digcode, dignumb, result, localistat;
   if ( istat == 0xffffffff )
   {
      strncpy ( stat, "ERROR", statlen );

      stat[statlen-1] = '\0';
      *vallen = 5;
      return "ERROR";
   }
   else if ( istat != 0 )
   {
      localistat = istat;
      if (pt_typex == PI_Type_digital)
      {
         result = pipt_digpointers ( point, &digcode, &dignumb );
         if (!result && istat >= 0 && istat <= dignumb )
            localistat += digcode;
      }
      result = pipt_digstate ( localistat, stat, statlen );
      if ( result )
         strncpy ( stat, "-----", statlen );
      
      stat[statlen-1] = '\0';
      *vallen = strlen(stat);
      return stat;
   }
   strncpy ( stat, "Good", statlen );
   stat[statlen-1] = '\0';
   switch ( pt_typex )
   {
   case PI_Type_int16:
   case PI_Type_int32:
      sprintf ( tmpstr, "%11ld %s", ival, engunit );
      *vallen = strlen(tmpstr);
      break;

   case PI_Type_blob:
      sprintf ( tmpstr, "N/A   Size = %d", bsize ); 
      *vallen = strlen(tmpstr);
      break;

   case PI_Type_PItimestamp:
   case PI_Type_PIstring:
      *vallen = bsize;
      return (char *)bval;

   default:
   case PI_Type_float32:
   case PI_Type_float16:
   case PI_Type_float64:
   case PI_Type_PI2:
      /* TODO: implement precision attribute */
      sprintf ( tmpstr, "%.2f %s", drval, engunit ); 
      *vallen = strlen(tmpstr);
      break;
   }/* End switch pt_typex */
   return tmpstr;
}
static char * gettimestr( int32 istat, PITIMESTAMP pits)
{
   static char tstr[32];
   static char mstr[12][4] = {"Jan","Feb","Mar","Apr","May","Jun",
      "Jul","Aug","Sep","Oct","Nov","Dec"};
   double frac;
   if ( istat == 0xffffffff )
      return "ERROR";
   else {
      sprintf(tstr,"%02d-%s-%02d %02d:%02d:%02d",
         pits.day, mstr[pits.month-1],
         ( (pits.year>=2000)?pits.year-2000 : pits.year-1900 ),
         pits.hour, pits.minute, (int)pits.second);
      frac = (pits.second-(int32)pits.second);
      if ( frac > 0.00001)
         sprintf(tstr, "%s.%05d", tstr, (int)(frac*100000.0));
   }
   return tstr;
}

static void print_taginfo ( TAG *tag )
{
   int32 valpos;
   char stat[80];
   char arcstat[80];

   printf ( "\n\n  Tag = %s   Point Number = %ld   Type = %s",
      tag->tagname, tag->point, gettypestr(tag->pt_typex) );
   printf ( "\n  %s", tag->descriptor );
   printf ( "\n\n                Snapshot value" );
   printf ( "\n  Value = %s", getvaluestr(stat, sizeof(stat), &valpos,
      tag->point, tag->pt_typex, tag->engunit,
                tag->rval, tag->ival, tag->bval, tag->bsize, tag->istat));
   if (valpos < 50)
      printf("\t%s", gettimestr(tag->istat, tag->ts) );
   else
      printf("\n  Time = %s", gettimestr(tag->istat, tag->ts) );

   if ( tag->pt_typex != PI_Type_digital)
      printf ( "\n  Status = %s", stat ); 
   if (tag->flags > 0) {
      stat[0] = '\0';/* Reuse stat. */
      /* Allow for combinations of flags by check each individually. */
      if ( (tag->flags & PI_M_AFLAG) )
         strcat ( stat, " Annotated");
      if ( (tag->flags & PI_M_QFLAG) )
         strcat ( stat, " Questionable" );
      if ( (tag->flags & PI_M_SFLAG) )
         strcat ( stat, " Substituted" );
      printf ( "\n  Flags =%s", stat ); 
   }
   
   printf ( "\n\n              Latest archive value" );
   printf ( "\n  Value = %s", getvaluestr(arcstat, sizeof(arcstat), &valpos,
      tag->point, tag->pt_typex, tag->engunit,
                tag->arcrval, tag->arcival, tag->arcbval, tag->arcbsize, tag->arcistat));
   if (valpos < 50)
      printf("\t%s", gettimestr(tag->arcistat, tag->arcts) );
   else
      printf("\n  Time = %s", gettimestr(tag->arcistat, tag->arcts) );

   if ( tag->pt_typex != PI_Type_digital)
      printf ( "\n  Status = %s", stat ); 

   if (tag->arcflags > 0) {
      arcstat[0] = '\0';/* Reuse stat. */
      /* Allow for combinations of flags by check each individually. */
      if ( (tag->arcflags & PI_M_AFLAG) )
         strcat ( arcstat, " Annotated");
      if ( (tag->arcflags & PI_M_QFLAG) )
         strcat ( arcstat, " Questionable" );
      if ( (tag->arcflags & PI_M_SFLAG) )
         strcat ( arcstat, " Substituted" );
      printf ( "\n  Flags =%s\n", arcstat ); 
   } else printf("\n");
   return;
}

static int32 lastdayofmonth ( int32 month )
{
	switch (month) { /* month is 1-12 */
	case 1: /* jan */
	case 3: /* mar */
	case 5: /* may */
	case 7: /* jul */
	case 8: /* aug */
	case 10:  /* oct */
	case 12: /* dec */
		return 31;

	case 4: /* apr */
	case 6: /* jun */
	case 9: /* sep */
	case 11:  /* nov */
		return 30;

	case 2: /* feb */
	default: /* not worth worrying about leap years */
		return 28; /* return lowest legal day for all months */
	}
}
