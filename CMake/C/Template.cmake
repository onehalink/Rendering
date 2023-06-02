set(TEMPLATE_TARGET_NAME "Template")

set(TEMPLATE_SOURCE_DIR "${C_TARGETS_ROOT_DIR}${TEMPLATE_TARGET_NAME}/Source/")


set(
    TEMPLATE_ALL_SOURCE_FILES
    ${TEMPLATE_SOURCE_DIR}Application.c
    ${TEMPLATE_SOURCE_DIR}Application.h
    ${TEMPLATE_SOURCE_DIR}EntryPoint.c
    ${TEMPLATE_SOURCE_DIR}Runtime.h
)

source_group(TREE "${TEMPLATE_SOURCE_DIR}../" FILES ${TEMPLATE_ALL_SOURCE_FILES})


# has some dependencies on Windows OS
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(
        ${TEMPLATE_TARGET_NAME}
        ${TEMPLATE_ALL_SOURCE_FILES}
    )

    target_link_libraries(
        ${TEMPLATE_TARGET_NAME}
        PRIVATE
        ${ENGINE_TARGET_NAME}
    )

    target_include_directories(
        ${TEMPLATE_TARGET_NAME}
        PRIVATE
        ${ENGINE_INCLUDE_DIR}
    )
endif()
