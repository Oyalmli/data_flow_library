add_executable(
  dvfw_test
  main.cpp
  pipe/chunks.cpp
  pipe/moving_avg.cpp
  pipe/take.cpp
  pipe/drop.cpp
  pipe/scanl.cpp
  sink/hole.cpp
  pipe/drop_while.cpp
  pipe/filter.cpp
  pipe/set_state.cpp
  pipe/tee.cpp
  pipe/fork.cpp
  pipe/transform.cpp
  gen/range.cpp
  gen/value.cpp
  gen/file.cpp
  gen/take.cpp
  gen/impl_generator.cpp)
add_test(NAME dvfw_test COMMAND dvfw_test)

target_include_directories(
  dvfw_test PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

target_compile_features(dvfw_test PRIVATE cxx_std_17)

target_compile_options(
  dvfw_test
  PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
          $<$<CXX_COMPILER_ID:MSVC>:/W4>
          $<$<CXX_COMPILER_ID:MSVC>:/WX>
          $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall>
          $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-deprecated-copy>
          $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Werror>
          $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pedantic>)
