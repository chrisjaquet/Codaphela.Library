@echo off

set INST_DIR="D:\Work\Devel\0Libraries\0PreBuilt"

REM set GENERATOR="MinGW Makefiles"
set GENERATOR="CodeBlocks - MinGW Makefiles"
REM set GENERATOR="Visual Studio 10"
REM set GENERATOR="Eclipse CDT4 - MinGW Makefiles"

echo Generator is %GENERATOR%

set CUR_DIR=%CD%
set INST_DIR_UNIX=%INST_DIR:\=/%
set BUILD_DIR=%CUR_DIR%\..\build\Codaphela.Library
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
