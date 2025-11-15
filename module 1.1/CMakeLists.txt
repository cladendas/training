cmake_minimum_required(VERSION 3.20)
project(TEST)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(${PROJECT_NAME} ThreadSafeQueue.cpp)
# add_executable(${PROJECT_NAME} Accumulate.cpp)
add_executable(${PROJECT_NAME} ObjectPool.cpp)
add_executable(${PROJECT_NAME} is_container.cpp)