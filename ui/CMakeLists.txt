add_library(chat_ui STATIC)

qt_add_qml_module(chat_ui
    URI ChatUI
    VERSION 1.0
    QML_FILES
        ChatFrame.qml
)

target_link_libraries(chat_ui PUBLIC Qt6::Core Qt6::Qml Qt6::Quick)
target_include_directories(chat_ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})