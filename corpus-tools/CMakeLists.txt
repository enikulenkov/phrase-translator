cmake_minimum_required(VERSION 3.14)

project(corpus-tools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(corpus-tools
  main.cpp
)

target_link_libraries(corpus-tools
    Qt${QT_VERSION_MAJOR}::Core
    phrase-translator-common
    meta-greedy-tagger
    meta-sequence
    meta-io
    meta-index
    meta-parser
)
