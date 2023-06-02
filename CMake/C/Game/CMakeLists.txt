set(C_GAME_TARGETS_ROOT_DIR "${C_TARGETS_ROOT_DIR}Game/")
set(C_GAME_TARGETS_FOLDER_NAME "C/Game")


# set Tetris
include("Tetris.cmake")


if(TARGET ${TETRIS_TARGET_NAME})
    set_target_properties(
        ${TETRIS_TARGET_NAME}
        PROPERTIES
        FOLDER
        ${C_GAME_TARGETS_FOLDER_NAME}
    )
endif()