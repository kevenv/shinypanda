cmake_minimum_required(VERSION 2.8)

project(shinypanda)

file(GLOB shinypanda_SRC
	"${PROJECT_SOURCE_DIR}/../../include/*.h"
	"${PROJECT_SOURCE_DIR}/../../src/*.cpp"
)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
include_directories(${PROJECT_SOURCE_DIR}/../../src)

add_executable(shinypanda ${shinypanda_SRC})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)

set(CMAKE_CXX_FLAGS "-std=gnu++11 -Wall")

target_link_libraries(shinypanda sfml-graphics)
target_link_libraries(shinypanda sfml-window)
target_link_libraries(shinypanda sfml-system)
target_link_libraries(shinypanda sfml-audio)

install(TARGETS shinypanda RUNTIME DESTINATION bin)