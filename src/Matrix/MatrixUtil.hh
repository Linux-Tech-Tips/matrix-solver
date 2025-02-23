/**
 * @file Matrix.hh
 * @author Martin
 * @brief File containing Matrix class utility functions
*/
#ifndef MATRIX_UTIL_H
#define MATRIX_UTIL_H

#include <utility>

#include "Matrix.hh"

namespace MatrixRowOps {

    /** Substitutes a multiple of row2 from row1 (row1 -= multiple * row2) */
    template <typename T>
    void rowSub(Matrix<T>& m, size_t row1Idx, T multiple, size_t row2Idx) {
	for(size_t idx = 0; idx < m.getCols(); ++idx) {
	    m.at(idx, row1Idx) -= multiple * m.at(idx, row2Idx);
	}
    }

    /** Substitutes row2 from row1 (row1 -= row2) */
    template <typename T>
    void rowSub(Matrix<T>& m, size_t row1Idx, size_t row2Idx) {
	rowSub(m, row1Idx, T{1}, row2Idx);
    }
    
    /** Multiplies a row with the given element (row *= multiple) */
    template <typename T>
    void rowMul(Matrix<T>& m, size_t rowIdx, T multiple) {
	for(size_t idx = 0; idx < m.getCols(); ++idx) {
	    m.at(idx, rowIdx) *= multiple;
	}
    }
    
    /** Divides a row with the given element (row /= divisor) */
    template <typename T>
    void rowDiv(Matrix<T>& m, size_t rowIdx, T divisor) {
	for(size_t idx = 0; idx < m.getCols(); ++idx) {
	    m.at(idx, rowIdx) /= divisor;
	}
    }
    
    /** Swaps row1 and row2 */
    template <typename T>
    void rowSwap(Matrix<T>& m, size_t row1Idx, size_t row2Idx) {
         for(size_t idx = 0; idx < m.getCols(); ++idx) {
	    std::swap(m.at(idx, row1Idx), m.at(idx, row2Idx));
	}   
    }

} /* namespace MatrixRowOps */


namespace MatrixReduce {

// TODO FUNCTIONS TO REDUCE TO REF AND RREF

} /* namespace MatrixReduce */


#endif /* MATRIX_UTIL_H */
