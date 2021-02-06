cmake_minimum_required(VERSION 3.14)

project(phrase-translator LANGUAGES CXX)

add_subdirectory(phrase-translator-cli/)
add_subdirectory(common/)
add_subdirectory(meta/)
add_subdirectory(corpus-tools/)
