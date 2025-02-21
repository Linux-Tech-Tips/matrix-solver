/** Simple test main file */

#include <iostream>

#include "RationalTest.hh"
#include "MatrixTest.hh"
#include "MatrixUtilTest.hh"

int main(void) {

    /* Calling all Rational test cases */
    rationalTest();

    /* Calling all Matrix test cases */
    matrixTest();

    /* Calling all MatrixUtil test cases */
    matrixUtilTest();

    return 0;
}
