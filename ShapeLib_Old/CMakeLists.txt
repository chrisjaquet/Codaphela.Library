SET(LIB_NAME ShapeLib)
OPTION(${PROJECT_NAME}_BUILD_${LIB_NAME} "Set this to ON to build ${LIB_NAME}." OFF)

IF(${${PROJECT_NAME}_BUILD_${LIB_NAME}})

    # We need DirectX
    IF(NOT ${DirectX_FOUND})
        MESSAGE(SEND_ERROR "${LIB_NAME} requires DirectX, but DirectX_FOUND is set to ${DirectX_FOUND}.")
    ELSE()
        INCLUDE_DIRECTORIES(${DirectX_INCLUDE_DIR})
    ENDIF()

    SET(HEADER_FILES
                        Box.h
                        Capsule.h
                        CD3DTriangle.h
                        Cone.h
                        ConvexHull.h
                        Distances.h
                        Intersections.h
                        LineInfinite.h
                        LineSegment.h
                        Plane.h
                        Ray.h
                        Shape.h
                        ShapeHierachy.h
                        Shapes.h
                        ShapeTransformer.h
                        ShapeTypes.h
                        Sphere.h
                        Triangle.h
                        VertexArray.h
                    )

    SET(SOURCE_FILES 
                        Box.cpp
                        Capsule.cpp
                        Cone.cpp
                        ConvexHull.cpp
                        Distances.cpp
                        Intersections.cpp
                        LineInfinite.cpp
                        LineSegment.cpp
                        Plane.cpp
                        Ray.cpp
                        Shape.cpp
                        ShapeHierachy.cpp
                        ShapeTransformer.cpp
                        ShapeTypes.cpp
                        Sphere.cpp
                        Triangle.cpp
                        VertexArray.cpp
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