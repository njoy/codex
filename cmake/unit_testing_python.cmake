#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set( test_name "codex.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        PYTHONPATH=${CODEX_PYTHONPATH}:$ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding codex Python unit testing" )

add_python_test( matrix                     Test_codex_matrix.py )
add_python_test( MetaData                   Test_codex_MetaData.py )
add_python_test( CovarianceBlock            Test_codex_CovarianceBlock.py )

add_python_test( format.endf.SquareMatrix   format/endf/Test_codex_format_endf_SquareMatrix.py )
