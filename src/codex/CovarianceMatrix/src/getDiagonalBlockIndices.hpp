static std::vector< std::size_t >
getDiagonalBlockIndices( const std::vector< CovarianceBlock >& blocks ) {

  std::vector< std::size_t > indices;
  for ( std::size_t i = 0; i < blocks.size(); ++i ) {

    if ( blocks[i].isDiagonal() ) {

      indices.push_back( i );
    }
  }

  return indices;
}
