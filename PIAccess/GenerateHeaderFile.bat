rem generate c header file:
cd bin
javah -jni piaccess.PiDb
move /Y *.h ..\
pause
exit

rem AdditionalIncludeDirectories
rem "D:\Program Files\Java\jdk1.6.0_16\include\win32";"D:\Program Files\Java\jdk1.6.0_16\include"
rem copy /Y *.h ..\..\..\pisrc-MFC\PIInterface\
