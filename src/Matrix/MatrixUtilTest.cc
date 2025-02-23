/**
 * @file MatrixTest.cc
 * @author Martin
 * @brief File containing test case implementations for the Matrix class
*/

#include "MatrixUtilTest.hh"

namespace {

void rowSubTest(void) {
    
    Matrix<Rational> m {{4, 5, 6, 7}, {1, 2, 3, 4}, {2, 4, 6, 8}};

    MatrixRowOps::rowSub(m, 0, 1);
    assert(m.at(0, 0) == 3 && m.at(1, 0) == 3 && m.at(2, 0) == 3 && m.at(3, 0) == 3);

    MatrixRowOps::rowSub(m, 2, Rational{2}, 1);
    assert(m.at(0, 2) == 0 && m.at(1, 2) == 0 && m.at(2, 2) == 0 && m.at(3, 2) == 0);
}

void rowMulDivTest(void) {

    Matrix<Rational> m {{1, 2, 3, 4}, {1, 3, 5, 7}, {10, 20, 30, 40}};

    MatrixRowOps::rowMul(m, 0, Rational{2});
    assert(m.at(0, 0) == 2 && m.at(1, 0) == 4 && m.at(2, 0) == 6 && m.at(3, 0) == 8);

    MatrixRowOps::rowDiv(m, 2, Rational{10});
    assert(m.at(0, 2) == 1 && m.at(1, 2) == 2 && m.at(2, 2) == 3 && m.at(3, 2) == 4);
}

void rowSwapTest(void) {

    Matrix<Rational> m {{1, 3, 5, 7}, {1, 2, 3, 4}, {2, 4, 6, 8}};

    MatrixRowOps::rowSwap(m, 0, 2);
    assert(m.at(0, 0) == 2 && m.at(1, 0) == 4 && m.at(2, 0) == 6 && m.at(3, 0) == 8);
    assert(m.at(0, 2) == 1 && m.at(1, 2) == 3 && m.at(2, 2) == 5 && m.at(3, 2) == 7);

    MatrixRowOps::rowSwap(m, 1, 0);
    assert(m.at(0, 1) == 2 && m.at(1, 1) == 4 && m.at(2, 1) == 6 && m.at(3, 1) == 8);
    assert(m.at(0, 0) == 1 && m.at(1, 0) == 2 && m.at(2, 0) == 3 && m.at(3, 0) == 4);
}

} /* anonymous */

/** Function containing test cases for the Matrix class */
void matrixUtilTest(void) {

    std::puts("--- MatrixUtil RowOps TC Running ---");
    rowSubTest();
    std::puts("-> Passed rowSubTest()");
    rowMulDivTest();
    std::puts("-> Passed rowMulDivTest()");
    rowSwapTest();
    std::puts("-> Passed rowSwapTest()");
    std::puts("--- MatrixUtil RowOps Tests Passed ---");
}
