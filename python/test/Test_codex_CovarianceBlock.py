# standard imports
import unittest

# third party imports

# local imports
import numpy
from codex import CovarianceBlock

class Test_codex_CovarianceBlock( unittest.TestCase ) :
    """Unit test for the CovarianceBlock class."""

    def test_diagonal_covariance_block( self ) :

        # the data is given explicitly - for a diagonal block
        chunk = CovarianceBlock( nuclide = 'U235', reaction = 'elastic',
                                 energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                 matrix = numpy.array( [ [ 1., 2., 3. ],
                                                         [ 2., 4., 6. ],
                                                         [ 3., 6., 9. ] ] ) )

        # verify content
        self.assertEqual( 'U235', chunk.row_metadata.nuclide )
        self.assertEqual( 'elastic', chunk.row_metadata.reaction )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( 'U235', chunk.column_metadata.nuclide )
        self.assertEqual( 'elastic', chunk.column_metadata.reaction )
        self.assertEqual( 4, len( chunk.column_metadata.energies ) )
        self.assertEqual( 3, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.column_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[3] )

        self.assertEqual( False, chunk.is_off_diagonal_block )
        self.assertEqual( True, chunk.is_diagonal_block )

        self.assertEqual( None, chunk.uncertainties )
        self.assertEqual( None, chunk.correlations )
        self.assertEqual( None, chunk.eigenvalues )

        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 3., chunk.covariances[0,2] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 4., chunk.covariances[1,1] )
        self.assertAlmostEqual( 6., chunk.covariances[1,2] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 6., chunk.covariances[2,1] )
        self.assertAlmostEqual( 9., chunk.covariances[2,2] )

        chunk.calculate_uncertainties()
        self.assertAlmostEqual( 1., chunk.uncertainties[0] )
        self.assertAlmostEqual( 2., chunk.uncertainties[1] )
        self.assertAlmostEqual( 3., chunk.uncertainties[2] )

        chunk.calculate_correlations()
        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[0,2] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,2] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,2] )

        chunk.calculate_eigenvalues()
        self.assertAlmostEqual( 0., chunk.eigenvalues[0] )
        self.assertAlmostEqual( 0., chunk.eigenvalues[1] )
        self.assertAlmostEqual( 14., chunk.eigenvalues[2] )

    def test_off_diagonal_covariance_block( self ) :

        # the data is given explicitly
        chunk = CovarianceBlock( row_nuclide = 'U235', row_reaction = 'elastic',
                                 row_energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                 column_nuclide = 'U238', column_reaction = 'fission',
                                 column_energies = [ 1e-5, 2., 2e+7 ],
                                 matrix = numpy.array( [ [ 1., 2. ],
                                                         [ 2., 4. ],
                                                         [ 3., 6. ] ] ) )

        # verify content
        self.assertEqual( 'U235', chunk.row_metadata.nuclide )
        self.assertEqual( 'elastic', chunk.row_metadata.reaction )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( 'U238', chunk.column_metadata.nuclide )
        self.assertEqual( 'fission', chunk.column_metadata.reaction )
        self.assertEqual( 3, len( chunk.column_metadata.energies ) )
        self.assertEqual( 2, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 2.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[2] )

        self.assertEqual( True, chunk.is_off_diagonal_block )
        self.assertEqual( False, chunk.is_diagonal_block )

        self.assertEqual( None, chunk.uncertainties )
        self.assertEqual( None, chunk.correlations )
        self.assertEqual( None, chunk.eigenvalues )

        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 4., chunk.covariances[1,1] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 6., chunk.covariances[2,1] )

        chunk.calculate_uncertainties()
        self.assertEqual( None, chunk.uncertainties )

        chunk.calculate_correlations( [ 1., 2., 3. ], [ 1., 2. ] )
        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )

        chunk.calculate_eigenvalues()
        self.assertEqual( None, chunk.eigenvalues )

    def test_failures( self ) :

        print( '\n' )

if __name__ == '__main__' :

    unittest.main()
