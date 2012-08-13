SET(LIB_NAME WorldLib)
OPTION(${PROJECT_NAME}_BUILD_${LIB_NAME} "Set this to ON to build ${LIB_NAME}." ON)

IF(${${PROJECT_NAME}_BUILD_${LIB_NAME}})

    # We need DirectX
    IF(NOT ${DirectX_FOUND})
        MESSAGE(SEND_ERROR "${LIB_NAME} requires DirectX, but DirectX_FOUND is set to ${DirectX_FOUND}.")
    ELSE()
        INCLUDE_DIRECTORIES(${DirectX_INCLUDE_DIR})
    ENDIF()

    SET(HEADER_FILES
                        Animation.h
                        AnimationConverter.h
                        AnimationInvokeAnimation.h
                        AnimationManager.h
                        CameraInstance.h
                        ConversionMapper.h
                        GraphicsDynamicVertexBuffer.h
                        GraphicsInstance.h
                        GraphicsMaterial.h
                        GraphicsObject.h
                        GraphicsPrimitive.h
                        GraphicsState.h
                        GraphicsTexture.h
                        GraphicsVertexBuffer.h
                        GraphicsViewport.h
                        HomeGrid.h
                        InstanceConverter.h
                        Interpolator.h
                        InterpolatorArray.h
                        LightInstance.h
                        Map2D.h
                        MaterialConverter.h
                        MatrixArray.h
                        MatrixSelectionConverter.h
                        MeshAdjuster.h
                        MeshConverter.h
                        MeshInstance.h
                        MeshObject.h
                        MeshSelectionConverter.h
                        Movement.h
                        ParticleSystem.h
                        Position.h
                        PositionHelper.h
                        Quad2D.h
                        Rotation.h
                        SceneConverter.h
                        SelectionOverrides.h
                        TextureConverter.h
                        TransformNode.h
                        VectorArray.h
                        World.h
                        WorldEditor.h
                        WorldLists.h
                    )

    SET(SOURCE_FILES 
                        Animation.cpp
                        AnimationConverter.cpp
                        AnimationInvokeAnimation.cpp
                        AnimationManager.cpp
                        CameraInstance.cpp
                        ConversionMapper.cpp
                        GraphicsDynamicVertexBuffer.cpp
                        GraphicsInstance.cpp
                        GraphicsMaterial.cpp
                        GraphicsObject.cpp
                        GraphicsPrimitive.cpp
                        GraphicsState.cpp
                        GraphicsTexture.cpp
                        GraphicsVertexBuffer.cpp
                        GraphicsViewport.cpp
                        HomeGrid.cpp
                        InstanceConverter.cpp
                        InterpolatorArray.cpp
                        LightInstance.cpp
                        Map2D.cpp
                        MaterialConverter.cpp
                        MatrixSelectionConverter.cpp
                        MeshAdjuster.cpp
                        MeshConverter.cpp
                        MeshInstance.cpp
                        MeshObject.cpp
                        MeshSelectionConverter.cpp
                        Movement.cpp
                        ParticleSystem.cpp
                        Position.cpp
                        PositionHelper.cpp
                        Quad2D.cpp
                        Rotation.cpp
                        SceneConverter.cpp
                        TextureConverter.cpp
                        TransformNode.cpp
                        VectorArray.cpp
                        World.cpp
                        WorldEditor.cpp
                        WorldLists.cpp
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