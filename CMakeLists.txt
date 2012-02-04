# Preamble
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(CodaphelaLibrary)

# Architecture detection
IF(CYGWIN)
    OPTION(CodaphelaLibrary_FORCE_CYGWIN "Set this to ON to enable building on Cygwin. This is not guaranteed to work in the slightest," OFF)
    MARK_AS_ADVANCED(CodaphelaLibrary_FORCE_CYGWIN)
    IF(${CodaphelaLibrary_FORCE_CYGWIN})
        MESSAGE(WARNING "Cygwin is not a supported build environment -- use at own risk.")
    ELSE()
        MESSAGE(FATAL_ERROR "Cygwin is not a supported build environment.")
    ENDIF()
ELSEIF(APPLE)
    OPTION(CodaphelaLibrary_FORCE_APPLE "Set this to ON to enable building on Apple. This is not guaranteed to work in the slightest," OFF)
    MARK_AS_ADVANCED(CodaphelaLibrary_FORCE_APPLE)
    IF(${CodaphelaLibrary_FORCE_APPLE})
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
IF(${CMAKE_COMPILER_IS_GNUCXX} AND WIN32)
    ADD_DEFINITIONS(-DWIN_GNU_32)
ENDIF()

OPTION(CodaphelaLibrary_BUILD_SHARED_LIBRARIES "Set this to ON to build shared libraries, rather than static libraries." OFF)

# Sub-directories
ADD_SUBDIRECTORY(BaseLib)
ADD_SUBDIRECTORY(CoreLib)
ADD_SUBDIRECTORY(StandardLib)

# uninstall target
CONFIGURE_FILE(
  "${CodaphelaLibrary_SOURCE_DIR}/CMakeModules/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")