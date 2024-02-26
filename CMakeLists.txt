cmake_minimum_required(VERSION 3.18)
project(sfml-widgets VERSION 1.1.0)

# ##############################################################################
# Option Setting
option(ENABLE_DEMO "build demo program.(Default:ON)" ON)

# ##############################################################################
# IMPORTANT HINT: Tell CMake where you installed SFML libs & headers

# set(SFML_HOME "C:/SFML/SFML-2.6.1") ## (<---WINDOWS)
# set(SFML_HOME "/Library/Frameworks/SFML.framework/") ## (<---MACOS)
# set(SFML_DIR ${SFML_HOME}/lib/cmake/SFML)
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

# show warnings (depending on C++ compiler)
if(MSVC)
  target_compile_options(sfml-widgets PUBLIC /W4)
else()
  target_compile_options(sfml-widgets PUBLIC -Wall -Wextra)
endif()

# ##############################################################################
# Configure build for Sample program
if(ENABLE_DEMO)
  file(GLOB DEMO_SRC demo/*.cpp)
  add_executable(demo_program ${DEMO_SRC})
 
  if(WIN32)
  add_executable(demo_program WIN32 ${DEMO_SRC})
  target_link_libraries(demo_program PRIVATE sfml-widgets sfml-main OpenGL::GL sfml-graphics sfml-window sfml-system)
 
  elseif(APPLE)
  include(${CMAKE_SOURCE_DIR}/apple_cmake/MacBundle.cmake)
  find_library(FOUNDATION_FRAMEWORK Foundation)
  target_link_libraries(demo_program PRIVATE sfml-widgets OpenGL::GL sfml-graphics sfml-window sfml-system
                         ${FOUNDATION_FRAMEWORK})
  else()
  add_executable(demo_program ${SOURCES}) 
  target_link_libraries(demo_program PRIVATE sfml-widgets OpenGL::GL sfml-graphics sfml-window sfml-system)
  endif()

  #include SFML headers
  include_directories(${SFML_HOME}/include)

  # show warnings (depending on C++ compiler)
  if(MSVC)
    target_compile_options(demo_program PUBLIC /W4)
  else()
    target_compile_options(demo_program PUBLIC -Wall -Wextra)
  endif()

  
  # COPY resources folder to destination (Windows & Linux)
  if(NOT APPLE)
   add_custom_command(
   TARGET demo_program POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/demo/resources $<TARGET_FILE_DIR:demo_program>/resources
)
endif()
