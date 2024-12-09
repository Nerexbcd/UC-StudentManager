cmake_minimum_required(VERSION 3.5.0)
project(UC-StudentManager VERSION 0.1.0 LANGUAGES C)

add_executable(UC-StudentManager main.c)


file(GLOB LIB_SOURCES "libs/**/*.c" "libs/**/*.h")
include(CTest)

target_sources(UC-StudentManager PRIVATE ${LIB_SOURCES})


enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
