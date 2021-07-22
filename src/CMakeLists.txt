# file: CMakeLists.txt
# author: kyunggeun lee
# brief: build FileIOSamples project
cmake_minimum_required(VERSION 3.16)

project(FileIOSamples)

add_executable(ReadPrint ReadPrint.cpp)
add_executable(ReadBinaryPrintHex ReadBinaryPrintHex.cpp)

message(STATUS ${CMAKE_CXX_COMPILER_ID})
message(STATUS ${CMAKE_CXX_COMPILER_VERSION})
message(STATUS ${CMAKE_GENERATOR})

file(GLOB MY_TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.txt)

if(${CMAKE_GENERATOR} EQUAL "CodeBlocks - MinGW Makefiles")
    file(COPY ${MY_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(UNIX)
    file(COPY ${MY_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(MSVC)
    message(${MY_TEST_FILES})
    file(COPY ${MY_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${MY_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
endif()


