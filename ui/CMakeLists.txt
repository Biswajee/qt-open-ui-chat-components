add_library(open-web-ui STATIC)

qt_add_qml_module(open-web-ui
    URI ChatUI
    VERSION 1.0
    SOURCES
        ChatModel.h
        ChatModel.cpp
    QML_FILES
        ChatFrame.qml
)

target_link_libraries(open-web-ui PUBLIC Qt6::Core Qt6::Qml Qt6::Quick Qt6::Network)
target_include_directories(open-web-ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
