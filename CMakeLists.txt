cmake_minimum_required(VERSION 3.18)
project(sfml-widgets VERSION 1.1.0)

# ##############################################################################
# Option Setting
option(ENABLE_DEMO "build demo program.(Default:ON)" ON)
set(DEMO_EXE "demo_widgets")

# ##############################################################################
# IMPORTANT HINT: Tell CMake where you installed SFML libs & headers (root folder)
###############################################################################
# set(SFML_HOME "C:/SFML/SFML-2.6.1")                  ## (<---WINDOWS) 
# set(SFML_HOME "/Library/Frameworks/SFML.framework/") ## (<---MACOS) set(SFML_DIR
# ${SFML_HOME}/lib/cmake/SFML) s

set(ENABLE_DEMO TRUE)

# FIND SFML libs
find_package(SFML 2.6 REQUIRED COMPONENTS "graphics" "window" "system")
find_package(OpenGL REQUIRED)

# ##############################################################################
# Configure general build settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
endif()

# ##############################################################################
# Configure build for SFGraphing library
file(GLOB_RECURSE SFML_WIDGETS_SRC src/Gui/*.cpp src/Gui/**/*.cpp)
add_library(sfml-widgets ${SFML_WIDGETS_SRC})
target_link_libraries(sfml-widgets PUBLIC sfml-graphics sfml-window sfml-system)
target_include_directories(sfml-widgets PUBLIC ${CMAKE_SOURCE_DIR}/src/)

# ##############################################################################
# Configure build for Sample program
if(ENABLE_DEMO)
  file(GLOB DEMO_SRC demo/*.cpp demo/*.mm)

  if(WIN32)
    add_executable(${DEMO_EXE} WIN32 ${DEMO_SRC})
    target_link_libraries(
      ${DEMO_EXE} PRIVATE sfml-widgets sfml-main OpenGL::GL sfml-graphics
                          sfml-window sfml-system)

  elseif(APPLE)
    include(${CMAKE_SOURCE_DIR}/apple_cmake/MacBundle.cmake)
    find_library(FOUNDATION_FRAMEWORK Foundation)
    target_link_libraries(
      ${DEMO_EXE} PRIVATE sfml-widgets OpenGL::GL sfml-graphics sfml-window
                          sfml-system ${FOUNDATION_FRAMEWORK})
  else()
    add_executable(${DEMO_EXE} ${DEMO_SRC})
    target_link_libraries(
      ${DEMO_EXE} PRIVATE sfml-widgets OpenGL::GL sfml-graphics sfml-window
                          sfml-system)
  endif(WIN32)

  # COPY resources folder to destination (Windows & Linux)
  if(NOT APPLE)
    add_custom_command(
      TARGET ${DEMO_EXE}
      POST_BUILD
      COMMAND
        ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/demo/resources
        $<TARGET_FILE_DIR:${DEMO_EXE}>/resources)
  endif()
endif(ENABLE_DEMO)
############################ END OF DEMO PROGRAM ###############################

# include SFML headers
include_directories(${SFML_HOME}/include)

# show warnings (depending on C++ compiler)
if(MSVC)
  target_compile_options(${DEMO_EXE} PUBLIC /W4)
else()
  target_compile_options(${DEMO_EXE} PUBLIC -Wall -Wextra)
endif()
