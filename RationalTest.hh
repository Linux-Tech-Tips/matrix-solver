/**
 * @file RationalTest.hh
 * @author Martin
 * @brief File containing test cases for the Rational class
*/
#ifndef RATIONAL_TEST_H
#define RATIONAL_TEST_H

#include <iostream>
#include <cassert>

#include "Rational.hh"

namespace {

void constructorTest(void) {

    /* A/B/Negative Constructor */
    Rational ar1(1, 2);
    Rational ar2(3, 4);
    Rational ar3(1, 2, true);
    Rational ar4(6, 4);
    Rational ar5(51, 6, true);

    assert(ar1.getNumerator() == 1 && ar1.getDenominator() == 2 && ar1.isNegative() == false);
    assert(ar2.getNumerator() == 3 && ar2.getDenominator() == 4 && ar2.isNegative() == false);
    assert(ar3.getNumerator() == 1 && ar3.getDenominator() == 2 && ar3.isNegative() == true);
    /* ar4 should be simplified to 3/2 */
    assert(ar4.getNumerator() == 3 && ar4.getDenominator() == 2 && ar4.isNegative() == false);
    /* ar5 should be simplified to 17/2 */
    assert(ar5.getNumerator() == 17 && ar5.getDenominator() == 2 && ar5.isNegative() == true);

    /* Float Constructor */
    Rational fr1(0.5f);
    Rational fr2(-0.1f);
    Rational fr3(0.33f);
    Rational fr4(0.111111f);
    Rational fr5(-12.7f);

    assert(fr1.getNumerator() == 1 && fr1.getDenominator() == 2 && fr1.isNegative() == false);
    assert(fr2.getNumerator() == 1 && fr2.getDenominator() == 10 && fr2.isNegative() == true);
    assert(fr3.getNumerator() == 33 && fr3.getDenominator() == 100 && fr3.isNegative() == false);
    assert(fr4.getNumerator() == 111111 && fr4.getDenominator() == 1000000 && fr4.isNegative() == false);
    assert(fr5.getNumerator() == 127 && fr5.getDenominator() == 10 && fr5.isNegative() == true);

    /* Int Constructor */
    Rational ir1(5);
    Rational ir2(-325);

    assert(ir1.getNumerator() == 5 && ir1.getDenominator() == 1 && ir1.isNegative() == false);
    assert(ir2.getNumerator() == 325 && ir2.getDenominator() == 1 && ir2.isNegative() == true);

    /* String Constructor */
    Rational sr1("1/2");
    Rational sr2("-5/7");
    Rational sr3("9/12");
    Rational sr4("0.5");
    Rational sr5("-0.2");
    
    assert(sr1.getNumerator() == 1 && sr1.getDenominator() == 2 && sr1.isNegative() == false);
    assert(sr2.getNumerator() == 5 && sr2.getDenominator() == 7 && sr2.isNegative() == true);
    assert(sr3.getNumerator() == 3 && sr3.getDenominator() == 4 && sr3.isNegative() == false);
    assert(sr4.getNumerator() == 1 && sr4.getDenominator() == 2 && sr4.isNegative() == false);
    assert(sr5.getNumerator() == 1 && sr5.getDenominator() == 5 && sr5.isNegative() == true);

    bool caught = false;
    try {
	Rational sr6("5This is not valid!4");
    } catch(const std::exception& e) {
	caught = true;
    }
    assert(caught);

    /* Void Constructor */
    Rational vr1;

    assert(vr1.getNumerator() == 0 && vr1.getDenominator() == 1 && vr1.isNegative() == false);

    /* Special Case 1: Simplifying to zero */
    Rational cr1(0, 45, true);

    assert(cr1.getNumerator() == 0 && cr1.getDenominator() == 1 && cr1.isNegative() == false);

}

void modifyTest(void) {

    /* Testing negate() */
    Rational n1(3, 4, false);
    Rational n2(5, 6, true);

    n1.negate();
    n2.negate();

    assert(n1.getNumerator() == 3 && n1.getDenominator() == 4 && n1.isNegative() == true);
    assert(n2.getNumerator() == 5 && n2.getDenominator() == 6 && n2.isNegative() == false);

    /* Testing invert() */
    Rational i1(1, 2, false);
    Rational i2(3, 4, true);

    i1.invert();
    i2.invert();

    assert(i1.getNumerator() == 2 && i1.getDenominator() == 1 && i1.isNegative() == false);
    assert(i2.getNumerator() == 4 && i2.getDenominator() == 3 && i2.isNegative() == true);

    /* Special Case 1: Zero has no inverse element */
    Rational i3;

    bool caught = false;
    try {
	i3.invert();
    } catch(std::exception& e) {
	caught = true;
    }

    assert(caught);

}

} /* anonymous */

/** Rational test function, collecting all test cases */
void rationalTest(void) {

    std::puts("--- Rational TC Running ---");
    constructorTest();
    std::puts("-> Passed constructorTest()");
    modifyTest();
    std::puts("-> Passed modifyTest()");

    // TODO TC PLAN:
    //  -> Creating and verifying valid creation of Rational, all constructors (a/b/n, float, int, string, void)
    //  -> Modifying the number using invert() and negate(), then verifying numbers using get... functions
    //  -> Verifying conversion to string and to float
    //  -> Verifying all overloaded operators
    //    -> assignment
    //    -> comparisons (==, !=, <, >, <=, >=)
    //    -> arithmetic (+=, -=, *=, /=, +, -, *, /)

    std::puts("--- Rational Tests Passed ---");

}


#endif /* RATIONAL_TEST_H */
