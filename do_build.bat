@echo off

set INST_DIR="D:\Work\Devel\0Libraries\0PreBuilt"

REM set GENERATOR="MinGW Makefiles"
set GENERATOR="CodeBlocks - MinGW Makefiles"
REM set GENERATOR="CodeBlocks - NMake Makefiles" REM FIXME Does not work yet
REM set GENERATOR="Eclipse CDT4 - MinGW Makefiles"
REM set GENERATOR="Eclipse CDT4 - NMake Makefiles"
REM set GENERATOR="Visual Studio 8 2005"
REM set GENERATOR="Visual Studio 8 2005 Win64"
REM set GENERATOR="Visual Studio 9 2008"
REM set GENERATOR="Visual Studio 9 2008 IA64"
REM set GENERATOR="Visual Studio 9 2008 Win64"
REM set GENERATOR="Visual Studio 10"
REM set GENERATOR="Visual Studio 10 IA64"
REM set GENERATOR="Visual Studio 10 Win64"
REM set GENERATOR="Visual Studio 11"
REM set GENERATOR="Visual Studio 11 Win64"

echo Generator is %GENERATOR%

set CUR_DIR=%CD%
set INST_DIR_UNIX=%INST_DIR:\=/%
set GEN_DIR=%GENERATOR: =%
set BUILD_DIR=%CUR_DIR%\..\build\Codaphela.Library\%GEN_DIR%
mkdir %BUILD_DIR%
cd %BUILD_DIR%
mkdir Debug
cd Debug
cmake -G %GENERATOR% %CUR_DIR% -DCMAKE_INSTALL_PREFIX=%INST_DIR_UNIX% -DCodaphelaLibrary_BUILD_SHARED_LIBRARY=ON -DCMAKE_BUILD_TYPE="Debug"
REM mingw32-make install
REM cd %BUILD_DIR%
REM mkdir Release
REM cd Release
REM cmake -G %GENERATOR% %CUR_DIR% -DCMAKE_INSTALL_PREFIX=%INST_DIR_UNIX% -DCodaphelaLibrary_BUILD_SHARED_LIBRARY=ON -DCMAKE_BUILD_TYPE="Release"
REM mingw32-make install
cd %CUR_DIR%
