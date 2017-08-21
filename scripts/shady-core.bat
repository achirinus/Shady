@echo off

::Paths, variables, and common compiler options setup
call scripts\sh_build_setup.bat %1 %2

::Build needed projects
call scripts\shady-commons.bat %1


set coreInputLibs=%com_input_libs% shady-commons.lib opengl32.lib glew32s.lib Gdi32.lib dinput8.lib dxguid.lib
set coreInputFiles=%shCore%\src\shady-core.cpp
set coreCompilerOptions=%com_opt% %config_opt% %symbols%
set coreLinkOptions=/NOLOGO

if /I "%configuration%"=="SH_DEBUG" (
	pushd %shCore%\sh_debug
	set coreLinkOptions=%coreLinkOptions% /NODEFAULTLIB:libcmt
	set coreCompilerOptions=%coreCompilerOptions% /MTd
	) 
if /I "%configuration%"=="SH_RELEASE" (
	pushd %shCore%\sh_release
	set coreCompilerOptions=%coreCompilerOptions% /MT
	)

cl %coreCompilerOptions% %coreInputFiles% /link %coreLinkOptions% %coreInputLibs%

if "%action%"=="SH_RUN" (start shady-core.exe)

if "%action%"=="SH_VSRUN" (start devenv shady-core.exe)



popd