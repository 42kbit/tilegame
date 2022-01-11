cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME glad)
project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
