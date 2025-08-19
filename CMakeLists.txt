#############################################################################
# File :       CMakeLists.txt
# Brief:       Cmake for GLOverlayUI 
# Author:      Umar Ba <jUmarB@protonmail.com> 
# Licence:     None
#############################################################################

cmake_minimum_required(VERSION 3.11...3.30 FATAL_ERROR)
project("GLOverlayUI" VERSION "0.1.0" DESCRIPTION "Interactive Gui App")


#NOTE:w'll not build if your cmake version  is (under) < 3.11 
if(NOT ${CMAKE_VERSION}  GREATER "3.11")
  message(FATAL_ERROR "Require Cmake version >=3.11")
else() 
  include(FetchContent) 
endif()

set(CMAKE_CXX_STANDARD  17) 
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)  

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/GLOverlayUI_config.in 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/GLOverlayUI_config.in.H)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib) 

file(GLOB_RECURSE  src  ${CMAKE_CURRENT_SOURCE_DIR}/src/*) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) 


#--NOTE:Change it to Release  in prodution mode 
set(CMAKE_BUILD_TYPE  Release)
#-- Autobuild the documentation on Release  
if(CMAKE_BUILD_TYPE STREQUAL "Release") 
  message(STATUS "Generating Autodoc")
  include(docs/autodocs.cmake) 
endif()


#-- Looking for git  command -- 
message(CHECK_START "Looking for Git command") 
find_package(Git  REQUIRED) 

if(NOT GIT_FOUND)  
  message(CHECK_FAIL  "Require Git to create submodule path") 
endif()  

if(NOT EXISTS  ${PROJECT_SOURCE_DIR}/.git)
  message(CHECK_FAIL "The current path is not a valid .git repo")
endif()

#-- WxWidget --  
message(STATUS "WxWidget configuration") 

set(wxwigets_base_source_url "https://github.com/wxWidgets/wxWidgets.git") 
set(wxwidgets_base_version_tag "v3.3.1")

if(NOT EXISTS   ${FETCHCONTENT_BASE_DIR}/wxwidgets-src/CMakeLists.txt) 
  message(WARNING "WxWiget source not found ${FETCHCONTENT_BASE_DIR} ")
  message(STATUS "Download  WxWidget  from Git repository") 
  message(INFO   "\turl :${wxwigets_base_source_url}\n\tTag ${wxwidgets_base_version_tag}") 
  
  FetchContent_Declare(
    wxWidgets 
    GIT_REPOSITORY  ${wxwigets_base_source_url} 
    GIT_TAG         ${wxwidgets_base_version_tag} 
  )
  FetchContent_MakeAvailable(wxWidgets) 
endif() 

add_definitions(-DwxUSE_GLCANVAS=1)

#-- WxWidget -- ! 

#-- OpenGL --
message(CHECK_START   "looking requirements")
message(STATUS  "OpenGL  configuration") 
find_package(OpenGL REQUIRED) 

if(NOT  OPENGL_FOUND) 
  message(FATAL_ERROR "Build receip Require OpenGL library  to proceed") 
else() 
  message(CHECK_PASS  "OpenGL library found")
  include_directories(${OPENGL_INCLUDE_DIRS})
endif()

 
add_subdirectory(${FETCHCONTENT_BASE_DIR}/wxwidgets-src)  

add_executable(${PROJECT_NAME}  ${PROJECT_NAME}_app.C  ${src} )
target_link_libraries(${PROJECT_NAME} wx::net wx::core wx::base wx::gl ${OPENGL_LIBRARIES})
