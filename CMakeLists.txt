cmake_minimum_required(VERSION 3.12)
project(Chaos)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for built targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define SDL2 paths
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendors/SDL2")
set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
set(SDL2_LIBRARY_DIR "${SDL2_DIR}/lib/x64")
set(SDL2_LIBRARIES "${SDL2_LIBRARY_DIR}/SDL2.lib;${SDL2_LIBRARY_DIR}/SDL2main.lib")

# Define SDL2 Image paths
set(SDL2_IMG_DIR "${CMAKE_SOURCE_DIR}/vendors/SDL2_image")
set(SDL2_IMG_INCLUDE_DIRS "${SDL2_IMG_DIR}/include")
set(SDL2_IMG_LIBRARY_DIR "${SDL2_IMG_DIR}/lib/x64")
set(SDL2_IMG_LIBRARIES "${SDL2_IMG_LIBRARY_DIR}/SDL2_image.lib")

# Define SDL2 TTF paths
set(SDL2_TTF_DIR "${CMAKE_SOURCE_DIR}/vendors/SDL2_ttf")
set(SDL2_TTF_INCLUDE_DIRS "${SDL2_TTF_DIR}/include")
set(SDL2_TTF_LIBRARY_DIR "${SDL2_TTF_DIR}/lib/x64")
set(SDL2_TTF_LIBRARIES "${SDL2_TTF_LIBRARY_DIR}/SDL2_ttf.lib")

# Define ImGui paths
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/vendors/imgui")
set(IMGUI_INCLUDE_DIRS "${IMGUI_DIR}" "${IMGUI_DIR}/backends")

# Helper function to add a library or executable
function(add_project_target TARGET_NAME SOURCE_DIR TYPE)
    # Find all source files including those in subdirectories
    file(GLOB_RECURSE SOURCE_FILES
        "${SOURCE_DIR}/*.cpp"
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.hpp"
    )
    
    if(${TYPE} STREQUAL "EXECUTABLE")
        add_executable(${TARGET_NAME} ${SOURCE_FILES})
    else()
        add_library(${TARGET_NAME} ${SOURCE_FILES})
    endif()
    
    # Create source groups (filters in Visual Studio)
    foreach(SOURCE_FILE IN ITEMS ${SOURCE_FILES})
        get_filename_component(SOURCE_PATH "${SOURCE_FILE}" PATH)
        file(RELATIVE_PATH SOURCE_PATH_REL "${SOURCE_DIR}" "${SOURCE_PATH}")
        string(REPLACE "/" "\\" SOURCE_PATH_MSVC "${SOURCE_PATH_REL}")
        source_group("${SOURCE_PATH_MSVC}" FILES "${SOURCE_FILE}")
    endforeach()
    
    # Include all directories
    target_include_directories(${TARGET_NAME} PRIVATE
        ${SOURCE_DIR}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMG_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${IMGUI_INCLUDE_DIRS}
    )
    
    if(${TYPE} STREQUAL "EXECUTABLE")
        target_link_libraries(${TARGET_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES} helpers_lib)
    else()
        target_link_libraries(${TARGET_NAME} PRIVATE ${SDL2_LIBRARY_DIR}/SDL2.lib ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES})
    endif()
endfunction()

# Add the helpers library
add_project_target(helpers_lib ${CMAKE_SOURCE_DIR}/helpers "LIBRARY")

# Add the main project
add_project_target(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/project "EXECUTABLE")

# Link the helpers library to the main project
target_link_libraries(${PROJECT_NAME} PRIVATE helpers_lib)

# Add the test project
add_project_target(tests ${CMAKE_SOURCE_DIR}/test "EXECUTABLE")

# Link the helpers library to the test project
target_link_libraries(tests PRIVATE helpers_lib)

# Set the startup project to the main project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Add ImGui source files directly to the main project
target_sources(${PROJECT_NAME} PRIVATE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)