static Matrix< double >
constructCovarianceMatrix( const std::vector< CovarianceBlock >& blocks,
                           const std::vector< std::size_t >& diagonal ) {

  // determine the size of the final matrix
  std::size_t order = 0;
  for ( std::size_t index : diagonal ) {

    order += blocks[index].rowMetadata().numberGroups();
  }

  // initialise the matrix
  Matrix< double > covariances( order, order );
  covariances.setZero();

  // go over the diagonal blocks and assign the matrices
  std::size_t position = 0;
  for ( std::size_t index : diagonal ) {

    std::size_t size = blocks[index].rowMetadata().numberGroups();
    covariances.block( position, position, size, size ) = blocks[index].covariances().value();
    position += size;
  }

  // return the matrix
  return covariances;
}
