cmake_minimum_required (VERSION 2.8)
project (IOBReader)
set (IOBReader_VERSION_MAJOR 1)
set (IOBReader_VERSION_MINOR 0)

set (IOBReader_SOURCES
 AnsiFile.cpp IobReader.cpp main.cpp)

set (IOBReader_HEADERS
 AnsiFile.h IobReader.h IobTags.h)

add_executable(IOBReader ${IOBReader_SOURCES})

target_link_libraries(IOBReader)

