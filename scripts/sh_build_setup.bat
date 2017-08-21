@echo off

::	In order to build to need Visual studio 2015 and have set 
::enviromental variable VC_HOME 
::


::Setting directories
SET projDir=%CD%
SET shCommons=%projDir%\shady-commons
SET shCore=%projDir%\shady-core
SET depDir=%projDir%\Dep
SET VS_PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE
SET VS_IDE=%VS_PATH%\denenv.exe

REM Setting include dirs
SET shCommonsInclude=%shCommons%\include
SET shCoreInclude=%shCore%\include
REM Remove glew after I learn how to load GL functions myself
SET glewInclude=%depDir%\GLEW\include\GL
SET stbLib=%depDir%\STB

SET AllDepsInclude=%glewInclude%;%stbLib%


REM Win include copied from VS proj
REM Try to remove as much as possible from this things
set VsInclude1=%VC_HOME%\VC\include
set VsInclude2=%VC_HOME%\VC\atlmfc\include
set VsInclude3=C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt
set VsInclude4=C:\Program Files (x86)\Windows Kits\8.1\Include\um
set VsInclude5=C:\Program Files (x86)\Windows Kits\8.1\Include\shared
set VsInclude6=C:\Program Files (x86)\Windows Kits\8.1\Include\winrt
set VsInclude7=C:\Program Files (x86)\Windows Kits\8.1\Include\um\gl

Set AllVsIncludes=%VsInclude1%;%VsInclude2%;%VsInclude3%;%VsInclude4%;%VsInclude5%;%VsInclude6%;%VsInclude7%
REM Final INCLUDE that CL will use
SET INCLUDE=%shCommonsInclude%;%AllVsIncludes%;%AllDepsInclude%;%shCoreInclude%

SET PATH=%PATH%;%VS_PATH%

REM Setting lib dirs

SET glewReleaseLib=%depDir%\GLEW\lib\Release\Win32

SET shCommonsLib=%shCommons%\lib
SET shCommonsRelLib=%shCommonsLib%\sh_release
SET shCommonsDebLib=%shCommonsLib%\sh_debug

SET AllDepsLibs=%glewReleaseLib%

REM Win Lib dirs copied from VS proj
REM Try to trim this down or remove it all somehow
set VsLib1=%VC_HOME%\VC\lib
set VsLib2=%VC_HOME%\VC\atlmfc\lib
set VsLib3=C:\Program Files (x86)\Windows Kits\10\lib\10.0.10240.0\ucrt\x86
set VsLib4=C:\Program Files (x86)\Windows Kits\8.1\lib\winv6.3\um\x86
set VsLib5=C:\Program Files (x86)\Windows Kits\NETFXSDK\4.6.1\Lib\um\x86

set AllWinLibs=%VsLib1%;%VsLib2%;%VsLib3%;%VsLib4%;%VsLib5%


set symbols=/DWIN32 /DGLEW_STATIC /D_CONSOLE /D_UNICODE /DUNICODE 

set com_opt=/EHa /Oi /nologo
set config_opt=


set com_input_libs=user32.lib
set out_dir=projDir

set configuration=%1
set action=%2

if "%configuration%"==""  set configuration=SH_DEBUG
if "%action%"=="" set action=SH_BUILD


REM If no action is specified, set SH_BUILD as default
if "%action%"=="" set action=SH_BUILD

REM If no configuration is specified, set default to DEBUG
if "%configuration%"==""  set configuration=SH_DEBUG

if /I "%configuration%"=="SH_DEBUG" (
		set config_opt=/Od /ZI /Ob0
		set symbols=%symbols% /D_DEBUG /DSHADY_DEBUG 
		SET LIB=%shCommonsDebLib%
	) 
if /I "%configuration%"=="SH_RELEASE" (
		set config_opt=/Ox
		set symbols=%symbols% /DNDEBUG /DSHADY_RELEASE
		SET LIB=%shCommonsRelLib%
	)

::SET shCommonsRelLib in LIB first because AllWinLibs include path with parenthesys
::and  the IF statement breaks
SET LIB=%LIB%;%AllDepsLibs%;%AllWinLibs%