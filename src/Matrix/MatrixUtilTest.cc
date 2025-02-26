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

void formValidateTest(void) {

    Matrix<Rational> m1 {{1, 2, 3, 4, 5}, {0, 1, 2, 3, 4}, {0, 0, 1, 2, 3}, {0, 0, 0, 1, 2}};
    Matrix<Rational> m2 {{1, 2, 3, 4, 5}, {0, 0, 1, 2, 3}, {0, 0, 0, 1, 2}, {0, 0, 0, 0, 0}};
    Matrix<Rational> m3 {{0, 1, 2, 3, 4}, {0, 0, 0, 1, 2}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    assert(MatrixReduce::isREF(m1));
    assert(MatrixReduce::isREF(m2));
    assert(MatrixReduce::isREF(m3));

    Matrix<Rational> m4 {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
    Matrix<Rational> m5 {{1, 2, 3, 4, 5}, {0, 2, 3, 4, 5}, {0, 0, 1, 2, 3}, {0, 0, 0, 1, 2}};
    Matrix<Rational> m6 {{0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}, {0, 0, 1, 2, 3}, {0, 0, 0, 1, 2}};

    assert(!MatrixReduce::isREF(m4));
    assert(!MatrixReduce::isREF(m5));
    assert(!MatrixReduce::isREF(m6));

    Matrix<Rational> m7 {{1, 0, 0, 0, 5}, {0, 1, 0, 0, 4}, {0, 0, 1, 0, 3}, {0, 0, 0, 1, 2}};
    Matrix<Rational> m8 {{0, 1, 0, 0, 5}, {0, 0, 1, 0, 4}, {0, 0, 0, 1, 2}, {0, 0, 0, 0, 0}};
    Matrix<Rational> m9 {{1, 2, 0, 0, 5}, {0, 0, 1, 0, 4}, {0, 0, 0, 1, 3}, {0, 0, 0, 0, 0}};

    assert(MatrixReduce::isREF(m7, true));
    assert(MatrixReduce::isREF(m8, true));
    assert(MatrixReduce::isREF(m9, true));
    assert(MatrixReduce::isRREF(m7));
    assert(MatrixReduce::isRREF(m8));
    assert(MatrixReduce::isRREF(m9));
}

void matrixReduceTest(void) {

    /* --- REF TC --- */

    Matrix<Rational> m1 = {{0, 2, 2}, {1, 3, 3}, {2, 4, 2}};
    Matrix<Rational> m2 = {{1, 2, 3, 1}, {4, 5, 6, -2}, {7, 8, 3, 1}};
    Matrix<Rational> m3 = {{1, 2, 3, 9}, {2, -1, 1, 8}, {3, 0, -1, 3}};
    Matrix<Rational> m4 = {{1, 3, 3, 8, 5}, {0, 1, 3, 10, 8}, {0, 0, 0, -1, -4}, {0, 0, 0, 2, 8}};
    Matrix<Rational> m5 = {{1, 2, -2, 7}, {0, 1, 5, 6}, {0, 0, 1, -3}, {0, 0, 0, 0}};

    assert(!MatrixReduce::isREF(m1));
    assert(MatrixReduce::toREF(m1));
    assert(MatrixReduce::isREF(m1));

    assert(!MatrixReduce::isREF(m2));
    assert(MatrixReduce::toREF(m2));
    assert(MatrixReduce::isREF(m2));

    assert(!MatrixReduce::isREF(m3));
    assert(MatrixReduce::toREF(m3));
    assert(MatrixReduce::isREF(m3));

    assert(!MatrixReduce::isREF(m4));
    assert(MatrixReduce::toREF(m4));
    assert(MatrixReduce::isREF(m4));

    /* m5 is already in REF, so the first assert should ensure that it is */
    assert(MatrixReduce::isREF(m5));
    assert(MatrixReduce::toREF(m5));
    assert(MatrixReduce::isREF(m5));

    std::puts(" -> matrixReduceTest(): Passed REF TC");

    /* --- REF->RREF TC --- */

    assert(!MatrixReduce::isRREF(m1));
    assert(MatrixReduce::REFtoRREF(m1));
    assert(MatrixReduce::isRREF(m1));

    assert(!MatrixReduce::isRREF(m2));
    assert(MatrixReduce::REFtoRREF(m2));
    assert(MatrixReduce::isRREF(m2));

    assert(!MatrixReduce::isRREF(m3));
    assert(MatrixReduce::REFtoRREF(m3));
    assert(MatrixReduce::isRREF(m3));

    assert(!MatrixReduce::isRREF(m4));
    assert(MatrixReduce::REFtoRREF(m4));
    assert(MatrixReduce::isRREF(m4));

    assert(!MatrixReduce::isRREF(m5));
    assert(MatrixReduce::REFtoRREF(m5));
    assert(MatrixReduce::isRREF(m5));

    std::puts(" -> matrixReduceTest(): Passed REF->RREF TC");

    /* --- RREF TC --- */
    Matrix<Rational> m6 = {{0, 2, 2}, {1, 3, 3}, {2, 4, 2}};
    Matrix<Rational> m7 = {{1, 2, 3, 1}, {4, 5, 6, -2}, {7, 8, 3, 1}};
    Matrix<Rational> m8 = {{1, 2, 3, 9}, {2, -1, 1, 8}, {3, 0, -1, 3}};
    Matrix<Rational> m9 = {{1, 3, 3, 8, 5}, {0, 1, 3, 10, 8}, {0, 0, 0, -1, -4}, {0, 0, 0, 2, 8}};
    Matrix<Rational> m10 = {{1, 2, -2, 7}, {0, 1, 5, 6}, {0, 0, 1, -3}, {0, 0, 0, 0}};

    assert(!MatrixReduce::isRREF(m6));
    assert(MatrixReduce::toRREF(m6));
    assert(MatrixReduce::isRREF(m6));

    assert(!MatrixReduce::isRREF(m7));
    assert(MatrixReduce::toRREF(m7));
    assert(MatrixReduce::isRREF(m7));

    assert(!MatrixReduce::isRREF(m8));
    assert(MatrixReduce::toRREF(m8));
    assert(MatrixReduce::isRREF(m8));

    assert(!MatrixReduce::isRREF(m9));
    assert(MatrixReduce::toRREF(m9));
    assert(MatrixReduce::isRREF(m9));

    assert(!MatrixReduce::isRREF(m10));
    assert(MatrixReduce::toRREF(m10));
    assert(MatrixReduce::isRREF(m10));

    std::puts(" -> matrixReduceTest(): Passed RREF TC");
}

void matrixInvertTest(void) {

    Matrix<Rational> m1 {{4, 3}, {3, 2}};
    Matrix<Rational> m2 {{5, 8}, {12, 34}};
    Matrix<Rational> m3 {{4, 2, 3}, {7, 8, 6}, {1, 9, 5}};
    Matrix<Rational> m4 {{1, 2, 3, 4}, {7, 8, 10, 11}, {9, 1, 6, 8}, {1, 9, 9, 9}};
    Matrix<Rational> m5 {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix<Rational> m6 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    assert(MatrixReduce::invert(m1));
    Matrix<Rational> r1 {{-2, 3}, {3, -4}};
    assert(m1 == r1);

    assert(MatrixReduce::invert(m2));
    Matrix<Rational> r2 {{"17/37", "-4/37"}, {"-6/37", "5/74"}};
    assert(m2 == r2);

    assert(MatrixReduce::invert(m3));
    Matrix<Rational> r3 {{"-14/51", "1/3", "-4/17"}, {"-29/51", "1/3", "-1/17"}, {"55/51", "-2/3", "6/17"}};
    assert(m3 == r3);

    assert(MatrixReduce::invert(m4));
    Matrix<Rational> r4 {{"-3/26", "9/26", "-3/26", "-7/26"}, {"31/78", "21/26", "-47/78", "-49/78"}, {"-145/78", "-37/26", "89/78", "121/78"}, {"115/78", "15/26", "-41/78", "-61/78"}};
    assert(m4 == r4);

    assert(MatrixReduce::invert(m5));
    Matrix<Rational> r5 {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    assert(m5 == r5);

    assert(!MatrixReduce::invert(m6));
}

} /* anonymous */

/** Function containing test cases for the Matrix class */
void matrixUtilTest(void) {

    std::puts("--- MatrixUtil MatrixRowOps TC Running ---");
    rowSubTest();
    std::puts("-> Passed rowSubTest()");
    rowMulDivTest();
    std::puts("-> Passed rowMulDivTest()");
    rowSwapTest();
    std::puts("-> Passed rowSwapTest()");
    std::puts("--- MatrixUtil MatrixRowOps Tests Passed ---");

    std::puts("--- MatrixUtil MatrixReduce TC Running ---");
    formValidateTest();
    std::puts("-> Passed formValidateTest()");
    matrixReduceTest();
    std::puts("-> Passed matrixReduceTest()");
    matrixInvertTest();
    std::puts("-> Passed matrixInvertTest()");
    std::puts("--- MatrixUtil MatrixReduce Tests Passed ---");
}
