add_executable(qt-open-ui-chat main.cpp)

find_package(Qt6 COMPONENTS Core Gui Qml Quick QuickControls2 REQUIRED)

# Register the example's QML
qt_add_qml_module(qt-open-ui-chat
    URI ChatExample
    VERSION 1.0
    QML_FILES Main.qml
)

target_link_libraries(qt-open-ui-chat PRIVATE Qt6::Core Qt6::Qml Qt6::Quick Qt6::QuickControls2 open-web-ui open-web-uiplugin)

# Custom commands for Windows deployment (windeployqt)
if(WIN32)
    # Find windeployqt
    if(TARGET Qt6::windeployqt)
        get_target_property(WINDEPLOYQT_EXECUTABLE Qt6::windeployqt IMPORTED_LOCATION)
    else()
        get_target_property(_qt_bin_dir Qt6::qmake IMPORTED_LOCATION)
        get_filename_component(_qt_bin_dir ${_qt_bin_dir} DIRECTORY)
        find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS ${_qt_bin_dir})
    endif()

    if(WINDEPLOYQT_EXECUTABLE)
        # Scan QML directories to ensure imports are found
        set(QML_DIRS 
            "${CMAKE_SOURCE_DIR}/ui" 
            "${CMAKE_SOURCE_DIR}/example"
        )

        add_custom_command(TARGET qt-open-ui-chat POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Running windeployqt..."
            COMMAND ${WINDEPLOYQT_EXECUTABLE} 
                --qmldir "${CMAKE_SOURCE_DIR}/ui"
                --qmldir "${CMAKE_SOURCE_DIR}/example"
                --dir $<TARGET_FILE_DIR:qt-open-ui-chat>
                --no-compiler-runtime
                --force-openssl
                $<TARGET_FILE:qt-open-ui-chat>
            COMMENT "Deploying Qt dependencies"
        )
    endif()
endif()

install(TARGETS qt-open-ui-chat RUNTIME DESTINATION bin)

if(WIN32)
    # Install dependencies deployed by windeployqt
    install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
            DESTINATION bin
            USE_SOURCE_PERMISSIONS
            FILES_MATCHING
            PATTERN "*.dll"
            PATTERN "*.qm"
            PATTERN "plugins"
            PATTERN "qml"
            PATTERN "translations"
    )
endif()
