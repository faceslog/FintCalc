cmake_minimum_required(VERSION 3.10)

project(FintCalc)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

if (WIN32)
    set(WHERE-IS-SDL "C:/programs/sdl/lib/x64")
    set(WHERE-IS-SDL-HEADERS "C:/programs/sdl/include")
    set(WHERE-IS-GLAD "glad/src/glad.c")
    set(WHERE-IS-GLAD-HEADERS "glad/include")
endif()

if (UNIX)
    set(WHERE-IS-GLAD "glad/src/glad.c")
    set(WHERE-IS-GLAD-HEADERS "glad/include")

    if (APPLE)
        set(WHERE-IS-SDL "${CMAKE_SOURCE_DIR}/lib")
        set(WHERE-IS-SDL-HEADERS "${CMAKE_SOURCE_DIR}/lib/SDL2.framework/Versions/Current/Headers")
    endif()

    if(NOT APPLE)
        find_package(SDL2 REQUIRED)
        include_directories(${SDL2_INCLUDE_DIRS})
    endif()
endif()

if (WIN32 OR APPLE)
    find_library(SDL SDL2 PATHS ${WHERE-IS-SDL})
    if (WIN32)
        find_library(SDLmain SDL2main PATHS ${WHERE-IS-SDL})
    endif()
    
    include_directories(
            "${WHERE-IS-SDL-HEADERS}"
    )
endif()

add_library("glad" ${WHERE-IS-GLAD})
include_directories(
        "${WHERE-IS-GLAD-HEADERS}"
)

# your sources
set(sources
        src/main.cpp
        src/fint.cpp
        src/controller.cpp
        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_opengl3.h
        imgui/imgui_impl_sdl.cpp
        imgui/imgui_impl_sdl.h
        )

if (WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${sources})
    target_link_libraries(${CMAKE_PROJECT_NAME}
            "glad"
            ${SDL}
            ${SDLmain}
            ${OPENGL_gl_LIBRARY}
            )
else()
    add_executable(${CMAKE_PROJECT_NAME} ${sources})
    target_link_libraries(${CMAKE_PROJECT_NAME}
            "glad"
            ${OPENGL_gl_LIBRARY}
            )
    if (APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
                ${SDL}
                )
    endif()
    if (UNIX AND NOT APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
                ${SDL2_LIBRARIES}
                ${CMAKE_DL_LIBS}
                )
    endif()
endif()

