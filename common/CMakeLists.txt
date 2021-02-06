cmake_minimum_required(VERSION 3.14)

project(phrase-translator-common LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core LinguistTools Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core LinguistTools Network REQUIRED)

add_library(phrase-translator-common
  phrasetranslatorbase.h
  phrasetranslatorgoogle.cpp
  phrasetranslatorgoogle.h
  postag.cpp
  postag.h
  postagger.cpp
  postagger.h
  phrasepattern.cpp
  phrasepattern.h
  phrasegeneratorbase.h
  phrasegeneratorrandom.cpp
  phrasegeneratorrandom.h
  phrasegeneratormarkov.cpp
  phrasegeneratormarkov.h
  wordlist.cpp
  wordlist.h
)

target_link_libraries(phrase-translator-common
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    meta-greedy-tagger
    meta-sequence
    meta-io
    meta-index
    meta-parser
)

# TODO: How install works and how to do it properly?
target_include_directories(phrase-translator-common INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>)
