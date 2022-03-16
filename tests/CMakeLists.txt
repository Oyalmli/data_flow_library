add_executable(dvfw_test
    main.cpp
    take.cpp
    drop.cpp
    hole.cpp
    set_state.cpp
    transform.cpp
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