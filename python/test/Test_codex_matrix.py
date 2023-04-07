# standard imports
import unittest

# third party imports

# local imports
import numpy
from codex import is_square, is_symmetric

class Test_codex_matrix( unittest.TestCase ) :
    """Unit test for matrix functions."""

    def test_diagonal_covariance_block( self ) :

        square_symmetric = numpy.array( [ [ 1., 2. ], [ 2., 4. ] ] )
        square_notsymmetric = numpy.array( [ [ 1., 2. ], [ 1000., 4. ] ] )
        notsquare = numpy.array( [ [ 1., 2. ], [ 2., 4. ], [ 3., 6. ] ] )

        # verify
        self.assertEqual( true, is_square( square_symmetric ) )
        self.assertEqual( true, is_square( square_notsymmetric ) )
        self.assertEqual( false, is_square( notsquare ) )

        self.assertEqual( true, is_symmetric( square_symmetric ) )
        self.assertEqual( false, is_symmetric( square_notsymmetric ) )
        self.assertEqual( false, is_symmetric( notsquare ) )

if __name__ == '__main__' :

    unittest.main()
