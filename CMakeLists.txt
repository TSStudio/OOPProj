cmake_minimum_required(VERSION 3.16)
project(sfSnake LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
 
# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     GIT_TAG 2.6.x)
# FetchContent_MakeAvailable(SFML)

# FetchContent_Declare(Freetype
#     GIT_REPOSITORY https://github.com/freetype/freetype.git
#     GIT_TAG VER-2-13-2)
# FetchContent_MakeAvailable(Freetype)

find_package(Freetype REQUIRED)
find_package(SFML COMPONENTS system window graphics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



aux_source_directory(. SRC_LIST)
add_executable(sfSnake ${SRC_LIST})
target_link_libraries(sfSnake PRIVATE sfml-graphics sfml-audio ${FREETYPE_LIBRARIES})
target_include_directories(sfSnake PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_compile_features(sfSnake PRIVATE cxx_std_20)

install(TARGETS sfSnake)