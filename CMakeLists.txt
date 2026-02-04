cmake_minimum_required(VERSION 3.16)

project(QtChatUI LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(ARCH_DIR "x64")
set(BUILD_DIR "${CMAKE_SOURCE_DIR}/__Builds/${ARCH_DIR}/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_DIR}/lib")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_subdirectory(ui)
add_subdirectory(example)