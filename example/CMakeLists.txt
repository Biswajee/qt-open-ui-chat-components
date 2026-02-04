add_executable(chat_example main.cpp)

find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)

qt_add_resources(chat_example "resources"
    PREFIX "/"
    FILES Main.qml
)

add_custom_command(TARGET chat_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Gui>
        $<TARGET_FILE:Qt6::Qml>
        $<TARGET_FILE:Qt6::Quick>
        $<TARGET_FILE:Qt6::Network>
        $<TARGET_FILE_DIR:chat_example>
)

add_custom_command(TARGET chat_example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:chat_example>/platforms
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:Qt6::Gui>/../plugins/platforms/qwindows.dll"
        $<TARGET_FILE_DIR:chat_example>/platforms/
)

target_link_libraries(chat_example PRIVATE Qt6::Core Qt6::Qml Qt6::Quick chat_ui)
qt_add_qml_module(chat_example
    URI ChatExample
    QML_FILES Main.qml
)