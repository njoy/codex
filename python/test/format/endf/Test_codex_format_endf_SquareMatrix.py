# standard imports
import unittest

# third party imports

# local imports
import numpy
from codex.format import from_endf
from ENDFtk import SquareMatrix

class Test_codex_format_from_endf( unittest.TestCase ) :
    """Unit test for the from_endf function."""

    endf_string = (
        " 0.000000+0 0.000000+0          1          5         66         11223133 16     \n"
        " 1.000000-5 1.187260+7 1.200000+7 1.300000+7 1.400000+7 1.500000+7223133 16     \n"
        " 1.600000+7 1.700000+7 1.800000+7 1.900000+7 2.000000+7 0.000000+0223133 16     \n"
        " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0223133 16     \n"
        " 0.000000+0 0.000000+0 0.000000+0 2.500000-1 0.000000+0 0.000000+0223133 16     \n"
        " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0223133 16     \n"
        " 3.897788-3 3.151794-3 2.605989-3 2.173942-3 1.843332-3 1.579267-3223133 16     \n"
        " 1.391836-3 1.269227-3 2.822801-3 2.436598-3 2.140176-3 1.913301-3223133 16     \n"
        " 1.731503-3 1.615025-3 1.549830-3 2.244027-3 2.112649-3 2.011479-3223133 16     \n"
        " 1.927034-3 1.882109-3 1.864828-3 2.123149-3 2.130883-3 2.131577-3223133 16     \n"
        " 2.150402-3 2.176944-3 2.223439-3 2.291726-3 2.362609-3 2.426673-3223133 16     \n"
        " 2.415636-3 2.531881-3 2.632081-3 2.689968-3 2.830254-3 3.018361-3223133 16     \n" )

    endf = SquareMatrix.from_string( endf_string, 2231, 33, 16 )

    def test_diagonal_covariance_block( self ) :

        # the data is read from
        chunk = from_endf( "Ti48", "n,2n", self.endf )

        # verify content
        self.assertEqual( 'Ti48', chunk.row_metadata.nuclide )
        self.assertEqual( 'n,2n', chunk.row_metadata.reaction )
        self.assertEqual( 11, len( chunk.row_metadata.energies ) )
        self.assertEqual( 10, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.000000e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.187260e+7, chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1.200000e+7, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 1.300000e+7, chunk.row_metadata.energies[3] )
        self.assertAlmostEqual( 1.400000e+7, chunk.row_metadata.energies[4] )
        self.assertAlmostEqual( 1.500000e+7, chunk.row_metadata.energies[5] )
        self.assertAlmostEqual( 1.600000e+7, chunk.row_metadata.energies[6] )
        self.assertAlmostEqual( 1.700000e+7, chunk.row_metadata.energies[7] )
        self.assertAlmostEqual( 1.800000e+7, chunk.row_metadata.energies[8] )
        self.assertAlmostEqual( 1.900000e+7, chunk.row_metadata.energies[9] )
        self.assertAlmostEqual( 2.000000e+7, chunk.row_metadata.energies[10] )

        self.assertEqual( 'Ti48', chunk.column_metadata.nuclide )
        self.assertEqual( 'n,2n', chunk.column_metadata.reaction )
        self.assertEqual( 11, len( chunk.column_metadata.energies ) )
        self.assertEqual( 10, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 1.000000e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 1.187260e+7, chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 1.200000e+7, chunk.column_metadata.energies[2] )
        self.assertAlmostEqual( 1.300000e+7, chunk.column_metadata.energies[3] )
        self.assertAlmostEqual( 1.400000e+7, chunk.column_metadata.energies[4] )
        self.assertAlmostEqual( 1.500000e+7, chunk.column_metadata.energies[5] )
        self.assertAlmostEqual( 1.600000e+7, chunk.column_metadata.energies[6] )
        self.assertAlmostEqual( 1.700000e+7, chunk.column_metadata.energies[7] )
        self.assertAlmostEqual( 1.800000e+7, chunk.column_metadata.energies[8] )
        self.assertAlmostEqual( 1.900000e+7, chunk.column_metadata.energies[9] )
        self.assertAlmostEqual( 2.000000e+7, chunk.column_metadata.energies[10] )

        self.assertEqual( True, chunk.is_relative_block )
        self.assertEqual( False, chunk.is_off_diagonal_block )
        self.assertEqual( True, chunk.is_diagonal_block )

        self.assertEqual( None, chunk.standard_deviations )
        self.assertEqual( None, chunk.correlations )
        self.assertEqual( None, chunk.eigenvalues )

        self.assertAlmostEqual( 0., chunk.covariances[0,0] )
        self.assertAlmostEqual( 0., chunk.covariances[0,1] )
        self.assertAlmostEqual( 0., chunk.covariances[0,2] )
        self.assertAlmostEqual( 0., chunk.covariances[0,3] )
        self.assertAlmostEqual( 0., chunk.covariances[0,4] )
        self.assertAlmostEqual( 0., chunk.covariances[0,5] )
        self.assertAlmostEqual( 0., chunk.covariances[0,6] )
        self.assertAlmostEqual( 0., chunk.covariances[0,7] )
        self.assertAlmostEqual( 0., chunk.covariances[0,8] )
        self.assertAlmostEqual( 0., chunk.covariances[0,9] )

        self.assertAlmostEqual( 0., chunk.covariances[1,0] )
        self.assertAlmostEqual( 0.25, chunk.covariances[1,1] )
        self.assertAlmostEqual( 0., chunk.covariances[1,2] )
        self.assertAlmostEqual( 0., chunk.covariances[1,3] )
        self.assertAlmostEqual( 0., chunk.covariances[1,4] )
        self.assertAlmostEqual( 0., chunk.covariances[1,5] )
        self.assertAlmostEqual( 0., chunk.covariances[1,6] )
        self.assertAlmostEqual( 0., chunk.covariances[1,7] )
        self.assertAlmostEqual( 0., chunk.covariances[1,8] )
        self.assertAlmostEqual( 0., chunk.covariances[1,9] )

        self.assertAlmostEqual( 0., chunk.covariances[2,0] )
        self.assertAlmostEqual( 0., chunk.covariances[2,1] )
        self.assertAlmostEqual( 3.897788e-3, chunk.covariances[2,2] )
        self.assertAlmostEqual( 3.151794e-3, chunk.covariances[2,3] )
        self.assertAlmostEqual( 2.605989e-3, chunk.covariances[2,4] )
        self.assertAlmostEqual( 2.173942e-3, chunk.covariances[2,5] )
        self.assertAlmostEqual( 1.843332e-3, chunk.covariances[2,6] )
        self.assertAlmostEqual( 1.579267e-3, chunk.covariances[2,7] )
        self.assertAlmostEqual( 1.391836e-3, chunk.covariances[2,8] )
        self.assertAlmostEqual( 1.269227e-3, chunk.covariances[2,9] )

        self.assertAlmostEqual( 0., chunk.covariances[3,0] )
        self.assertAlmostEqual( 0., chunk.covariances[3,1] )
        self.assertAlmostEqual( 3.151794e-3, chunk.covariances[3,2] )
        self.assertAlmostEqual( 2.822801e-3, chunk.covariances[3,3] )
        self.assertAlmostEqual( 2.436598e-3, chunk.covariances[3,4] )
        self.assertAlmostEqual( 2.140176e-3, chunk.covariances[3,5] )
        self.assertAlmostEqual( 1.913301e-3, chunk.covariances[3,6] )
        self.assertAlmostEqual( 1.731503e-3, chunk.covariances[3,7] )
        self.assertAlmostEqual( 1.615025e-3, chunk.covariances[3,8] )
        self.assertAlmostEqual( 1.549830e-3, chunk.covariances[3,9] )

        self.assertAlmostEqual( 0., chunk.covariances[4,0] )
        self.assertAlmostEqual( 0., chunk.covariances[4,1] )
        self.assertAlmostEqual( 2.605989e-3, chunk.covariances[4,2] )
        self.assertAlmostEqual( 2.436598e-3, chunk.covariances[4,3] )
        self.assertAlmostEqual( 2.244027e-3, chunk.covariances[4,4] )
        self.assertAlmostEqual( 2.112649e-3, chunk.covariances[4,5] )
        self.assertAlmostEqual( 2.011479e-3, chunk.covariances[4,6] )
        self.assertAlmostEqual( 1.927034e-3, chunk.covariances[4,7] )
        self.assertAlmostEqual( 1.882109e-3, chunk.covariances[4,8] )
        self.assertAlmostEqual( 1.864828e-3, chunk.covariances[4,9] )

        self.assertAlmostEqual( 0., chunk.covariances[5,0] )
        self.assertAlmostEqual( 0., chunk.covariances[5,1] )
        self.assertAlmostEqual( 2.173942e-3, chunk.covariances[5,2] )
        self.assertAlmostEqual( 2.140176e-3, chunk.covariances[5,3] )
        self.assertAlmostEqual( 2.112649e-3, chunk.covariances[5,4] )
        self.assertAlmostEqual( 2.123149e-3, chunk.covariances[5,5] )
        self.assertAlmostEqual( 2.130883e-3, chunk.covariances[5,6] )
        self.assertAlmostEqual( 2.131577e-3, chunk.covariances[5,7] )
        self.assertAlmostEqual( 2.150402e-3, chunk.covariances[5,8] )
        self.assertAlmostEqual( 2.176944e-3, chunk.covariances[5,9] )

        self.assertAlmostEqual( 0., chunk.covariances[6,0] )
        self.assertAlmostEqual( 0., chunk.covariances[6,1] )
        self.assertAlmostEqual( 1.843332e-3, chunk.covariances[6,2] )
        self.assertAlmostEqual( 1.913301e-3, chunk.covariances[6,3] )
        self.assertAlmostEqual( 2.011479e-3, chunk.covariances[6,4] )
        self.assertAlmostEqual( 2.130883e-3, chunk.covariances[6,5] )
        self.assertAlmostEqual( 2.223439e-3, chunk.covariances[6,6] )
        self.assertAlmostEqual( 2.291726e-3, chunk.covariances[6,7] )
        self.assertAlmostEqual( 2.362609e-3, chunk.covariances[6,8] )
        self.assertAlmostEqual( 2.426673e-3, chunk.covariances[6,9] )

        self.assertAlmostEqual( 0., chunk.covariances[7,0] )
        self.assertAlmostEqual( 0., chunk.covariances[7,1] )
        self.assertAlmostEqual( 1.579267e-3, chunk.covariances[7,2] )
        self.assertAlmostEqual( 1.731503e-3, chunk.covariances[7,3] )
        self.assertAlmostEqual( 1.927034e-3, chunk.covariances[7,4] )
        self.assertAlmostEqual( 2.131577e-3, chunk.covariances[7,5] )
        self.assertAlmostEqual( 2.291726e-3, chunk.covariances[7,6] )
        self.assertAlmostEqual( 2.415636e-3, chunk.covariances[7,7] )
        self.assertAlmostEqual( 2.531881e-3, chunk.covariances[7,8] )
        self.assertAlmostEqual( 2.632081e-3, chunk.covariances[7,9] )

        self.assertAlmostEqual( 0., chunk.covariances[8,0] )
        self.assertAlmostEqual( 0., chunk.covariances[8,1] )
        self.assertAlmostEqual( 1.391836e-3, chunk.covariances[8,2] )
        self.assertAlmostEqual( 1.615025e-3, chunk.covariances[8,3] )
        self.assertAlmostEqual( 1.882109e-3, chunk.covariances[8,4] )
        self.assertAlmostEqual( 2.150402e-3, chunk.covariances[8,5] )
        self.assertAlmostEqual( 2.362609e-3, chunk.covariances[8,6] )
        self.assertAlmostEqual( 2.531881e-3, chunk.covariances[8,7] )
        self.assertAlmostEqual( 2.689968e-3, chunk.covariances[8,8] )
        self.assertAlmostEqual( 2.830254e-3, chunk.covariances[8,9] )

        self.assertAlmostEqual( 0., chunk.covariances[9,0] )
        self.assertAlmostEqual( 0., chunk.covariances[9,1] )
        self.assertAlmostEqual( 1.269227e-3, chunk.covariances[9,2] )
        self.assertAlmostEqual( 1.549830e-3, chunk.covariances[9,3] )
        self.assertAlmostEqual( 1.864828e-3, chunk.covariances[9,4] )
        self.assertAlmostEqual( 2.176944e-3, chunk.covariances[9,5] )
        self.assertAlmostEqual( 2.426673e-3, chunk.covariances[9,6] )
        self.assertAlmostEqual( 2.632081e-3, chunk.covariances[9,7] )
        self.assertAlmostEqual( 3.018361e-3, chunk.covariances[9,9] )

    def test_failures( self ) :

        print( '\n' )

if __name__ == '__main__' :

    unittest.main()
