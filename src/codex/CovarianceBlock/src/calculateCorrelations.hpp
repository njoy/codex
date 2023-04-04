void calculateCorrelations() {

  if ( ! this->correlations_ ) {

    // calculate uncertainties if we have not already
    this->calculateUncertainties();

    // make a temporary diagonal matrix equal to 1 / uncertainty
    DiagonalMatrix< double > temporary( this->row().numberGroups() );
    temporary.setIdentity();
    for ( unsigned int i = 0; i < this->row().numberGroups(); ++i ) {

      temporary.diagonal()[i] /= this->uncertainties()[i];
    }

    // calculate the correlation matrix
    this->correlations_ = temporary * this->covariances() * temporary;
  }
}
