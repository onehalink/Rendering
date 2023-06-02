set(TETRIS_TARGET_NAME "Tetris")

set(TETRIS_SOURCE_DIR "${C_GAME_TARGETS_ROOT_DIR}${TETRIS_TARGET_NAME}/Source/")


set(
    TETRIS_ALL_SOURCE_FILES

    # UI
    ${TETRIS_SOURCE_DIR}UI/AsciiGlyphInfo.c
    ${TETRIS_SOURCE_DIR}UI/AsciiGlyphInfo.h
    ${TETRIS_SOURCE_DIR}UI/AsciiLibrary.h
    ${TETRIS_SOURCE_DIR}UI/Button.c
    ${TETRIS_SOURCE_DIR}UI/Button.h
    ${TETRIS_SOURCE_DIR}UI/Text.c
    ${TETRIS_SOURCE_DIR}UI/Text.h

    # Template
    ${TETRIS_SOURCE_DIR}Application.c
    ${TETRIS_SOURCE_DIR}Application.h
    ${TETRIS_SOURCE_DIR}EntryPoint.c
    ${TETRIS_SOURCE_DIR}Runtime.h

    # Game related
    ${TETRIS_SOURCE_DIR}BaseDefines.c
    ${TETRIS_SOURCE_DIR}BaseDefines.h
    ${TETRIS_SOURCE_DIR}Framework.c
    ${TETRIS_SOURCE_DIR}Framework.h

    # Other
    ${TETRIS_SOURCE_DIR}../使用手册.txt
    ${TETRIS_SOURCE_DIR}UI/AsciiLibrary.bmp
)

source_group(TREE "${TETRIS_SOURCE_DIR}../" FILES ${TETRIS_ALL_SOURCE_FILES})


# has some dependencies on Windows OS
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(
        ${TETRIS_TARGET_NAME}
        ${TETRIS_ALL_SOURCE_FILES}
    )

    target_link_libraries(
        ${TETRIS_TARGET_NAME}
        PRIVATE
        ${ENGINE_TARGET_NAME}
    )

    target_include_directories(
        ${TETRIS_TARGET_NAME}
        PRIVATE
        ${ENGINE_INCLUDE_DIR}
    )
endif()