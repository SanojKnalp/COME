# UnitTests/CMakeLists.txt 
set(UNIT_TEST_SOURCES) 
add_subdirectory(FEM)
add_subdirectory(Grid)
add_subdirectory(LinearAlgebra) 
add_subdirectory(LinearSolvers) 
add_executable(UnitTests UnitTestmain.cpp ${UNIT_TEST_SOURCES} ) 
target_link_libraries(UnitTests PRIVATE come_lib ) 
target_compile_definitions(UnitTests PRIVATE CATCH_CONFIG_NO_POSIX_SIGNALS)
target_include_directories(UnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ) 
add_test( NAME UnitTests COMMAND UnitTests )
set_tests_properties(UnitTests PROPERTIES
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)