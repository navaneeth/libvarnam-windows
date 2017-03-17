 @ECHO OFF

regsvr32 /u /s VarnamIME.dll
mkdir %ALLUSERSPROFILE%\varnam
XCOPY schemes %ALLUSERSPROFILE%\varnam\schemes /i
regsvr32 /s VarnamIME.dll

pause