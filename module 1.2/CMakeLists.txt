cmake_minimum_required(VERSION 3.20)
project(Module_1.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra 
    -Wpedantic
)

# Отладочные флаги только для Debug
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-g -O0>)

# Релизные флаги только для Release  
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:-O3>)

add_library(utils_lib STATIC src/utils.cpp)
target_include_directories(utils_lib PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE utils_lib)

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(TARGETS utils_lib DESTINATION lib)
install(FILES include/utils.h DESTINATION include)

set(CPACK_PACKAGE_NAME "Module_1_2")
set(CPACK_PACKAGE_VERSION "1.0.0")

include(CPack)