# standard imports
import unittest

# third party imports

# local imports
import numpy
from codex import CovarianceMatrix

class Test_codex_CovarianceMatrix( unittest.TestCase ) :
    """Unit test for the CovarianceMatrix class."""

    def test_covariance_matrix( self ) :

        # the data is given explicitly
        chunk = CovarianceMatrix(
                    blocks = [ CovarianceMatrix( nuclide = 'U235', reaction = 'elastic',
                                                 energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                                 matrix = numpy.array( [ [ 1., 2., 3. ],
                                                                         [ 2., 4., 6. ],
                                                                         [ 3., 6., 9. ] ] ) ),
                               CovarianceMatrix( nuclide = 'U235', reaction = 'fission',
                                                 energies = [ 1e-5, 2., 2e+7 ],
                                                 matrix = numpy.array( [ [ 16.,  0. ],
                                                                         [  0., 25. ] ] ) ) ] )

        # verify content
        block = chunk.block( 0, 0 )
        self.assertEqual( 'U235', block.row.nuclide )
        self.assertEqual( 'elastic', block.row.reaction )
        self.assertEqual( 'U235', block.column.nuclide )
        self.assertEqual( 'elastic', block.column.reaction )

        block = chunk.block( 1, 1 )
        self.assertEqual( 'U235', block.row.nuclide )
        self.assertEqual( 'fission', block.row.reaction )
        self.assertEqual( 'U235', block.column.nuclide )
        self.assertEqual( 'fission', block.column.reaction )

        metadata = chunk.metadata( 0 )
        self.assertEqual( 'U235', metadata.nuclide )
        self.assertEqual( 'elastic', metadata.reaction )

        metadata = chunk.metadata( 1 )
        self.assertEqual( 'U235', metadata.nuclide )
        self.assertEqual( 'fission', metadata.reaction )

        self.assertEqual( 5, chunk.order )

        self.assertAlmostEqual(  1., chunk.covariances[0,0] )
        self.assertAlmostEqual(  2., chunk.covariances[0,1] )
        self.assertAlmostEqual(  3., chunk.covariances[0,2] )
        self.assertAlmostEqual(  0., chunk.covariances[0,3] )
        self.assertAlmostEqual(  0., chunk.covariances[0,4] )
        self.assertAlmostEqual(  2., chunk.covariances[1,0] )
        self.assertAlmostEqual(  4., chunk.covariances[1,1] )
        self.assertAlmostEqual(  6., chunk.covariances[1,2] )
        self.assertAlmostEqual(  0., chunk.covariances[1,3] )
        self.assertAlmostEqual(  0., chunk.covariances[1,4] )
        self.assertAlmostEqual(  3., chunk.covariances[2,0] )
        self.assertAlmostEqual(  6., chunk.covariances[2,1] )
        self.assertAlmostEqual(  9., chunk.covariances[2,2] )
        self.assertAlmostEqual(  0., chunk.covariances[2,3] )
        self.assertAlmostEqual(  0., chunk.covariances[2,4] )
        self.assertAlmostEqual(  0., chunk.covariances[3,0] )
        self.assertAlmostEqual(  0., chunk.covariances[3,1] )
        self.assertAlmostEqual(  0., chunk.covariances[3,2] )
        self.assertAlmostEqual( 16., chunk.covariances[3,3] )
        self.assertAlmostEqual(  0., chunk.covariances[3,4] )
        self.assertAlmostEqual(  0., chunk.covariances[4,0] )
        self.assertAlmostEqual(  0., chunk.covariances[4,1] )
        self.assertAlmostEqual(  0., chunk.covariances[4,2] )
        self.assertAlmostEqual(  0., chunk.covariances[4,3] )
        self.assertAlmostEqual( 25., chunk.covariances[4,4] )

    def test_failures( self ) :

        print( '\n' )

if __name__ == '__main__' :

    unittest.main()
