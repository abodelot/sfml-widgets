# icon
set(MACOSX_BUNDLE_ICON_FILE "SfmlWidgets.icns")
set(application_icon "${CMAKE_SOURCE_DIR}/demo/resources/${MACOSX_BUNDLE_ICON_FILE}")
set_source_files_properties(${application_icon}
                            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# images and fonts
file(GLOB_RECURSE my_images "${CMAKE_SOURCE_DIR}/demo/resources/*")
foreach(FILE ${my_images})
  file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/" ${FILE})
  get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
  set_source_files_properties(${FILE} PROPERTIES MACOSX_PACKAGE_LOCATION
                                                 "Resources/${NEW_FILE_PATH}")
endforeach()

add_executable(${DEMO_EXE} MACOSX_BUNDLE
               ${DEMO_SRC} "${my_images}")

set_target_properties(
  ${DEMO_EXE}
  PROPERTIES BUNDLE TRUE
             XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
             XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
             XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/../Frameworks"
             MACOSX_BUNDLE_BUNDLE_NAME "${DEMO_EXE}"
             MACOSX_BUNDLE_GUI_IDENTIFIER "com.alexandre.bodelot.${DEMO_EXE}"
             MACOSX_BUNDLE_COPYRIGHT "(c) 2021, Alexandre Bodelot"
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
             RESOURCE "${my_images}")
