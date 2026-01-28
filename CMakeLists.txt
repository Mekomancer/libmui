cmake_minimum_required(VERSION 4.2) # nice
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_COMPILER_IMPORT_STD 26)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY target)
set(CMAKE_CXX_MODULE_STD 1)

project(mui
  VERSION 0.1.0 # SemVer
  DESCRIPTION "μ"
  LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
     "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_library(mui
  src/ioctl.cxx
  src/cmdline.cxx
  src/fb.cxx
  src/display.cxx
  src/font.cxx
  src/file.cxx
)

target_sources(mui
  PUBLIC
  FILE_SET CXX_MODULES
  BASE_DIRS src
  FILES
  src/display.ixx
  src/types.ixx
  src/mui.ixx
  src/cmdline.ixx
  src/fb.ixx
  src/ioctl.ixx
  src/error.ixx
  src/font.ixx
  src/io.ixx
  src/file.ixx	
  src/graphics.ixx
)

add_executable(test
  src/test.cpp
)

add_custom_target(format 
  COMMAND clang-format -i
  "$<PATH:ABSOLUTE_PATH,$<TARGET_PROPERTY:test,SOURCES>
  ,${CMAKE_SOURCE_DIR}>"
  "$<PATH:ABSOLUTE_PATH,$<TARGET_PROPERTY:mui,SOURCES>
  ,${CMAKE_SOURCE_DIR}>"
  "$<PATH:ABSOLUTE_PATH,$<TARGET_PROPERTY:mui,CXX_MODULE_SET>
  ,${CMAKE_SOURCE_DIR}>"
  COMMAND_EXPAND_LISTS
  VERBATIM
)

target_compile_definitions(mui 
  PRIVATE 
  VERSION=\"${PROJECT_VERSION}\"
  NAME=\"mui\"
)

target_compile_features(mui PUBLIC cxx_std_26)

target_link_libraries(mui)
target_link_libraries(test mui)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(module_interface_dir  ${CMAKE_INSTALL_INCLUDEDIR}/mui/)
configure_package_config_file(
  ${CMAKE_SOURCE_DIR}/cmake/muiConfig.cmake.in
  ${CMAKE_BINARY_DIR}/muiConfig.cmake
  PATH_VARS module_interface_dir
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mui
)
install(TARGETS mui 
  EXPORT muiModules
  CXX_MODULES_BMI  
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET CXX_MODULES
    DESTINATION ${module_interface_dir}
)
install(FILES
  ${CMAKE_BINARY_DIR}/muiConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mui
)
install(EXPORT muiModules 
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mui 
    CXX_MODULES_DIRECTORY .
)

