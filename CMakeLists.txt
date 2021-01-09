cmake_minimum_required(VERSION 3.0)
project(sfml-widgets)

###################################################################
# Option Setting
option(ENABLE_DEMO "build demo program.(Default:OFF)" OFF)

###################################################################
# import SFML library
find_package(SFML 2.5.1 COMPONENTS system window graphics)
if (SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIRS: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif ()

###################################################################
# Configure general build settings
set(CMAKE_CXX_STANDARD 17)

###################################################################
# Configure build for SFGraphing library
file(GLOB SFML_WIDGETS_SRC src/Gui/*.cpp src/Gui/**/*.cpp)
add_library(sfml-widgets ${SFML_WIDGETS_SRC} )
target_link_libraries(sfml-widgets PUBLIC sfml-graphics sfml-window sfml-system GL)
target_include_directories(sfml-widgets PUBLIC src/)

###################################################################
# Configure build for Sample program
if(ENABLE_DEMO)
file(GLOB DEMO_SRC demo/*.cpp)
add_executable(demo_program ${DEMO_SRC})
target_link_libraries(demo_program sfml-widgets)
endif()
