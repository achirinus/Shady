@echo off


REM DO NOT CALL THIS ON IT'S OWN!!!
REM this need to be called from sh_build.bat



if /I "%configuration%"=="SH_DEBUG" (
	pushd %shCommonsLib%\sh_debug
	cl /c %com_opt% %config_opt% %symbols% %shCommons%\src\shady-commons.cpp /Foshady-commons.obj
	lib /OUT:shady-commons.lib shady-commons.obj 
	) 
if /I "%configuration%"=="SH_RELEASE" (
	pushd %shCommonsLib%\sh_release
	cl /c %com_opt% %config_opt% %symbols% %shCommons%\src\shady-commons.cpp /Foshady-commons.obj
	lib /OUT:shady-commons.lib shady-commons.obj 
	)

popd