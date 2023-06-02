set(C_APP_TARGETS_ROOT_DIR "${C_TARGETS_ROOT_DIR}App/")
set(C_APP_TARGETS_FOLDER_NAME "C/App")


# set BitmapViewer
include("BitmapViewer.cmake")

# set StreammingAudioPlayer
include("StreammingAudioPlayer.cmake")


if(TARGET ${BITMAP_VIEWER_TARGET_NAME})
    set_target_properties(
        ${BITMAP_VIEWER_TARGET_NAME}
        PROPERTIES
        FOLDER
        ${C_APP_TARGETS_FOLDER_NAME}
    )
endif()

if(TARGET ${STREAMMING_AUDIO_PLAYER_TARGET_NAME})
    set_target_properties(
        ${STREAMMING_AUDIO_PLAYER_TARGET_NAME}
        PROPERTIES
        FOLDER
        ${C_APP_TARGETS_FOLDER_NAME}
    )
endif()