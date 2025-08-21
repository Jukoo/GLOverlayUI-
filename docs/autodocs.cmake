# @file autodocs.cmake 
# @brief This cmake file is used to automate the documentation 
#+       using doxygen the generated doxyfile w'll be used by
#+       sphinx combined with breathe extension to handle C/C++ 
#+       docstring
# @author  Umar Ba <jUmarB@protonmail.com> 

#-- looking for Doxygen  -- 

find_package(Doxygen  REQUIRED) 
if(NOT DOXYGEN_FOUND)
  message(SEND_ERROR "Documentation build  Error")
endif() 

#-- Prevent to wipe out the pre-configured DOXYFILE   
#-- If the Doxyfile already exists you should remove it manualy 

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
  #+ Generate a new doxyfile 
  execute_process(
    COMMAND ${DOXYGEN_EXECUTABLE}  "-g"   
    WORKING_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/docs 
    RESULT_VARIABLE    DOXYOUT_RESULT 
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  
  if(NOT DOXYOUT_RESULT   EQUAL "0") 
    message(WARNING "Error while generating the docs from  code-source")
  endif()

else() 
   message(STATUS  "Doxyfile already generated ! ")
endif() 

#-- Execute Doxygen to  process the Doxyfile and generate the 
#-+ appropriate directory  
message(STATUS "Processing Doxyfile")
execute_process(
  COMMAND  ${DOXYGEN_EXECUTABLE}
  WORKING_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/docs
  RESULT_VARIABLE  HTML_BUILD_RESULT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT HTML_BUILD_RESULT EQUAL  "0")
  message(FATAL_ERROR "Fail to Process Doxyfile")
endif() 

#-- Generate the Html Doc  

message(STATUS "Build doc using Sphinx configuration X Breathe Extension")
if(NOT EXISTS  ${CMAKE_CURRENT_SOURCE_DIR}/docs/index.rst) 
  message(FATAL_ERROR "Not able to generate the html file")
endif() 

execute_process(
  COMMAND  make html
  WORKING_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/docs
  RESULT_VARIABLE  HTML_BUILD_RESULT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT HTML_BUILD_RESULT EQUAL "0") 
  message(SEND_ERROR  "Fail to build html documentation ressources")
  message(INFO  ":|\tCheck if you're under  py virtual env")
  message(WARNING  "\tDo not forget to install the depencies via requirements.txt file")
else() 
  message(NOTICE "\tHINT:: You can  visualize the generated doc through your web browser by executing a http server")
  message(NOTICE "\tHINT:: python3  -m http.server  -d  <path_to_html_folder>")
endif() 

