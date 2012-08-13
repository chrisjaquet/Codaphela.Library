SET(LIB_NAME DirectXLib)
OPTION(${PROJECT_NAME}_BUILD_${LIB_NAME} "Set this to ON to build ${LIB_NAME}." ON)

IF(${${PROJECT_NAME}_BUILD_${LIB_NAME}})

    # We need DirectX
    IF(NOT ${DirectX_FOUND})
        MESSAGE(SEND_ERROR "${LIB_NAME} requires DirectX, but DirectX_FOUND is set to ${DirectX_FOUND}.")
    ELSE()
        INCLUDE_DIRECTORIES(${DirectX_INCLUDE_DIR})
    ENDIF()

    SET(HEADER_FILES
                        Constants.h
                        DebugMovementFlightStyle.h
                        DebugMovementWalkStyle.h
                        Direct3DGlobal.h
                        DirectXGlobal.h
                        FlexibleVertexFormats.h
                        TextureStates.h
                    )

    SET(SOURCE_FILES 
                        DebugMovementFlightStyle.cpp
                        DebugMovementWalkStyle.cpp
                        Direct3DGlobal.cpp
                        DirectXGlobal.cpp
                    )

    # Shared Library or Static                    
    IF(${CodaphelaLibrary_BUILD_SHARED_LIBRARY})
        ADD_LIBRARY(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
    ELSE()
        ADD_LIBRARY(${LIB_NAME} ${SOURCE_FILES} ${HEADER_FILES})
    ENDIF()
    TARGET_LINK_LIBRARIES(${LIB_NAME} ${DirectX_LIBRARY})

    # Installation
    INSTALL(TARGETS ${LIB_NAME}
            LIBRARY DESTINATION lib${LIB_ARCH}
            ARCHIVE DESTINATION lib${LIB_ARCH}
            RUNTIME DESTINATION bin)
    INSTALL(FILES ${HEADER_FILES}
            DESTINATION include/${PROJECT_NAME}/${LIB_NAME})
ENDIF()