@ECHO OFF

SET INST_DIR="D:\Work\Devel\0Libraries\0PreBuilt"

IF [%1]==[] GOTO noinput
IF [%1]==[1] GOTO gen1
IF [%1]==[2] GOTO gen2
IF [%1]==[3] GOTO gen3
IF [%1]==[4] GOTO gen4
IF [%1]==[5] GOTO gen5
IF [%1]==[6] GOTO gen6
IF [%1]==[7] GOTO gen7
IF [%1]==[8] GOTO gen8
IF [%1]==[9] GOTO gen9
IF [%1]==[A] GOTO gen10
IF [%1]==[B] GOTO gen11
IF [%1]==[C] GOTO gen12
IF [%1]==[D] GOTO gen13
IF [%1]==[E] GOTO gen14
IF [%1]==[F] GOTO gen15

ECHO [do_build] Invalid generator selected. Input was: %1
GOTO errornow

:noinput
ECHO Generator Options:
ECHO ==================
ECHO.
ECHO     1. MinGW Makefiles
ECHO     2. CodeBlocks - MinGW Makefiles
ECHO     3. CodeBlocks - NMake Makefiles (Broken)
ECHO     4. Eclipse CDT4 - MinGW Makefiles
ECHO     5. Eclipse CDT4 - NMake Makefiles
ECHO     6. Visual Studio 8 2005
ECHO     7. Visual Studio 8 2005 Win64
ECHO     8. Visual Studio 9 2008
ECHO     9. Visual Studio 9 2008 IA64
ECHO     A. Visual Studio 9 2008 Win64
ECHO     B. Visual Studio 10
ECHO     C. Visual Studio 10 IA64
ECHO     D. Visual Studio 10 Win64
ECHO     E. Visual Studio 11
ECHO     F. Visual Studio 11 Win64
ECHO.
CHOICE /CS /N /C "123456789ABCDEF" /M "Choose Generator (Case Sensitive): "
IF ERRORLEVEL 255 GOTO noinput
IF ERRORLEVEL 1 GOTO selection
IF ERRORLEVEL 0 GOTO errornow
:selection
SET dest=gen%ERRORLEVEL% 
GOTO %dest%

:gen1
SET GENERATOR="MinGW Makefiles"
GOTO dobuild
:gen2
SET GENERATOR="CodeBlocks - MinGW Makefiles"
GOTO dobuild
:gen3
SET GENERATOR="CodeBlocks - NMake Makefiles" REM FIXME Does not work yet
GOTO dobuild
:gen4
SET GENERATOR="Eclipse CDT4 - MinGW Makefiles"
GOTO dobuild
:gen5
SET GENERATOR="Eclipse CDT4 - NMake Makefiles"
GOTO dobuild
:gen6
SET GENERATOR="Visual Studio 8 2005"
GOTO dobuild
:gen7
SET GENERATOR="Visual Studio 8 2005 Win64"
GOTO dobuild
:gen8
SET GENERATOR="Visual Studio 9 2008"
GOTO dobuild
:gen9
SET GENERATOR="Visual Studio 9 2008 IA64"
GOTO dobuild
:gen10
SET GENERATOR="Visual Studio 9 2008 Win64"
GOTO dobuild
:gen11
SET GENERATOR="Visual Studio 10"
GOTO dobuild
:gen12
SET GENERATOR="Visual Studio 10 IA64"
GOTO dobuild
:gen13
SET GENERATOR="Visual Studio 10 Win64"
GOTO dobuild
:gen14
SET GENERATOR="Visual Studio 11"
GOTO dobuild
:gen15
SET GENERATOR="Visual Studio 11 Win64"
GOTO dobuild

:dobuild
echo [do_build] Generator is %GENERATOR%

SET CUR_DIR=%CD%
SET INST_DIR_UNIX=%INST_DIR:\=/%
SET GEN_DIR=%GENERATOR: =%
SET BUILD_DIR=%CUR_DIR%\..\build\Codaphela.Library\%GEN_DIR%
mkdir %BUILD_DIR%
cd %BUILD_DIR%
mkdir Debug
cd Debug
SET BUILD_COMMON_STRING=-G %GENERATOR% %CUR_DIR% -DCMAKE_INSTALL_PREFIX=%INST_DIR_UNIX% -DCodaphelaLibrary_BUILD_SHARED_LIBRARY=OFF
cmake %BUILD_COMMON_STRING% -DCMAKE_BUILD_TYPE="Debug"
REM mingw32-make install
REM cd %BUILD_DIR%
REM mkdir Release
REM cd Release
REM cmake %BUILD_COMMON_STRING% -DCMAKE_BUILD_TYPE="Release"
REM mingw32-make install
cd %CUR_DIR%

GOTO done

:errornow
echo [do_build] An Error Occurred!

:done
echo [do_build] Done!