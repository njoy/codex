# standard imports
import unittest

# third party imports

# local imports
from codex import MetaData

class Test_codex_MetaData( unittest.TestCase ) :
    """Unit test for the MetaData class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 'U235', chunk.nuclide )
            self.assertEqual( 'elastic', chunk.reaction )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 3, chunk.number_groups )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 1.  , chunk.energies[1] )
            self.assertAlmostEqual( 1e+6, chunk.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.energies[3] )

        # the data is given explicitly
        chunk = MetaData( nuclide = 'U235', reaction = 'elastic',
                          energies = [ 1e-5, 1., 1e+6, 2e+7 ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the energy grid does not have at least 2 elements
        with self.assertRaises( Exception ) :

            chunk = MetaData( nuclide = 'U235', reaction = 'elastic',
                              energies = [ 1e-5 ] )

        # the energy grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = MetaData( nuclide = 'U235', reaction = 'elastic',
                              energies = [ 2e+7, 1e+6, 1., 1e-5 ] )

        # the energy grid has duplicate points
        with self.assertRaises( Exception ) :

            chunk = MetaData( nuclide = 'U235', reaction = 'elastic',
                              energies = [ 1e-5, 1., 1., 2e+7 ] )

if __name__ == '__main__' :

    unittest.main()
