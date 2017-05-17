cmake_minimum_required(VERSION 3.7)
project(tinyrenderer)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES
        "*.cpp"
        "*.h")

add_executable(tinyrenderer ${SOURCE_FILES})

add_custom_command(TARGET tinyrenderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/obj
        $<TARGET_FILE_DIR:tinyrenderer>/obj)