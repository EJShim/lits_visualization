cmake_minimum_required(VERSION 3.3)

PROJECT(Core)

set(SRC_FILES
    E_Volume
)

add_library(${PROJECT_NAME} ${SRC_FILES})