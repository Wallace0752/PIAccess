# Microsoft Developer Studio Generated NMAKE File, Based on apisnap.dsp
!IF "$(CFG)" == ""
CFG=apisnap - Win32 Debug
!MESSAGE No configuration specified. Defaulting to apisnap - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "apisnap - Win32 Release" && "$(CFG)" !=\
 "apisnap - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "apisnap.mak" CFG="apisnap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "apisnap - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "apisnap - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "apisnap - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\apisnap.exe"

!ELSE 

ALL : "$(OUTDIR)\apisnap.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\apisnap.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\apisnap.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G3 /ML /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32"\
 /D "_CONSOLE" /D "_MBCS" /D "_WIN32" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\apisnap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=piapi32.lib kernel32.lib user32.lib advapi32.lib /nologo\
 /subsystem:console /pdb:none /machine:I386 /out:"$(OUTDIR)\apisnap.exe"\
 /libpath:"..\..\library" 
LINK32_OBJS= \
	"$(INTDIR)\apisnap.obj"

"$(OUTDIR)\apisnap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "apisnap - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\apisnap.exe"

!ELSE 

ALL : "$(OUTDIR)\apisnap.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\apisnap.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\apisnap.exe"
	-@erase "$(OUTDIR)\apisnap.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "_DEBUG" /D\
 "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_WIN32" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\apisnap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=piapi32.lib kernel32.lib user32.lib advapi32.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)\apisnap.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\apisnap.exe" /pdbtype:sept\
 /libpath:"..\..\library" 
LINK32_OBJS= \
	"$(INTDIR)\apisnap.obj"

"$(OUTDIR)\apisnap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "apisnap - Win32 Release" || "$(CFG)" ==\
 "apisnap - Win32 Debug"
SOURCE=.\apisnap.c
DEP_CPP_APISN=\
	"..\..\include\piapi.h"\
	"..\..\include\piapix.h"\
	"..\..\include\piba.h"\
	"..\..\include\pidefs.h"\
	"..\..\include\pisql.h"\
	

"$(INTDIR)\apisnap.obj" : $(SOURCE) $(DEP_CPP_APISN) "$(INTDIR)"



!ENDIF 

