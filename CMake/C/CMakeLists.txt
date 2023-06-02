cmake_minimum_required(VERSION 3.20.0)


# Binary output directory(*.exe, *.lib, *.dll and *.exp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Binary/C")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Binary/C")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Binary/C")


project("Rendering" LANGUAGES C)


set(CMAKE_C_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set(RENDERING_ROOT_DIR "${CMAKE_SOURCE_DIR}/../../")

set(C_TARGETS_ROOT_DIR "${RENDERING_ROOT_DIR}C/")
set(C_TARGETS_FOLDER_NAME "C")


# set Engine
include("Engine.cmake")

# set Template
include("Template.cmake")


add_subdirectory("./App")
add_subdirectory("./Game")


set_target_properties(
    ${ENGINE_TARGET_NAME}
    PROPERTIES
    FOLDER
    ${C_TARGETS_FOLDER_NAME}
)

if(TARGET ${TEMPLATE_TARGET_NAME})
    set_target_properties(
        ${TEMPLATE_TARGET_NAME}
        PROPERTIES
        FOLDER
        ${C_TARGETS_FOLDER_NAME}
    )
endif()