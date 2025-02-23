/** Test Main file, meant to test functionality */

#include <iostream>

#include "Rational/RationalTest.hh"
#include "Matrix/MatrixTest.hh"
#include "Matrix/MatrixUtilTest.hh"

int main(void) {

    /* Calling all Rational test cases */
    rationalTest();

    /* Calling all Matrix test cases */
    matrixTest();

    /* Calling all MatrixUtil test cases */
    matrixUtilTest();

    return 0;
}
