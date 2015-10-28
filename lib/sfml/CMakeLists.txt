cmake_minimum_required(VERSION 3.0.2)

set(EXECUTABLE_NAME sfml)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++11")
set(SOURCE_FILES srcs/SfmlHandler.cpp)

set(CMAKE_MODULE_PATH /usr/local/Cellar/sfml/2.2/share/SFML/cmake/Modules)

find_package(SFML 2 REQUIRED system window graphics audio)

include_directories(incs)
add_library(${EXECUTABLE_NAME} MODULE ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
