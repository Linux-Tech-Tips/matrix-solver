/** App Main file for the matrix solver */

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

#include "Matrix/Matrix.hh"
#include "Matrix/MatrixUtil.hh"
#include "Rational/Rational.hh"

#include "Rational/RationalTest.hh"
#include "Matrix/MatrixTest.hh"
#include "Matrix/MatrixUtilTest.hh"

/** Asks the user to enter a Matrix and saves it into m */
void enterMatrix(Matrix<Rational>& m);

/** Asks the user for a Matrix, reduces to REF */
void ref(void);

/** Asks the user for a Matrix, reduces to RREF */
void rref(void);

/** Asks the user for a Matrix, prints both REF and RREF */
void forms(void);

/** Asks the user for two Matrices, adds them */
void add(void);

/** Asks the user for two Matrices, subtracts the second from the first */
void sub(void);

/** Asks the user for two Matrices, multiplies them */
void mul(void);

/** Runs Rational and Matrix TCs */
void test(void);

/** Prints out help information */
void help(void);

int main(int argc, char const ** argv) {

    /* Display help info immediately if help asked */
    for(int i = 0; i < argc; ++i) {
	if(std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
	    help();
	    return 0;
	}
    }

    /* Intro Text */
    std::puts("=== C++ Matrix (Gauss-Jordan Elimination) Solver ===");
    std::puts("Enter command (ref/rref/forms/add/sub/mul/test/help/exit)");

    /* Scanning command input from the user until exit */
    bool run = true;
    while(run) {
	std::string userIn;
	std::printf("> ");
	std::getline(std::cin, userIn);
	if(userIn == "ref") {
	    ref();
	} else if(userIn == "rref") {
	    rref();
	} else if(userIn == "forms") {
	    forms();
	} else if(userIn == "add") {
	    add();
	} else if(userIn == "sub") {
	    sub();
	} else if(userIn == "mul") {
	    mul();
	} else if(userIn == "test") {
	    test();
	} else if(userIn == "help") {
	    help();
	} else if(userIn == "exit") {
	    std::puts("Program Exit");
	    run = false;
	} else {
	    std::printf("Error: Unrecognized command: %s\n", userIn.c_str());
	}
    }

    return 0;
}


/* --- Function Implementations --- */

void enterMatrix(Matrix<Rational>& m) {
    std::puts("Enter Matrix (space separated Rational numbers, new line makes a new row, type DONE on a new line to stop):");
    /* Going through user input row by row and saving to get full Matrix */
    std::string matrix;
    while(true) {
	std::string row;
	std::getline(std::cin, row);
	if(row == "DONE" || row == "done")
	    break;
	matrix += row + "\n";
    }
    /* Processing user input to resize and populate Matrix */
    size_t rows = static_cast<size_t>(std::count(matrix.begin(), matrix.end(), '\n'));
    size_t cols = static_cast<size_t>(std::count(matrix.begin(), std::find(matrix.begin(), matrix.end(), '\n'), ' ')) + 1;
    m.resize(cols, rows);
    /* Go through user input to populate Matrix with the correct values */
    size_t col = 0, row = 0;
    std::string number;
    for(char c : matrix) {
	if(c == '\n' || c == ' ') {
	    m.at(col, row) = number;
	    number = "";
	    if(c == '\n') {
		col = 0;
		++row;
	    } else {
		++col;
	    }
	} else {
	    number += c;
	}
    }
}

void ref(void) {
    Matrix<Rational> m;
    enterMatrix(m);
    std::printf("Entered Matrix:\n%s\n", m.print([](Rational r) { return r.toString(); }).c_str());
    MatrixReduce::toREF(m);
    std::printf("Matrix in REF:\n%s\n", m.print([](Rational r) { return r.toString(); }).c_str());
}

void rref(void) {
    Matrix<Rational> m;
    enterMatrix(m);
    std::printf("Entered Matrix:\n%s\n", m.print([](Rational r) { return r.toString(); }).c_str());
    MatrixReduce::toRREF(m);
    std::printf("Matrix in RREF:\n%s\n", m.print([](Rational r) { return r.toString(); }).c_str());
}

void forms(void) {
    Matrix<Rational> m;
    enterMatrix(m);
    std::printf("Entered Matrix:\n%s\n", m.print([](Rational r) { return r.toString(); }).c_str());
    MatrixReduce::toREF(m);
    std::printf("Matrix in REF:\n%s\n", m.print([](Rational r) { return r.toString(); }).c_str());
    MatrixReduce::REFtoRREF(m);
    std::printf("Matrix in RREF:\n%s\n", m.print([](Rational r) { return r.toString(); }).c_str());
}

void add(void) {
    std::puts("1.");
    Matrix<Rational> m1;
    enterMatrix(m1);
    std::puts("2.");
    Matrix<Rational> m2;
    enterMatrix(m2);
    std::printf("Entered Matrices:\n%s\n%s\n", m1.print([](Rational r) { return r.toString(); }).c_str(), m2.print([](Rational r) { return r.toString(); }).c_str());
    try {
        m1 += m2;
	std::printf("Sum:\n%s\n", m1.print([](Rational r) { return r.toString(); }).c_str());
    } catch(std::exception& e) {
	std::printf("Matrix Addition Error: %s\n", e.what());
    }
}

void sub(void) {
    std::puts("1.");
    Matrix<Rational> m1;
    enterMatrix(m1);
    std::puts("2.");
    Matrix<Rational> m2;
    enterMatrix(m2);
    std::printf("Entered Matrices:\n%s\n%s\n", m1.print([](Rational r) { return r.toString(); }).c_str(), m2.print([](Rational r) { return r.toString(); }).c_str());
    try {
        m1 -= m2;
	std::printf("Difference (Matrix1 - Matrix2):\n%s\n", m1.print([](Rational r) { return r.toString(); }).c_str());
    } catch(std::exception& e) {
	std::printf("Matrix Subtraction Error: %s\n", e.what());
    }
}

void mul(void) {
    std::puts("1.");
    Matrix<Rational> m1;
    enterMatrix(m1);
    std::puts("2.");
    Matrix<Rational> m2;
    enterMatrix(m2);
    std::printf("Entered Matrices:\n%s\n%s\n", m1.print([](Rational r) { return r.toString(); }).c_str(), m2.print([](Rational r) { return r.toString(); }).c_str());
    try {
        m1 *= m2;
	std::printf("Product:\n%s\n", m1.print([](Rational r) { return r.toString(); }).c_str());
    } catch(std::exception& e) {
	std::printf("Matrix Multiplication Error: %s\n", e.what());
    }
}

void test(void) {
    /* Calling all Rational test cases */
    rationalTest();

    /* Calling all Matrix test cases */
    matrixTest();

    /* Calling all MatrixUtil test cases */
    matrixUtilTest();
}

void help(void) {
    std::puts("HELP INFORMATION:\n"
	      "This program reduces entered matrices to REF or RREF based on user preference.\n"
	      " -> Available commands:\n"
	      "   -> ref .... reduce to REF\n"
	      "   -> rref ... reduce to RREF\n"
	      "   -> forms .. reduce and show both REF and RREF\n"
	      "   -> add .... add two matrices\n"
	      "   -> sub .... subtract two matrices\n"
	      "   -> mul .... multiply two matrices\n"
	      "   -> test ... run program utility test cases\n"
	      "   -> help ... display this help info\n"
	      "   -> exit ... quit the program\n"
	      " -> Entering Matrices:\n"
	      "   -> enter rational numbers in format [-]<A>[/<B>]\n"
	      "      (A is the numerator, B the denominator, anything in '[]' is optional, anything in '<>' is mandatory, exclude the brackets when entering numbers)\n"
	      "   -> separate each new number in the same row with a single space, end row with a line break\n"
	      "   -> end Matrix input with EOF/Ctrl+d/Ctrl+z"
    );
}
