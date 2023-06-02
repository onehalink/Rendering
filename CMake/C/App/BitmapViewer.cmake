set(BITMAP_VIEWER_TARGET_NAME "BitmapViewer")

set(BITMAP_VIEWER_SOURCE_DIR "${C_APP_TARGETS_ROOT_DIR}${BITMAP_VIEWER_TARGET_NAME}/Source/")


set(
    BITMAP_VIEWER_ALL_SOURCE_FILES
    ${BITMAP_VIEWER_SOURCE_DIR}Application.c
    ${BITMAP_VIEWER_SOURCE_DIR}Application.h
    ${BITMAP_VIEWER_SOURCE_DIR}EntryPoint.c
    ${BITMAP_VIEWER_SOURCE_DIR}Runtime.h
)

source_group(TREE "${BITMAP_VIEWER_SOURCE_DIR}../" FILES ${BITMAP_VIEWER_ALL_SOURCE_FILES})


# has some dependencies on Windows OS
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(
        ${BITMAP_VIEWER_TARGET_NAME}
        ${BITMAP_VIEWER_ALL_SOURCE_FILES}
    )

    target_link_libraries(
        ${BITMAP_VIEWER_TARGET_NAME}
        PRIVATE
        ${ENGINE_TARGET_NAME}
    )

    target_include_directories(
        ${BITMAP_VIEWER_TARGET_NAME}
        PRIVATE
        ${ENGINE_INCLUDE_DIR}
    )
endif()