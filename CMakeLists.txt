cmake_minimum_required(VERSION 3.1)
project(apermake)

set(CMAKE_CXX_STANDARD 14)

set(APERMAKE_VERSION_MAJOR 0)
set(APERMAKE_VERSION_MINOR 0)
set(APERMAKE_VERSION_BUILD 2)

include(GenerateExportHeader)

add_subdirectory(dependencies/apercommon)

include_directories(dependencies/apercommon/include dependencies/cpptoml/include dependencies/optional)

# All files
# There is the C++ headers files.
set(HEADERS_BASE library/include/apermake/apermake.h library/include/apermake/project.h library/include/apermake/lang.h library/include/apermake/dependency.h library/include/apermake/errors.h)
set(HEADERS_FILES ${HEADERS_BASE})
# There is the C++ src files.
set(SOURCES_BASE library/src/apermake.cpp library/src/project.cpp)
set(SOURCES_FILES ${SOURCES_BASE})
add_library(apermake SHARED ${HEADERS_FILES} ${SOURCES_FILES})
# Generate the export header and include it.
GENERATE_EXPORT_HEADER(apermake
        BASE_NAME mapermake
        EXPORT_MACRO_NAME APERMAKE_API
        EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/apermake_exports.h
        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)
configure_file("cmake/apermake_data.cmake.in" "${CMAKE_BINARY_DIR}/exports/apermake_data.h" @ONLY)
target_include_directories(apermake PUBLIC ${CMAKE_BINARY_DIR}/exports)
target_link_libraries(apermake apercommon)

add_subdirectory(executable)