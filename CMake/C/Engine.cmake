set(ENGINE_TARGET_NAME "Engine")

set(ENGINE_SOURCE_DIR "${C_TARGETS_ROOT_DIR}${ENGINE_TARGET_NAME}/Source/")
set(ENGINE_INCLUDE_DIR "${C_TARGETS_ROOT_DIR}${ENGINE_TARGET_NAME}/Source/Include/")
set(ENGINE_RUNTIME_DIR "${C_TARGETS_ROOT_DIR}${ENGINE_TARGET_NAME}/Source/Runtime/")


### Engine All Source Files
# Begin

# Header Files
set(
    ENGINE_INCLUDE_HEADER_FILES

    ${ENGINE_INCLUDE_DIR}Engine.h
)

set(
    ENGINE_ASSET_HEADER_FILES

    ${ENGINE_RUNTIME_DIR}Asset/Asset.h
    ${ENGINE_RUNTIME_DIR}Asset/Bitmap.h
    ${ENGINE_RUNTIME_DIR}Asset/Wave.h
)

set(
    ENGINE_CORE_HEADER_FILES

    # Base
    ${ENGINE_RUNTIME_DIR}Core/Base/Enum.h
    ${ENGINE_RUNTIME_DIR}Core/Base/Micro.h
    ${ENGINE_RUNTIME_DIR}Core/Base/Type.h
    # Container
    ${ENGINE_RUNTIME_DIR}Core/Container/DynamicArray.h
    ${ENGINE_RUNTIME_DIR}Core/Container/LinkedList.h
    ${ENGINE_RUNTIME_DIR}Core/Container/LinkedListNode.h
    # Mathematics
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Color.h
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Math.h
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix3.h
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector2.h
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector3.h
    # String
    ${ENGINE_RUNTIME_DIR}Core/String/AsciiString.h
    ${ENGINE_RUNTIME_DIR}Core/String/AsciiStringHelper.h
    ${ENGINE_RUNTIME_DIR}Core/String/StringForward.h
    ${ENGINE_RUNTIME_DIR}Core/String/U8String.h
    ${ENGINE_RUNTIME_DIR}Core/String/U16String.h
    ${ENGINE_RUNTIME_DIR}Core/String/U32String.h
    ${ENGINE_RUNTIME_DIR}Core/String/Unicode.h
    # System
    ${ENGINE_RUNTIME_DIR}Core/System/Allocator.h
    ${ENGINE_RUNTIME_DIR}Core/System/HeapMemory.h
    ${ENGINE_RUNTIME_DIR}Core/System/Memory.h
    ${ENGINE_RUNTIME_DIR}Core/System/Timer.h

    # Header files as module's container
    ${ENGINE_RUNTIME_DIR}Core/Base.h
)

set(
    ENGINE_PLATFORM_HEADER_FILES

    # RHI
    ${ENGINE_RUNTIME_DIR}Platform/RHI/Serface.h
    # SAL
    ${ENGINE_RUNTIME_DIR}Platform/SAL/Directory.h
    ${ENGINE_RUNTIME_DIR}Platform/SAL/EventSystem.h
    ${ENGINE_RUNTIME_DIR}Platform/SAL/File.h
    ${ENGINE_RUNTIME_DIR}Platform/SAL/Path.h
    # OS special(Windows, Linux and so on..)
    #

    # Other
    ${ENGINE_RUNTIME_DIR}Platform/RHI/RHI.description
    ${ENGINE_RUNTIME_DIR}Platform/SAL/SAL.description
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(
        APPEND 
        ENGINE_PLATFORM_HEADER_FILES

        ${ENGINE_RUNTIME_DIR}Platform/Windows/DirectSound.h
        ${ENGINE_RUNTIME_DIR}Platform/Windows/FileDialog.h
        ${ENGINE_RUNTIME_DIR}Platform/Windows/GraphicDeviceInterface.h
        ${ENGINE_RUNTIME_DIR}Platform/Windows/Window.h
        ${ENGINE_RUNTIME_DIR}Platform/Windows/Windows.h
   )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # do something here
endif()

# Source Files
set(
    ENGINE_ASSET_SOURCE_FILES

    ${ENGINE_RUNTIME_DIR}Asset/Asset.c
    ${ENGINE_RUNTIME_DIR}Asset/Bitmap.c
    ${ENGINE_RUNTIME_DIR}Asset/Wave.c
)

set(
    ENGINE_CORE_SOURCE_FILES

    # Base
    # Not existed
    # Container
    ${ENGINE_RUNTIME_DIR}Core/Container/DynamicArray.c
    ${ENGINE_RUNTIME_DIR}Core/Container/LinkedList.c
    ${ENGINE_RUNTIME_DIR}Core/Container/LinkedListNode.c
    # Mathematics
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Color.c
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Math.c
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Matrix3.c
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector2.c
    ${ENGINE_RUNTIME_DIR}Core/Mathematics/Vector3.c
    # String
    ${ENGINE_RUNTIME_DIR}Core/String/AsciiString.c
    ${ENGINE_RUNTIME_DIR}Core/String/AsciiStringHelper.c
    ${ENGINE_RUNTIME_DIR}Core/String/U8String.c
    ${ENGINE_RUNTIME_DIR}Core/String/U16String.c
    ${ENGINE_RUNTIME_DIR}Core/String/U32String.c
    ${ENGINE_RUNTIME_DIR}Core/String/Unicode.c
    # System
    ${ENGINE_RUNTIME_DIR}Core/System/Allocator.c
    ${ENGINE_RUNTIME_DIR}Core/System/HeapMemory.c
    ${ENGINE_RUNTIME_DIR}Core/System/Memory.c
    ${ENGINE_RUNTIME_DIR}Core/System/Timer.c
)

set(
    ENGINE_PLATFORM_SOURCE_FILES

    # RHI
    ${ENGINE_RUNTIME_DIR}Platform/RHI/Serface.c
    # SAL
    ${ENGINE_RUNTIME_DIR}Platform/SAL/Directory.c
    ${ENGINE_RUNTIME_DIR}Platform/SAL/EventSystem.c
    ${ENGINE_RUNTIME_DIR}Platform/SAL/File.c
    ${ENGINE_RUNTIME_DIR}Platform/SAL/Path.c
    # OS special(Windows, Linux and so on..)
    #
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(
        APPEND 
        ENGINE_PLATFORM_SOURCE_FILES

        ${ENGINE_RUNTIME_DIR}Platform/Windows/DirectSound.c
        ${ENGINE_RUNTIME_DIR}Platform/Windows/FileDialog.c
        ${ENGINE_RUNTIME_DIR}Platform/Windows/GraphicDeviceInterface.c
        ${ENGINE_RUNTIME_DIR}Platform/Windows/Window.c
   )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # do something here
endif()

# End


set(
    ENGINE_ALL_SOURCE_FILES

    ${ENGINE_INCLUDE_HEADER_FILES}

    # Asset
    ${ENGINE_ASSET_HEADER_FILES}
    ${ENGINE_ASSET_SOURCE_FILES}
    # Core
    ${ENGINE_CORE_HEADER_FILES}
    ${ENGINE_CORE_SOURCE_FILES}
    # Platform
    ${ENGINE_PLATFORM_HEADER_FILES}
    ${ENGINE_PLATFORM_SOURCE_FILES}

    # Header files as module's container
    ${ENGINE_RUNTIME_DIR}Core.h
)

source_group(TREE "${ENGINE_SOURCE_DIR}../" FILES ${ENGINE_ALL_SOURCE_FILES})

# End
### Engine All Source Files


add_library(
    ${ENGINE_TARGET_NAME}
    SHARED
    ${ENGINE_ALL_SOURCE_FILES}
)