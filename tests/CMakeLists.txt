add_executable(dvfw_test
    main.cpp
    chunks.cpp
    take.cpp
    drop.cpp
    scanl.cpp
    hole.cpp
    drop_while.cpp
    filter.cpp
    set_state.cpp
    tee.cpp
    fork.cpp
    transform.cpp
    generators/file.cpp
    generators/impl_generator.cpp
)
add_test(NAME dvfw_test COMMAND dvfw_test)

target_include_directories(dvfw_test PRIVATE
                       $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                       $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

target_compile_features(dvfw_test PRIVATE cxx_std_17)

target_compile_options(dvfw_test
                   PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
                   $<$<CXX_COMPILER_ID:MSVC>:/W4>
                   $<$<CXX_COMPILER_ID:MSVC>:/WX>
                   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall>
                   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra>
                   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Werror>
                   $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pedantic>)