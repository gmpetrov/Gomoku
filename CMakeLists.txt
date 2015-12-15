cmake_minimum_required(VERSION 3.0.2)

project(Gomoku)

set(dev-warnings "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -std=c++11")
set(warnings "${CMAKE_CXX_FLAGS} -O3 -std=c++11")
set(CMAKE_CXX_FLAGS "${dev-warnings}")
set(EXECUTABLE_NAME Gomoku)
set(SOURCE_FILES
    srcs/main.cpp
    srcs/Board.cpp
    srcs/GraphSwitch.cpp
    srcs/Human.cpp
    srcs/AI.cpp
    srcs/State.cpp
    srcs/RulesChecker.cpp
    )

include_directories(includes)

add_subdirectory(lib/sfml)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
