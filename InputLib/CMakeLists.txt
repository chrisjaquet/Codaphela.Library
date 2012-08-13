SET(LIB_NAME InputLib)
OPTION(${PROJECT_NAME}_BUILD_${LIB_NAME} "Set this to ON to build ${LIB_NAME}." ON)

IF(${${PROJECT_NAME}_BUILD_${LIB_NAME}})
    SET(HEADER_FILES
                        Input.h
                        InputActions.h
                        InputCategories.h
                        InputCategory.h
                        InputCategoryGeneric.h
                        InputChord.h
                        InputChordCriteria.h
                        InputChordCriteriaDesc.h
                        InputChordDesc.h
                        InputChordDescs.h
                        InputChordReader.h
                        InputChords.h
                        InputDataFormat.h
                        InputDataFormats.h
                        InputDevice.h
                        InputDeviceCopyContext.h
                        InputDeviceDesc.h
                        InputDevicePointerArray.h
                        InputDevices.h
                        InputDevicesReader.h
                        InputDeviceState.h
                        InputDeviceValue.h
                        InputDeviceValueHistory.h
                        InputDeviceVariable.h
                        InputDeviceVariableCondition.h
                        InputDeviceVariableDesc.h
                        InputDeviceVariableListener.h
                        InputDeviceVariables.h
                        InputDeviceVariableValue.h
                        InputDeviceVariableValueConditionDesc.h
                        InputDeviceVariableValueDesc.h
                        InputDeviceVirtualDeviceArray.h
                        InputListener.h
                        InputSourceChannel.h
                        InputSourceDesc.h
                        InputSourceEvaluator.h
                        InputSourceValue.h
                        InputVirtualDevice.h
                        InputVirtualDeviceCommonality.h
                        InputVirtualDeviceDesc.h
                        InputVirtualDeviceReader.h
                        InputVirtualDeviceSource.h
                        InputVirtualDeviceSwitch.h
                        InputVirtualSourceDesc.h
                        KeyboardKeyList.h
                        NativeDetail.h
                        ProgramDeviceDetail.h
                        ProgramInput.h
                        WinDirectInput.h
                        WinInput.h
                        WinRaw.h
                        WinXInput.h
                    )

    SET(SOURCE_FILES 
                        Input.cpp
                        InputActions.cpp
                        InputCategories.cpp
                        InputCategory.cpp
                        InputCategoryGeneric.cpp
                        InputChord.cpp
                        InputChordCriteria.cpp
                        InputChordCriteriaDesc.cpp
                        InputChordDesc.cpp
                        InputChordDescs.cpp
                        InputChordReader.cpp
                        InputChords.cpp
                        InputDataFormat.cpp
                        InputDataFormats.cpp
                        InputDevice.cpp
                        InputDeviceCopyContext.cpp
                        InputDeviceDesc.cpp
                        InputDevices.cpp
                        InputDevicesReader.cpp
                        InputDeviceState.cpp
                        InputDeviceValue.cpp
                        InputDeviceVariable.cpp
                        InputDeviceVariableCondition.cpp
                        InputDeviceVariableDesc.cpp
                        InputDeviceVariables.cpp
                        InputDeviceVariableValue.cpp
                        InputDeviceVariableValueConditionDesc.cpp
                        InputDeviceVariableValueDesc.cpp
                        InputSourceChannel.cpp
                        InputSourceDesc.cpp
                        InputSourceEvaluator.cpp
                        InputSourceValue.cpp
                        InputVirtualDevice.cpp
                        InputVirtualDeviceCommonality.cpp
                        InputVirtualDeviceDesc.cpp
                        InputVirtualDeviceReader.cpp
                        InputVirtualDeviceSource.cpp
                        InputVirtualDeviceSwitch.cpp
                        InputVirtualSourceDesc.cpp
                        KeyboardKeyList.cpp
                        NativeDetail.cpp
                        ProgramDeviceDetail.cpp
                        ProgramInput.cpp
                        WinDirectInput.cpp
                        WinInput.cpp
                        WinRaw.cpp
                        WinXInput.cpp
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