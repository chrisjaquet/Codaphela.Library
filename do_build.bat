@echo off

set INST_DIR="D:\Work\Devel\0Libraries\0PreBuilt"

if [%1]==[] goto gen0
if [%1]==[0] goto gen0
if [%1]==[1] goto gen1
if [%1]==[2] goto gen2
if [%1]==[3] goto gen3
if [%1]==[4] goto gen4
if [%1]==[5] goto gen5
if [%1]==[6] goto gen6
if [%1]==[7] goto gen7
if [%1]==[8] goto gen8
if [%1]==[9] goto gen9
if [%1]==[10] goto gen10
if [%1]==[11] goto gen11
if [%1]==[12] goto gen12
if [%1]==[13] goto gen13
if [%1]==[14] goto gen14

echo [do_build] Invalid generator selected. Input was: %1
goto errornow

:gen0
set GENERATOR="MinGW Makefiles"
goto dobuild
:gen1
set GENERATOR="CodeBlocks - MinGW Makefiles"
goto dobuild
:gen2
set GENERATOR="CodeBlocks - NMake Makefiles" REM FIXME Does not work yet
goto dobuild
:gen3
set GENERATOR="Eclipse CDT4 - MinGW Makefiles"
goto dobuild
:gen4
set GENERATOR="Eclipse CDT4 - NMake Makefiles"
goto dobuild
:gen5
set GENERATOR="Visual Studio 8 2005"
goto dobuild
:gen6
set GENERATOR="Visual Studio 8 2005 Win64"
goto dobuild
:gen7
set GENERATOR="Visual Studio 9 2008"
goto dobuild
:gen8
set GENERATOR="Visual Studio 9 2008 IA64"
goto dobuild
:gen9
set GENERATOR="Visual Studio 9 2008 Win64"
goto dobuild
:gen10
set GENERATOR="Visual Studio 10"
goto dobuild
:gen11
set GENERATOR="Visual Studio 10 IA64"
goto dobuild
:gen12
set GENERATOR="Visual Studio 10 Win64"
goto dobuild
:gen13
set GENERATOR="Visual Studio 11"
goto dobuild
:gen14
set GENERATOR="Visual Studio 11 Win64"
goto dobuild

:dobuild
echo [do_build] Generator is %GENERATOR%

set CUR_DIR=%CD%
set INST_DIR_UNIX=%INST_DIR:\=/%
set GEN_DIR=%GENERATOR: =%
set BUILD_DIR=%CUR_DIR%\..\build\Codaphela.Library\%GEN_DIR%
mkdir %BUILD_DIR%
cd %BUILD_DIR%
mkdir Debug
cd Debug
set BUILD_COMMON_STRING=-G %GENERATOR% %CUR_DIR% -DCMAKE_INSTALL_PREFIX=%INST_DIR_UNIX% -DCodaphelaLibrary_BUILD_SHARED_LIBRARY=OFF
cmake %BUILD_COMMON_STRING% -DCMAKE_BUILD_TYPE="Debug"
REM mingw32-make install
REM cd %BUILD_DIR%
REM mkdir Release
REM cd Release
REM cmake %BUILD_COMMON_STRING% -DCMAKE_BUILD_TYPE="Release"
REM mingw32-make install
cd %CUR_DIR%

goto done

:errornow
echo [do_build] An Error Occurred!

:done
echo [do_build] Done!