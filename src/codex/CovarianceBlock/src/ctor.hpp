/**
 *  @brief Constructor for a diagonal covariance block
 *
 *  @param[in] metadata   the metadata associated with the covariance block
 *  @param[in] matrix     the covariance matrix
 */
CovarianceBlock( MetaData metadata, Matrix< double > matrix ) :
  row_( std::move( metadata ) ), column_( std::nullopt ),
  matrix_( std::move( matrix ) ) {

  verifyMatrix( this->matrix(), this->rowMetadata().energies() );
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
 *  @param[in] rowMetadata       the row metadata
 *  @param[in] columnMetadata    the column metadata
 *  @param[in] matrix            the covariance matrix
 */
CovarianceBlock( MetaData rowMetadata, MetaData columnMetadata,
                 Matrix< double > matrix ) :
  row_( std::move( rowMetadata ) ), column_( std::move( columnMetadata ) ),
  matrix_( std::move( matrix ) ) {

  verifyMatrix( this->matrix(),
                this->rowMetadata().energies(),
                this->columnMetadata().energies() );
}

/**
 *  @brief Constructor for an off-diagonal covariance block
 *
 *  @param[in] rowNuclide       the row nuclide identifier
 *  @param[in] rowReaction      the row reaction identifier
 *  @param[in] rowEnergies      the row energy boundaries
 *  @param[in] columnNuclide    the row nuclide identifier
 *  @param[in] columnReaction   the row reaction identifier
 *  @param[in] columnEnergies   the row energy boundaries
 *  @param[in] matrix           the covariance matrix
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
