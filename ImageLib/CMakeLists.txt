SET(LIB_NAME ImageLib)
SET(HEADER_FILES
                    crc32.h
                    deflate.h
                    inffast.h
                    inffixed.h
                    inflate.h
                    inftrees.h
                    png.h
                    pngconf.h
                    trees.h
                    zconf.h
                    zlib.h
                    zutil.h
                )

SET(SOURCE_FILES 
                    adler32.c
                    compress.c
                    crc32.c
                    deflate.c
                    gzio.c
                    infback.c
                    inffast.c
                    inflate.c
                    inftrees.c
                    png.c
                    pngerror.c
                    pnggccrd.c
                    pngget.c
                    pngmem.c
                    pngpread.c
                    pngread.c
                    pngrio.c
                    pngrtran.c
                    pngrutil.c
                    pngset.c
                    pngtest.c
                    pngtrans.c
                    pngvcrd.c
                    pngwio.c
                    pngwrite.c
                    pngwtran.c
                    pngwutil.c
                    trees.c
                    uncompr.c
                    zutil.c
                )

# Shared Library or Static                    
IF(${CodaphelaLibrary_BUILD_SHARED_LIBRARY})
    ADD_LIBRARY(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
ELSE()
    ADD_LIBRARY(${LIB_NAME} ${SOURCE_FILES} ${HEADER_FILES})
ENDIF()
# TARGET_LINK_LIBRARIES(${LIB_NAME} )

# Installation
INSTALL(TARGETS ${LIB_NAME}
        LIBRARY DESTINATION lib${LIB_ARCH}
        ARCHIVE DESTINATION lib${LIB_ARCH}
        RUNTIME DESTINATION bin)
INSTALL(FILES ${HEADER_FILES}
        DESTINATION include/${PROJECT_NAME}/${LIB_NAME})
