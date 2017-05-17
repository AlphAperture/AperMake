set(EXECUTABLE_SOURCES src/main.cpp)

add_executable(amake ${EXECUTABLE_SOURCES})
target_link_libraries(amake apermake apercommon)