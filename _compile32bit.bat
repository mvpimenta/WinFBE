set FBLIBDIR=win32
set FBCPATH=x:\PSS121\FB\WinFBE_Suite\FreeBASIC-1.06.0

cd src
%FBCPATH%\fbc32 WinFBE.bas -x ..\WinFBE32.exe WinFBE.rc -s gui
cd ..
 
