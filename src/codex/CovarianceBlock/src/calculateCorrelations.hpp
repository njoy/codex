/**
 *  @brief Calculate the correlations (for covariance blocks on the diagonal)
 *
 *  The correlations can only be calculated without input of the uncertainties
 *  for covariance blocks on the diagonal of the covariance matrix. When this
 *  method is called on an off diagonal block, the method has no effect.
 *  Uncertainties will be calculated and stored as well.
 */
void calculateCorrelations() {

  if ( this->isDiagonal() ) {

    this->calculateUncertainties();

    DiagonalMatrix< double > temporary( this->row().numberGroups() );
    temporary.setIdentity();
    for ( unsigned int i = 0; i < this->row().numberGroups(); ++i ) {

      temporary.diagonal()[i] /= this->uncertainties().value()[i];
    }

    this->correlations_ = temporary * this->covariances().value() * temporary;
  }
}

/**
 *  @brief Calculate the uncertainties (for off diagonal covariance blocks)
 *
 *  The correlations can only be calculated with input of the uncertainties
 *  for covariance blocks that are off diagonal in the covariance matrix.
 *  Uncertainties will not be stored.
 *
 *  @param[in] row      the uncertainties to be applied to each row
 *  @param[in] column   the uncertainties to be applied to each column
 */
void calculateCorrelations( const std::vector< double >& row,
                            const std::vector< double >& column ) {

  DiagonalMatrix< double > left( this->row().numberGroups() );
  left.setIdentity();
  for ( unsigned int i = 0; i < this->row().numberGroups(); ++i ) {

    left.diagonal()[i] /= row[i];
  }

  DiagonalMatrix< double > right( this->column().numberGroups() );
  right.setIdentity();
  for ( unsigned int i = 0; i < this->column().numberGroups(); ++i ) {

    right.diagonal()[i] /= column[i];
  }

  this->correlations_ = left * this->covariances().value() * right;
}
