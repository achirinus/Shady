@echo off



::Paths, variables, and common compiler options setup
call scripts\sh_build_setup.bat %1 %2

if %action%==SH_RUN goto return
 

if %action%==SH_VSRUN goto return
			

set LIB_OPTIONS=/NOLOGO

if /I "%configuration%"=="SH_DEBUG" (
	pushd %shCommonsLib%\sh_debug
	cl /c %com_opt% %config_opt% %symbols% %shCommons%\src\shady-commons.cpp /Foshady-commons.obj
	lib  %LIB_OPTIONS% /OUT:shady-commons.lib shady-commons.obj 
	) 
if /I "%configuration%"=="SH_RELEASE" (
	pushd %shCommonsLib%\sh_release
	cl /c %com_opt% %config_opt% %symbols% %shCommons%\src\shady-commons.cpp /Foshady-commons.obj
	lib %LIB_OPTIONS% /OUT:shady-commons.lib shady-commons.obj 
	)

:return

popd