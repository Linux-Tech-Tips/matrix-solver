/**
 * @file MatrixTest.cc
 * @author Martin
 * @brief File containing test case implementations for the Matrix class
*/

#include "MatrixTest.hh"

namespace {

void constructorTest(void) {

    Matrix<Rational> m1 {4, 3};
    Matrix<Rational> m2 {8, 9};
    Matrix<Rational> m3 {3, 3, 4.0f};
    Matrix<Rational> m4 {4, 2, "-1/2"};
    Matrix<Rational> m5 {{1, 2, 3}, {4.0f, 5.0f, 6.0f}, {"7", "8", "9"}};
    Matrix<Rational> m6 {{1.2f, 3.4f, 7.6f, 0.8f}, {"1/2", "-3/4", "8/9", "4/3"}};
    Matrix<Rational> m7;

    assert(m1.getCols() == 4 && m1.getRows() == 3 && (m1.at(0, 0) == 0));
    assert(m2.getCols() == 8 && m2.getRows() == 9 && (m2.at(0, 0) == 0));
    assert(m3.getCols() == 3 && m3.getRows() == 3 && (m3.at(0, 0) == 4));
    assert(m4.getCols() == 4 && m4.getRows() == 2 && (m4.at(0, 0) == "-1/2"));
    assert(m5.getCols() == 3 && m5.getRows() == 3 && (m5.at(0, 0) == 1));
    assert(m6.getCols() == 4 && m6.getRows() == 2 && (m6.at(0, 0) == "6/5"));
    assert(m7.getCols() == 0 && m7.getRows() == 0);

    /* Incorrect initializer list constructor test */
    bool caught = false;
    try {
	Matrix<Rational> m8 {{1, 2, 3, 4}, {1, 2, 3}, {1, 2}};
    } catch(std::exception& e) {
	caught = true;
    }
    assert(caught);
}

void accessTest(void) {

    Matrix<Rational> m1 {4, 3};
    Matrix<Rational> m2 {5, 6, 7.8f};
    Matrix<Rational> m3 {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    Matrix<Rational> m4 {{1.2f, 3.4f, 7.6f, 0.8f}, {"1/2", "-3/4", "8/9", "4/3"}};

    /* Access test - corner points */
    assert(m1.at(0, 0) == 0 && m1.at(0, 2) == 0 && m1.at(3, 0) == 0 && m1.at(3, 2) == 0);
    assert(m2.at(0, 0) == 7.8f && m2.at(0, 5) == 7.8f && m2.at(4, 0) == 7.8f && m2.at(4, 5) == 7.8f);

    /* Access test - out of bounds test */
    int caught = 0;
    try {
	m1.at(0, 3);
    } catch(std::exception& e) {
	++caught;
    }
    try {
	m1.at(4, 0);
    } catch(std::exception& e) {
	++caught;
    }
    try {
	m1.at(4, 3);
    }  catch(std::exception& e) {
	++caught;
    }
    assert(caught == 3);

    /* Access test - initializer list-based edge test */
    assert(m3.at(0, 0) == 1 && m3.at(0, 1) == 5 && m3.at(0, 2) == 9);
    assert(m3.at(3, 0) == 4 && m3.at(3, 1) == 8 && m3.at(3, 2) == 12);

    /* Access test - initializer list-based random access test */
    assert(m4.at(0, 0) == 1.2f && m4.at(2, 0) == 7.6f && m4.at(1, 1) == "-3/4" && m4.at(3, 1) == "4/3");
}

void resizeTest(void) {

    Matrix<Rational> m1 {{4.2f, 8.9f, 1.1f}, {3.4f, 6.2f, 7.7f}};

    std::puts("resizeTest: Matrix 1:");
    std::puts(m1.print([](Rational r) { return r.toString(); }).c_str());
    assert(m1.getCols() == 3 && m1.getRows() == 2);
    assert(m1.at(0, 0) == 4.2f && m1.at(2, 1) == 7.7f);

    /* Extend Matrix */
    m1.resize(5, 3);

    std::puts("resizeTest: Matrix 2:");
    std::puts(m1.print([](Rational r) { return r.toString(); }).c_str());
    assert(m1.getCols() == 5 && m1.getRows() == 3);
    assert(m1.at(0, 0) == 4.2f && m1.at(2, 1) == 7.7f && m1.at(4, 2) == 0);

    /* Shrink Matrix */
    m1.resize(2, 3);

    std::puts("resizeTest: Matrix 3:");
    std::puts(m1.print([](Rational r) { return r.toString(); }).c_str());
    assert(m1.getCols() == 2 && m1.getRows() == 3);
    assert(m1.at(0, 0) == 4.2f && m1.at(1, 1) == 6.2f && m1.at(1, 2) == 0);
}

void printTest(void) {

    /* This test is purely to ensure that printing various matrices works, and can be judged visually */
    Matrix<Rational> m1;
    Matrix<Rational> m2 {4, 3};
    Matrix<Rational> m3 {{1, 2, "5/8", "7/13"}, {5.2f, 3.1f, 6.5f, 70.0f}, {32565, 789.4256f, "147885646/1345453", 10.2f}};

    std::puts("printTest: Matrices:");
    try {
	std::puts(m1.print([](Rational r) { return r.toString(); }).c_str());
	std::puts(m2.print([](Rational r) { return r.toString(); }).c_str());
	std::puts(m3.print([](Rational r) { return r.toString(); }).c_str());
    } catch(std::exception& e) {
	assert(false);
    }
}

void equalsTest(void) {

    Matrix<Rational> m1 {{1, 2, 3, 4}, {5, 6, 7, 8}, {9.1f, 9.2f, 9.3f, 9.4f}};
    Matrix<Rational> m2 {{1, 2, 3}, {4, 5, 6}};

    assert(m1.getCols() == 4 && m1.getRows() == 3 && m1.at(3, 2) == 9.4f);
    assert(m2.getCols() == 3 && m2.getRows() == 2 && m2.at(2, 1) == 6);

    m2 = m1;
    m1.at(3, 2) = 4.2f;

    assert(m1.getCols() == 4 && m1.getRows() == 3 && m1.at(3, 2) == 4.2f);
    assert(m2.getCols() == 4 && m2.getRows() == 3 && m2.at(3, 2) == 9.4f);
}

void compareTest(void) {

    Matrix<Rational> m1 {{1, 2, 3}, {4, 5, 6}};
    Matrix<Rational> m2 {{1, 2, 3}, {4, 5, 6}};
    Matrix<Rational> m3 {{1, 2}, {3, 4}, {5, 6}};
    Matrix<Rational> m4 {{8, 9}, {10, 11}};

    assert(m1 == m2 && m2 == m1);
    assert(m1 != m3 && m3 != m1 && m2 != m3 && m3 != m2);
    assert(m1 != m4 && m4 != m1 && m3 != m4 && m4 != m3);
}

void arithmeticTest(void) {

    /* Addition */
    Matrix<Rational> m1 {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    Matrix<Rational> m2 {{10, 20, 30, 40}, {50, 60, 70, 80}, {90, 100, 110, 120}};
    Matrix<Rational> m3;

    m3 = m1 + m2;
    m1 += m2;

    assert(m1 == m3);
    assert(m3.at(0, 0) == 11 && m3.at(3, 0) == 44 && m3.at(0, 2) == 99 && m3.at(3, 2) == 132);

    /* Multiplication */
    Matrix<Rational> m4 {{1, 2}, {3, 4}, {5, 6}};
    Matrix<Rational> m5 {{1, 2, 3}, {4, 5, 6}};
    Matrix<Rational> m7;
    Matrix<Rational> m8;

    m7 = m4 * m5;
    m8 = m5 * m4;
    m4 *= m5;

    assert(m7 != m8);
    assert(m4 == m7 && m4 != m8);
    assert(m7.getCols() == 3 && m7.getRows() == 3);
    assert(m8.getCols() == 2 && m8.getRows() == 2);
    assert(m7.at(0, 0) == 9);
    assert(m8.at(0, 0) == 22);

    /* Scalar-Matrix Multiplication */
    m7 = m5 * 8;
    m8 = 2 * m5;

    assert(m7.getCols() == 3 && m7.getRows() == 2);
    assert(m7.at(0, 0) == 8);
    assert(m8.getCols() == 3 && m8.getRows() == 2);
    assert(m8.at(0, 0) == 2);

    /* Invalid shapes */
    uint8_t caught = 0;
    try {
	m1 + m4;
    } catch(std::exception& e) {
	++caught;
    }
    try {
	m1 * m4;
    } catch(std::exception& e) {
	++caught;
    }
    assert(caught == 2);
}

void identityTest(void) {

    Matrix<Rational> i1 = Matrix<Rational>::identity(1);
    Matrix<Rational> i2 = Matrix<Rational>::identity(2);
    Matrix<Rational> i3 = Matrix<Rational>::identity(3);
    Matrix<Rational> i4 = Matrix<Rational>::identity(4);
    Matrix<Rational> i5 = Matrix<Rational>::identity(5);

    assert(i1.at(0, 0) == 1);
    assert(i2.at(1, 1) == 1);
    assert(i3.at(2, 2) == 1);
    assert(i4.at(3, 3) == 1);
    assert(i5.at(4, 4) == 1);

}

} /* anonymous */

/** Function containing test cases for the Matrix class */
void matrixTest(void) {

    std::puts("--- Matrix TC Running ---");
    constructorTest();
    std::puts("-> Passed constructorTest()");
    accessTest();
    std::puts("-> Passed accessTest()");
    resizeTest();
    std::puts("-> Passed resizeTest()");
    printTest();
    std::puts("-> Passed printTest()");
    equalsTest();
    std::puts("-> Passed equalsTest()");
    compareTest();
    std::puts("-> Passed compareTest()");
    arithmeticTest();
    std::puts("-> Passed arithmeticTest()");
    identityTest();
    std::puts("-> Passed identityTest()");

    std::puts("--- Matrix Tests Passed ---");
}
