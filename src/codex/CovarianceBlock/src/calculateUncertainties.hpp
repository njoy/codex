void calculateUncertainties() {

  if ( ! this->uncertainties_ ) {

    std::vector< double > uncertainties;
    uncertainties.reserve( this->row().numberGroups() );

    for ( const auto& value : this->covariances().diagonal().reshaped() ) {

      uncertainties.emplace_back( std::sqrt( value ) );
    }

    this->uncertainties_ = uncertainties;
  }
}
