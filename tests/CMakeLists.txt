add_executable(
  dfl_test

  main.cpp
  test_example.cpp

  gen/adjacent.cpp
  gen/counter.cpp
  gen/file.cpp
  gen/impl_generator.cpp
  gen/mux.cpp
  gen/range.cpp
  gen/sine.cpp
  gen/value.cpp

  mod/noise.cpp
  mod/repeat.cpp
  mod/take.cpp

  pipe/chunks.cpp
  pipe/moving_avg.cpp
  pipe/take.cpp
  pipe/drop.cpp
  pipe/scanl.cpp
  pipe/drop_while.cpp
  pipe/filter.cpp
  pipe/set_state.cpp
  pipe/tee.cpp
  pipe/transform.cpp
  pipe/intersperse.cpp
  pipe/side_effect.cpp
  pipe/stride.cpp
  pipe/tap.cpp
  pipe/transform_s.cpp

  rdir/fork.cpp
  rdir/partition.cpp

  sink/hole.cpp
  sink/histogram.cpp
  sink/for_each.cpp
  sink/max.cpp
  sink/min.cpp
  sink/print.cpp
  sink/printf.cpp
  sink/push_back.cpp
  sink/sum.cpp
  sink/to_out_stream.cpp
  )
add_test(NAME dfl_test COMMAND dfl_test)

target_include_directories(
  dfl_test PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                   $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

target_compile_features(dfl_test PRIVATE cxx_std_17)

target_compile_options(
  dfl_test
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-deprecated-copy>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Werror>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pedantic>)
