cmake_minimum_required(VERSION 3.13)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

find_package(PkgConfig REQUIRED)

project(brisque_image_quality_assessment VERSION 0.1.0 DESCRIPTION "Brisque Image Quality Assessment Library")

find_package( OpenCV REQUIRED )
pkg_search_module(cppunit OPTIONAL cppunit)

add_library(brisque_iqa SHARED
  ${CMAKE_SOURCE_DIR}/brisque.cpp
  ${CMAKE_SOURCE_DIR}/computescore.cpp
  brisque.h
  )

set_target_properties(brisque_iqa PROPERTIES    
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER brisque.h
  )

if(cppunit_FOUND)

  if (EXISTS /usr/local/include/fr/cppunit OR EXISTS /usr/include/fr/cppunit)
    set(USE_FR_CPPUNIT TRUE)
  else()
    SET(USE_FR_CPPUNIT FALSE)
  endif()

  
  add_executable(test_computescore
    ${CMAKE_SOURCE_DIR}/test/test_runner_basic.cpp
    ${CMAKE_SOURCE_DIR}/test/test_computescore.cpp
    )

  target_compile_definitions(test_computescore PRIVATE
    TEST_MODEL="${CMAKE_SOURCE_DIR}/allmodel"
    TEST_IMAGE="${CMAKE_SOURCE_DIR}/test/original-scaled-image.jpg")

  if (USE_FR_CPPUNIT)
    target_compile_definitions(test_computescore PRIVATE HAVE_FR_LISTENER)
  endif()

  
  target_include_directories(test_computescore PRIVATE ${CMAKE_SOURCE_DIR})
  target_link_directories(test_computescore PRIVATE ${CMAKE_BIN_DIR})
  target_link_libraries(test_computescore PRIVATE ${OpenCV_LIBRARIES} ${cppunit_LIBRARIES} brisque_iqa)

  enable_testing()
  add_test(NAME test_computescore COMMAND test_computescore)

endif()
    
install(TARGETS brisque_iqa
  LIBRARY
  DESTINATION lib
  PUBLIC_HEADER
  DESTINATION include/brisque
  )
install(FILES allmodel
  DESTINATION share/brisque
  )

# SET(CMAKE_CXX_FLAGS -fpermissive)


target_link_libraries( brisque_iqa  ${OpenCV_LIBRARIES} svm)


