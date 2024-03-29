cmake_minimum_required(VERSION 3.12)

project(
  dfl
  VERSION 0.0.1
  DESCRIPTION "High level data validation framework for standalone IoT devices"
  HOMEPAGE_URL "https://github.com/Oyalmli/data_validation_framework")

include(GNUInstallDirs)

add_library(${PROJECT_NAME} INTERFACE)
add_library(oyalmli::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}_Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(
  EXPORT ${PROJECT_NAME}_Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
        DESTINATION include)

include(CTest)

if(BUILD_TESTING)
  add_subdirectory(tests)
  # Create example executabel using the framework
  find_package(benchmark REQUIRED)

  # MAIN
  add_executable(main benchmark/main.cpp)
  target_link_libraries(main PRIVATE dfl)
  target_link_libraries(main PRIVATE benchmark::benchmark)
  target_compile_features(main PRIVATE cxx_std_17)
  target_compile_options(main PRIVATE -fverbose-asm -save-temps -O2)

  # BENCHMARK
  add_executable(bench benchmark/benchmark.cpp)
  target_link_libraries(bench PRIVATE dfl)
  target_link_libraries(bench PRIVATE benchmark::benchmark)
  target_compile_features(bench PRIVATE cxx_std_17)
  target_compile_options(bench PRIVATE -O2)
endif()
