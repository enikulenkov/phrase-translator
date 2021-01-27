cmake_minimum_required(VERSION 3.14)

project(phrase-translator-cli LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core LinguistTools Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core LinguistTools Network REQUIRED)

set(TS_FILES phrase-translator-cli_en_US.ts)

add_executable(phrase-translator-cli
  main.cpp
  consoleui.cpp
  consoleui.h
  phrasetranslatorbase.h
  phrasetranslatorgoogle.cpp
  phrasetranslatorgoogle.h
  postag.cpp
  postag.h
  postagger.cpp
  postagger.h
  phrasepattern.cpp
  phrasepattern.h
  phrasegenerator.cpp
  phrasegenerator.h
  wordlist.cpp
  wordlist.h
  ${TS_FILES}
)
target_link_libraries(phrase-translator-cli
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    meta-greedy-tagger
    meta-sequence
    meta-io
    meta-index
    meta-parser
)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
