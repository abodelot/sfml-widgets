
# images and fonts
file(GLOB_RECURSE my_images "${CMAKE_SOURCE_DIR}/demo/resources/*")
foreach(FILE ${my_images})
  file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/" ${FILE})
  get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
  set_source_files_properties(${FILE} PROPERTIES MACOSX_PACKAGE_LOCATION
                                                 "Resources/${NEW_FILE_PATH}")
endforeach()

add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE
               ${DEMO_SRC} "${my_images}")

set_target_properties(
  ${CMAKE_PROJECT_NAME}
  PROPERTIES BUNDLE TRUE
             XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
             XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
             XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/../Frameworks"
             MACOSX_BUNDLE_BUNDLE_NAME "${CMAKE_PROJECT_NAME}"
             MACOSX_BUNDLE_GUI_IDENTIFIER "com.alexandre.bodelot.${CMAKE_PROJECT_NAME}"
             MACOSX_BUNDLE_COPYRIGHT "(c) 2023, Alexandre Bodelot"
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
             RESOURCE "${my_images}")
