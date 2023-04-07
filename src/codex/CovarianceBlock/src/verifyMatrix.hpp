static void verifyMatrix( const Matrix< double >& matrix,
                          const std::vector< double >& energies ) {

  // check if the matrix is square
  if ( ! isSquare( matrix ) ) {

    Log::error( "The matrix for a diagonal covariance block must be square" );
    throw std::exception();
  }

  // check if the matrix is symmetric
  if ( ! isSymmetric( matrix ) ) {

    Log::error( "The matrix for a diagonal covariance block must be symmetric" );
    throw std::exception();
  }

  // check if the matrix order is consistent with the energy boundaries
  if ( matrix.rows() != energies.size() - 1 ) {

    Log::error( "The matrix order and the energy boundaries are not consistent" );
    Log::info( "Number rows: {}", matrix.rows() );
    Log::info( "Number columns: {}", matrix.cols() );
    Log::info( "Number of energy groups: {}", energies.size() - 1 );
    throw std::exception();
  }
}

void verifyMatrix( const Matrix< double >& matrix,
                   const std::vector< double >& rowEnergies,
                   const std::vector< double >& columnEnergies ) {

  // check if the matrix row order is consistent with the energy boundaries
  if ( matrix.rows() != rowEnergies.size() - 1 ) {

    Log::error( "The matrix order and the energy boundaries are not consistent" );
    Log::info( "Number rows: {}", matrix.rows() );
    Log::info( "Number columns: {}", matrix.cols() );
    Log::info( "Number of row energy groups: {}", rowEnergies.size() - 1 );
    Log::info( "Number of column energy groups: {}", columnEnergies.size() - 1 );
    throw std::exception();
  }

  // check if the matrix column order is consistent with the energy boundaries
  if ( matrix.cols() != columnEnergies.size() - 1 ) {

    Log::error( "The matrix order and the energy boundaries are not consistent" );
    Log::info( "Number rows: {}", matrix.rows() );
    Log::info( "Number columns: {}", matrix.cols() );
    Log::info( "Number of row energy groups: {}", rowEnergies.size() - 1 );
    Log::info( "Number of column energy groups: {}", columnEnergies.size() - 1 );
    throw std::exception();
  }
}
