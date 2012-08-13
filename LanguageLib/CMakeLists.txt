SET(LIB_NAME LanguageLib)
OPTION(${PROJECT_NAME}_BUILD_${LIB_NAME} "Set this to ON to build ${LIB_NAME}." ON)

IF(${${PROJECT_NAME}_BUILD_${LIB_NAME}})
    SET(HEADER_FILES
                        CharElement.h
                        Definition.h
                        DefinitionElement.h
                        ElementTypes.h
                        EndElement.h
                        IdentifierElement.h
                        Meta.h
                        MetaParser.h
                        MetaTokeniser.h
                        NodeConstructor.h
                        NodeElement.h
                        TextElement.h
                        TokenArray.h
                        TokenDumper.h
                        Tokens.h
                        TokenTree.h
                        TypeElement.h
                    )

    SET(SOURCE_FILES 
                        Definition.cpp
                        Meta.cpp
                        MetaParser.cpp
                        MetaTokeniser.cpp
                        NodeConstructor.cpp
                        TokenArray.cpp
                        TokenDumper.cpp
                        Tokens.cpp
                        TokenTree.cpp
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