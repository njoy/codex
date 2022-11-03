/**
 *  @brief Constructor
 *
 *  @param[in] nuclide    the nuclide identifier
 *  @param[in] reaction   the reaction identifier
 *  @param[in] energies   the energy boundaries
 */
MetaData( NuclideID nuclide, ReactionID reaction,
          std::vector< double > energies ) :
  nuclide_( std::move( nuclide ) ), reaction_( std::move( reaction ) ),
  energies_( std::move( energies ) ) {

  verifyEnergies( this->energies() );
}