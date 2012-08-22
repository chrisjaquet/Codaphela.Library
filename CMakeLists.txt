# Preamble
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(CodaphelaLibrary)

# Architecture detection
IF(CYGWIN)
    OPTION(${PROJECT_NAME}_FORCE_CYGWIN "Set this to ON to enable building on Cygwin. This is not guaranteed to work in the slightest," OFF)
    MARK_AS_ADVANCED(${PROJECT_NAME}_FORCE_CYGWIN)
    IF(${${PROJECT_NAME}_FORCE_CYGWIN})
        MESSAGE(WARNING "Cygwin is not a supported build environment -- use at own risk.")
    ELSE()
        MESSAGE(FATAL_ERROR "Cygwin is not a supported build environment.")
    ENDIF()
ELSEIF(APPLE)
    OPTION(${PROJECT_NAME}_FORCE_APPLE "Set this to ON to enable building on Apple. This is not guaranteed to work in the slightest," OFF)
    MARK_AS_ADVANCED(${PROJECT_NAME}_FORCE_APPLE)
    IF(${${PROJECT_NAME}_FORCE_APPLE})
        MESSAGE(WARNING "Apple is not a supported build environment -- use at own risk.")
    ELSE()
        MESSAGE(FATAL_ERROR "Apple is not a supported build environment.")
    ENDIF()
ELSEIF(WIN32)
    # Windows has been found
    SET(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/win)
ELSEIF(UNIX)
    # Linux has been found
    SET(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/lin)
ELSE()
    MESSAGE(FATAL_ERROR "Your build system (${CMAKE_SYSTEM_NAME}) is not recognised.")
ENDIF()

# Determine architecture bitness
IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    MESSAGE(STATUS "Building for 32-Bit System")
    SET(ARCH_BITNESS "32")
    SET(LIB_ARCH "")
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    MESSAGE(STATUS "Building for 64-Bit System")
    SET(ARCH_BITNESS "64")
    SET(LIB_ARCH "64")
ELSE()
    MESSAGE(FATAL_ERROR "Could not determine bitness (32 or 64) of architecture.")
ENDIF()

SET(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}${ARCH_BITNESS})

# Add the custom .cmake file path
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH})

# Add some custom directories

# Find Required Libraries
FIND_PACKAGE(DirectX)

# Include Directories
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Definitions for Debug Mode
IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    SET(CMAKE_DEBUG_POSTFIX "d")
    ADD_DEFINITIONS(-D_DEBUG)
ELSE()
    SET(CMAKE_RELEASE_POSTFIX "")
    ADD_DEFINITIONS(-DNDEBUG) 
ENDIF()

# Extra Definitions
IF(WIN32)
    IF(${CMAKE_COMPILER_IS_GNUCXX})
        MESSAGE(STATUS "Using the GNUCXX compiler on windows -- adding suitable definition")
        ADD_DEFINITIONS(-DWIN_GNU_32)
    ENDIF()
    IF(${MSVC})
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
    ENDIF()
ENDIF()

OPTION(${PROJECT_NAME}_BUILD_SHARED_LIBRARIES "Set this to ON to build shared libraries, rather than static libraries." OFF)

IF(NOT ${${PROJECT_NAME}_BUILD_SHARED_LIBRARIES})
    ADD_DEFINITIONS(-D_LIB)
ENDIF()

# Extra Compiler Optins
IF(${CMAKE_COMPILER_IS_GNUCXX})
    ADD_DEFINITIONS(-Wno-write-strings)
ENDIF()

# Sub-directories
ADD_SUBDIRECTORY(BaseLib)
ADD_SUBDIRECTORY(CoreLib)
ADD_SUBDIRECTORY(StandardLib)
ADD_SUBDIRECTORY(BerkeleyLib)
ADD_SUBDIRECTORY(CppParserLib)
ADD_SUBDIRECTORY(DirectXLib)
ADD_SUBDIRECTORY(GameLib)
ADD_SUBDIRECTORY(ImageLib)
ADD_SUBDIRECTORY(InputLib)
ADD_SUBDIRECTORY(LanguageLib)
ADD_SUBDIRECTORY(ShapeLib_Old)
ADD_SUBDIRECTORY(SupportLib)
ADD_SUBDIRECTORY(TestLib)
ADD_SUBDIRECTORY(WindowLib)
ADD_SUBDIRECTORY(WorldLib)

# uninstall target
CONFIGURE_FILE(
  "${${PROJECT_NAME}_SOURCE_DIR}/CMakeModules/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
