/**
 *  @brief Calculate the uncertainties from the covariances
 *
 *  The uncertainties can only be calculated from covariance blocks on the
 *  diagonal of the covariance matrix. When this function is called on an
 *  off diagonal block, the function has no effect.
 */
void calculateUncertainties() {

  if ( this->isDiagonalBlock() ) {

    std::vector< double > uncertainties;
    uncertainties.reserve( this->rowMetadata().numberGroups() );

    for ( const auto& value : this->covariances().value().diagonal().reshaped() ) {

      uncertainties.emplace_back( std::sqrt( value ) );
    }

    this->uncertainties_ = uncertainties;
  }
}
