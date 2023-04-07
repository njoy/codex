private:

/**
 *  @brief Private intermediate constructor
 */
CovarianceMatrix( std::vector< CovarianceBlock >&& blocks,
                  std::vector< std::size_t >&& diagonal,
                  Matrix< double >&& covariances ) :
  blocks_( std::move( blocks ) ), diagonal_( std::move( diagonal ) ),
  covariances_( std::move( covariances ) ) {}

/**
 *  @brief Private intermediate constructor
 */
CovarianceMatrix( std::vector< CovarianceBlock >&& blocks,
                  std::vector< std::size_t >&& diagonal ) :
  CovarianceMatrix( std::move( blocks ), std::move( diagonal ),
                    constructCovarianceMatrix( blocks, diagonal ) ) {}

public:

/**
 *  @brief Constructor for a covariance matrix consisting of covariance blocks
 *
 *  @param[in] blocks   the covariance blocks making up the matrix
 */
CovarianceMatrix( std::vector< CovarianceBlock > blocks ) :
  CovarianceMatrix( std::move( blocks ), getDiagonalBlockIndices( blocks ) ) {}
