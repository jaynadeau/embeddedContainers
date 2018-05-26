cmake_minimum_required(VERSION 3.5)

project(embeddedContainers)

set(SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)
set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})