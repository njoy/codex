add_test( NAME codex.python.matrix COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/Test_codex_matrix.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
add_test( NAME codex.python.MetaData COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/Test_codex_MetaData.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
add_test( NAME codex.python.CovarianceBlock COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/Test_codex_CovarianceBlock.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
