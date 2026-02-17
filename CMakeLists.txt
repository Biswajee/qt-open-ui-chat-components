cmake_minimum_required(VERSION 3.16)

project(qt-open-ui-workspace LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(ARCH_DIR "x64")
set(BUILD_DIR "${CMAKE_SOURCE_DIR}/__Builds/${ARCH_DIR}/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_DIR}/lib")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Network)

add_subdirectory(ui)
add_subdirectory(example)

# Packaging
set(CPACK_PACKAGE_NAME "Qt Open UI Chat")
set(CPACK_PACKAGE_VENDOR "Biswajit Roy (@biswajee)")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Qt Open Web UI Chat Application")
set(CPACK_PACKAGE_CONTACT "GitHub <github.com/Biswajee/qt-open-ui-chat-components>")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "Qt Open UI Chat")
    set(CPACK_NSIS_PACKAGE_NAME "QtOpenUIChat")
    # Need to install to bin/ for execution to work relative to DLLs
    set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB;TGZ")
    set(CPACK_DEBIAN_PACKAGE_NAME "qt-open-ui-chat")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
endif()

include(CPack)
