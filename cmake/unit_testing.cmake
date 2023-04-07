#######################################################################
# Setup
#######################################################################

message( STATUS "Adding codex unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/codex/matrix/test )
add_subdirectory( src/codex/MetaData/test )
add_subdirectory( src/codex/CovarianceBlock/test )
add_subdirectory( src/codex/CovarianceMatrix/test )

#######################################################################
# python tests
#######################################################################

if( codex.python )

  add_subdirectory( python/test )

endif()
