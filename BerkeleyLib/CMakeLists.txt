SET(LIB_NAME BerkeleyLib)
OPTION(${PROJECT_NAME}_BUILD_${LIB_NAME} "Set this to ON to build ${LIB_NAME}." OFF)

IF(${${PROJECT_NAME}_BUILD_${LIB_NAME}})
    SET(HEADER_FILES
                        BerkeleyDB.h
                    )

    SET(SOURCE_FILES 
                        BerkeleyDB.cpp
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
ENDIF()