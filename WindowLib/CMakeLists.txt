SET(LIB_NAME WindowLib)
SET(HEADER_FILES
                    Block.h
                    BlockParameters.h
                    Border.h
                    BorderParameters.h
                    Caret.h
                    Component.h
                    ComponentFactory.h
                    ComponentInput.h
                    ComponentInputCommand.h
                    ComponentInputDevice.h
                    ComponentInputKeyboard.h
                    ComponentInputMotion.h
                    ComponentInputMouse.h
                    ComponentInputNumKey.h
                    ComponentInputPrintable.h
                    ComponentListener.h
                    ComponentPointers.h
                    Container.h
                    ContainerCell.h
                    Drawable.h
                    FillContainer.h
                    FixedContainer.h
                    FlipContainer.h
                    FlowContainer.h
                    Focus.h
                    FocusListener.h
                    GraphicalTextEditor.h
                    GridCell.h
                    GridContainer.h
                    Label.h
                    PlainGraphicalTextEditor.h
                    QuadParameters.h
                    SlidingMenu.h
                    SystemPointer.h
                    Text.h
                    TextData.h
                    TextField.h
                    TextFieldParameters.h
                    TextParameters.h
                    Toolbar.h
                    Viewport.h
                    Widget.h
                    Window.h
                )

SET(SOURCE_FILES 
                    Block.cpp
                    BlockParameters.cpp
                    Border.cpp
                    BorderParameters.cpp
                    Caret.cpp
                    Component.cpp
                    ComponentFactory.cpp
                    ComponentInput.cpp
                    ComponentInputCommand.cpp
                    ComponentInputDevice.cpp
                    ComponentInputKeyboard.cpp
                    ComponentInputMotion.cpp
                    ComponentInputMouse.cpp
                    ComponentInputNumKey.cpp
                    ComponentInputPrintable.cpp
                    ComponentPointers.cpp
                    Container.cpp
                    ContainerCell.cpp
                    Drawable.cpp
                    FillContainer.cpp
                    FixedContainer.cpp
                    FlipContainer.cpp
                    FlowContainer.cpp
                    Focus.cpp
                    GraphicalTextEditor.cpp
                    GridCell.cpp
                    GridContainer.cpp
                    Label.cpp
                    PlainGraphicalTextEditor.cpp
                    QuadParameters.cpp
                    SlidingMenu.cpp
                    SystemPointer.cpp
                    Text.cpp
                    TextData.cpp
                    TextField.cpp
                    TextFieldParameters.cpp
                    TextParameters.cpp
                    Toolbar.cpp
                    Viewport.cpp
                    Widget.cpp
                    Window.cpp
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
