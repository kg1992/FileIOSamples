# file: CMakeLists.txt
# author: kyunggeun lee
# brief: build FileIOSamples project
cmake_minimum_required(VERSION 3.16)

project(FileIOSamples)

find_package(ZLIB QUIET 1.2.1)

add_executable(PipePrint PipePrint.cpp)
add_executable(ReadPrint ReadPrint.cpp)
add_executable(ReadBinaryPrintHex ReadBinaryPrintHex.cpp)
add_executable(CopyFile CopyFile.cpp)
add_executable(FileSize FileSize.cpp)
add_executable(FileEqual FileEqual.cpp)
add_executable(PODToBinaryFile PODToBinaryFile.cpp)
add_executable(Book Book.cpp)
add_executable(DeleteFile DeleteFile.cpp)
add_executable(RenameFile RenameFile.cpp)
if(MSVC)
    add_executable(MoveToRecycleBinA MoveToRecycleBin.cpp)
    add_executable(MoveToRecycleBinW MoveToRecycleBin.cpp)
    target_compile_definitions (MoveToRecycleBinW PRIVATE -D_UNICODE -DUNICODE)
endif()
add_executable(ZipCompress ZipCompress.cpp)
if( ZLIB_FOUND )
    target_link_libraries(ZipCompress PRIVATE ZLIB::ZLIB)
    target_include_directories(ZipCompress PRIVATE ${ZLIB_INCLUDE_DIR})
endif()
add_executable(ListFolder ListFolder.cpp)
target_compile_features(ListFolder PRIVATE cxx_std_17)

message(STATUS ${CMAKE_CXX_COMPILER_ID})
message(STATUS ${CMAKE_CXX_COMPILER_VERSION})
message(STATUS ${CMAKE_GENERATOR})

file(GLOB MY_TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.txt 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.bmp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.png
)

if(UNIX)
    file(COPY ${MY_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(MSVC)
    file(COPY ${MY_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${MY_TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
endif()
