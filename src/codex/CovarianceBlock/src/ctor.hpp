/**
 *  @brief Constructor for a diagonal covariance block
 *
 *  @param[in] metadata   the metadata associated with the covariance block
 *  @param[in] matrix     the covariance matrix
 */
CovarianceBlock( MetaData metadata, Matrix< double > matrix ) :
  row_( std::move( metadata ) ), column_( std::nullopt ),
  matrix_( std::move( matrix ) ) {

  verifyMatrix( this->matrix(), this->row().energies() );
}

/**
 *  @brief Constructor for a diagonal covariance block
 *
 *  @param[in] nuclide    the nuclide identifier
 *  @param[in] reaction   the reaction identifier
 *  @param[in] energies   the energy boundaries
 *  @param[in] matrix     the covariance matrix
 */
CovarianceBlock( NuclideID nuclide, ReactionID reaction,
                 std::vector< double > energies, Matrix< double > matrix ) :
  CovarianceBlock( MetaData( std::move( nuclide ), std::move( reaction ),
                             std::move( energies ) ),
                   std::move( matrix ) ) {}

/**
 *  @brief Constructor for an off-diagonal covariance block
 *
 *  @param[in] metadata   the metadata associated with the covariance block
 *  @param[in] matrix     the covariance matrix
 */
CovarianceBlock( MetaData row, MetaData column, Matrix< double > matrix ) :
  row_( std::move( row ) ), column_( std::move( column ) ),
  matrix_( std::move( matrix ) ) {

  verifyMatrix( this->matrix(),
                this->row().energies(),
                this->column().energies() );
}

/**
*  @brief Constructor for an off-diagonal covariance block
*
*  @param[in] nuclide    the nuclide identifier
*  @param[in] reaction   the reaction identifier
*  @param[in] energies   the energy boundaries
*  @param[in] matrix     the covariance matrix
*/
CovarianceBlock( NuclideID rowNuclide,
                 ReactionID rowReaction,
                 std::vector< double > rowEnergies,
                 NuclideID columnNuclide,
                 ReactionID columnReaction,
                 std::vector< double > columnEnergies,
                 Matrix< double > matrix ) :
  CovarianceBlock( MetaData( std::move( rowNuclide ),
                             std::move( rowReaction ),
                             std::move( rowEnergies ) ),
                   MetaData( std::move( columnNuclide ),
                             std::move( columnReaction ),
                             std::move( columnEnergies ) ),
                   std::move( matrix ) ) {}
