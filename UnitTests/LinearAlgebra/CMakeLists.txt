# Register LinearAlgebra test sources

list(APPEND UNIT_TEST_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/LinAlg_dense_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinAlg_sparse_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinAlg_vector_test.cpp
)

# Export list to parent scope
set(UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES} PARENT_SCOPE)
