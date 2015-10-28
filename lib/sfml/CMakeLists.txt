cmake_minimum_required(VERSION 3.0.2)

set(EXECUTABLE_NAME sfml)

set(SFML_INCLUDE_DIR /usr/local/include)
set(SFML_ROOT /usr/local/lib/)
set(CMAKE_MODULE_PATH /usr/local/Cellar/sfml/2.3_1/share/SFML/cmake/Modules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++11")

set(SOURCE_FILES srcs/SfmlHandler.cpp)

include_directories(incs)

find_package(SFML 2 REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})

add_library(${EXECUTABLE_NAME} MODULE ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})





