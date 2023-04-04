# standard imports
import unittest

# third party imports

# local imports
import numpy
from codex import CovarianceBlock

class Test_codex_CovarianceBlock( unittest.TestCase ) :
    """Unit test for the CovarianceBlock class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk = CovarianceBlock( nuclide = 'U235', reaction = 'elastic',
                                 energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                 matrix = numpy.array( [ [ 1., 2., 3. ],
                                                         [ 2., 4., 5. ],
                                                         [ 3., 5., 6. ] ] ) )

        # verify content
        self.assertEqual( 'U235', chunk.row.nuclide )
        self.assertEqual( 'elastic', chunk.row.reaction )
        self.assertEqual( 4, len( chunk.row.energies ) )
        self.assertEqual( 3, chunk.row.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row.energies[3] )

        self.assertEqual( 'U235', chunk.column.nuclide )
        self.assertEqual( 'elastic', chunk.column.reaction )
        self.assertEqual( 4, len( chunk.column.energies ) )
        self.assertEqual( 3, chunk.column.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.column.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.column.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.column.energies[3] )

        self.assertEqual( False, chunk.is_off_diagonal )
        self.assertEqual( True, chunk.is_diagonal )

        self.assertAlmostEqual( 1., chunk.matrix[0,0] )
        self.assertAlmostEqual( 2., chunk.matrix[0,1] )
        self.assertAlmostEqual( 3., chunk.matrix[0,2] )
        self.assertAlmostEqual( 2., chunk.matrix[1,0] )
        self.assertAlmostEqual( 4., chunk.matrix[1,1] )
        self.assertAlmostEqual( 5., chunk.matrix[1,2] )
        self.assertAlmostEqual( 3., chunk.matrix[2,0] )
        self.assertAlmostEqual( 5., chunk.matrix[2,1] )
        self.assertAlmostEqual( 6., chunk.matrix[2,2] )

    def test_failures( self ) :

        print( '\n' )


if __name__ == '__main__' :

    unittest.main()
