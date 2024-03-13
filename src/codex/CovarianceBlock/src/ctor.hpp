/**
 *  @brief Constructor for a diagonal covariance block
 *
 *  @param[in] metadata      the metadata associated with the covariance block
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceBlock( MetaData metadata, Matrix< double > covariances, bool relative = true ) :
  row_( std::move( metadata ) ), column_( std::nullopt ), relative_( relative ),
  covariances_( std::move( covariances ) ), sigmas_( std::nullopt ),
  correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(), this->rowMetadata().energies() );
}

/**
 *  @brief Constructor for a diagonal covariance block
 *
 *  @param[in] nuclide       the nuclide identifier
 *  @param[in] reaction      the reaction identifier
 *  @param[in] energies      the energy boundaries
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceBlock( NuclideID nuclide, ReactionID reaction,
                 std::vector< double > energies, Matrix< double > covariances,
                 bool relative = true ) :
  CovarianceBlock( MetaData( std::move( nuclide ), std::move( reaction ),
                             std::move( energies ) ),
                   std::move( covariances ), relative ) {}

/**
 *  @brief Constructor for an off-diagonal covariance block
 *
 *  @param[in] rowMetadata       the row metadata
 *  @param[in] columnMetadata    the column metadata
 *  @param[in] covariances       the covariance matrix
 *  @param[in] relative          the relative covariance flag
 */
CovarianceBlock( MetaData rowMetadata, MetaData columnMetadata,
                 Matrix< double > covariances, bool relative = true ) :
  row_( std::move( rowMetadata ) ), column_( std::move( columnMetadata ) ),
  relative_( relative ), covariances_( std::move( covariances ) ),
  sigmas_( std::nullopt ), correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(),
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
 *  @param[in] covariances      the covariance matrix
 *  @param[in] relative         the relative covariance flag
 */
CovarianceBlock( NuclideID rowNuclide,
                 ReactionID rowReaction,
                 std::vector< double > rowEnergies,
                 NuclideID columnNuclide,
                 ReactionID columnReaction,
                 std::vector< double > columnEnergies,
                 Matrix< double > covariances,
                 bool relative = true ) :
  CovarianceBlock( MetaData( std::move( rowNuclide ),
                             std::move( rowReaction ),
                             std::move( rowEnergies ) ),
                   MetaData( std::move( columnNuclide ),
                             std::move( columnReaction ),
                             std::move( columnEnergies ) ),
                   std::move( covariances ),
                   relative ) {}
