@echo off

::Paths, variables, and common compiler options setup
call scripts\sh_build_setup.bat %1 %2

::Build needed projects
call scripts\shady-commons.bat %1 %2


set coreInputLibs=%com_input_libs% shady-commons.lib opengl32.lib glew32s.lib Gdi32.lib dinput8.lib dxguid.lib
set coreInputFiles=%shCore%\src\shady-core.cpp
set coreCompilerOptions=%com_opt% %config_opt% %symbols%
set coreLinkOptions=/NOLOGO /IGNORE:4099

if /I "%configuration%"=="SH_DEBUG" (
	pushd %shCore%\sh_debug
	set coreLinkOptions=%coreLinkOptions% /NODEFAULTLIB:libcmt
	set coreCompilerOptions=%coreCompilerOptions% /MTd
	) 
if /I "%configuration%"=="SH_RELEASE" (
	pushd %shCore%\sh_release
	set coreCompilerOptions=%coreCompilerOptions% /MT
	)

if %action%==SH_RUN (
 			start shady-core.exe
 			goto return
 			)

if %action%==SH_VSRUN (
			start devenv shady-core.exe
			goto return
			)



buildTimer b ..\..\data\shady.btm

cl %coreCompilerOptions% %coreInputFiles% /link %coreLinkOptions% %coreInputLibs%

set compilationError=%ERRORLEVEL%
buildTimer e ..\..\data\shady.btm %compilationError%

if %action%==SH_BUILD_RUN (
			if %compilationError%==0 (start shady-core.exe)
			
			
			)


:return
popd