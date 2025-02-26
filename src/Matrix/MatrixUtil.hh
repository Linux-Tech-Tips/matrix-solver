/**
 * @file MatrixUtil.hh
 * @author Martin
 * @brief File containing Matrix utility functions
*/
#ifndef MATRIX_UTIL_H
#define MATRIX_UTIL_H

#include <utility>

#include "Matrix.hh"

/** Namespace containing Matrix Row Operation functions */
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


/** Namespace containing Matrix Reduction functions */
namespace MatrixReduce {

    /** Checks whether a given Matrix is in Row Echelon Form */
    template <typename T>
    bool isREF(Matrix<T>& m, bool reduced = false) {
	/* Current considered top of each next column, moves downwards as the function progresses through the columns */
	size_t top = 0;
	/* Go through the Matrix column by column, checking the next top element */
	for(size_t col = 0; (col < m.getCols() && top < m.getRows()); ++col) {
	    /* The allowed values for any current column top are 1 or 0 */
	    if(m.at(col, top) != 1 && m.at(col, top) != 0)
		return false;
	    /* If the top value is 1, move the top downwards for the next column, and check the entire column if RREF */
	    if(m.at(col, top) == 1) {
		/* If validating RREF, the entire column with a leading one must be 0 */
		if(reduced) {
		    for(size_t row = 0; row < top; ++row) {
			if(m.at(col, row) != 0)
			    return false;
		    }
		}
		++top;
	    }
	    /* Go through the rest of the column and ensure everything under the pivot/top is zero */
	    for(size_t row = top; row < m.getRows(); ++row) {
		if(m.at(col, row) != 0)
		    return false;
	    }
	}
	/* The Matrix is in REF if no invalid spaces found */
        return true;
    }

    /** Checks whether a given Matrix is in Reduced Row Echelon Form */
    template <typename T>
    bool isRREF(Matrix<T>& m) {
	return isREF(m, true);
    }

    /** Reduces a Matrix to Row Echelon Form (REF) */
    template <typename T>
    bool toREF(Matrix<T>& m) {
	/* Check that the Matrix isn't already in REF, return immediately if it is */
	if(isREF(m))
	    return true;
	/* The column for which the algorithm is currently trying to set a pivot (leading zeros and a one) */
	size_t currentCol = 0;
	/* The number of pivots in the echelon that were skipped, to ensure rows swapped into the correct place */
	size_t skippedPivots = 0;
	/* The real column of the pivots at any current column */
	size_t pivots [m.getCols()];
	/* Iterating through the Matrix until we get to the bottom row with the last pivot or until we run out of columns */
	while((currentCol - skippedPivots) < m.getRows() && currentCol < m.getCols()) {
	    /* Find next row with a non-zero scalar at the current column to continue the diagonal */
	    size_t rowIdx;
	    for(rowIdx = (currentCol - skippedPivots); rowIdx < m.getRows(); ++rowIdx) {
		/* End loop at first non-zero column index to keep the rowIdx we want */
		if(m.at(currentCol, rowIdx) != 0)
		    break;
	    }
	    /* If no row with a scalar at this column found, increment the column and try again */
	    if(rowIdx == m.getRows()) {
		++currentCol;
		++skippedPivots;
		continue;
	    }
	    /* Swap the row into the correct position if not already correct */
	    if((rowIdx + skippedPivots) != currentCol) {
		MatrixRowOps::rowSwap(m, rowIdx, currentCol);
		/* Set the row index to the row we swapped to */
		rowIdx = currentCol;
	    }
	    /* If the row contains leading non-zero scalars, reduce until the leading numbers are all zero */
	    for(size_t x = 0; x < currentCol; ++x) {
		if(m.at(x, rowIdx) != 0) {
		    T scale = m.at(x, rowIdx);
		    MatrixRowOps::rowSub(m, rowIdx, scale, pivots[x]);
		}
	    }
	    /* If the pivot is zero as well, retry iteration */
	    if(m.at(currentCol, rowIdx) == 0)
		continue;
	    /* Reduce row diagonal to 1 */
	    T divisor = m.at(currentCol, rowIdx);
	    if(divisor != 1)
		MatrixRowOps::rowDiv(m, rowIdx, divisor);
	    /* Record real row location of pivot for the current column */
	    pivots[currentCol] = (currentCol - skippedPivots);
	    /* Move to the next column */
	    ++currentCol;
	}
	/* Once the loop is done, the Matrix should be in REF */
	return true;
    }

    /** Reduces a Matrix that is in REF to Reduced Row Echelon Form (RREF), returns false if incorrect Matrix given */
    template <typename T>
    bool REFtoRREF(Matrix<T>& m) {
	/* Don't proceed if input not in REF */
	if(!isREF(m))
	    return false;
	/* Keep track of current pivot row */
	size_t pivot = 0;
	/* Go through each column and reduce zeros above the pivot, if any found */
	for(size_t col = 0; (col < m.getCols() && pivot < m.getRows()); ++col) {
	    /* Skip column if pivot is zero */
	    if(m.at(col, pivot) == 0)
		continue;
	    /* If the pivot is one, go through all leading row values and subtract */
	    if(m.at(col, pivot) == 1) {
		for(size_t rowIdx = 0; rowIdx < pivot; ++rowIdx) {
		    if(m.at(col, rowIdx) != 0) {
			T scale = m.at(col, rowIdx);
			MatrixRowOps::rowSub(m, rowIdx, scale, pivot);
		    }
		}
		++pivot;
	    } else {
		/* Cancel function if something other than 1 or 0 found at the pivot spot */
		return false;
	    }
	}
	/* Once the loop is done, the REF Matrix should be in RREF */
	return true;
    }

    /** Reduces a Matrix to Reduced Row Echelon Form (RREF) */
    template <typename T>
    bool toRREF(Matrix<T>& m) {
	/* Return immediately if Matrix in RREF already */
	if(isRREF(m))
	    return true;
	/* Convert to REF */
	if(!toREF(m))
	    return false;
	/* Convert REF to RREF */
	if(!REFtoRREF(m))
	    return false;
	/* After converting first to REF and then to RREF, the Matrix will be in RREF */
	return true;
    }

    /** Inverts the given matrix, returns whether successful or not */
    template <typename T>
    bool invert(Matrix<T>& m) {
	/* Create the augmented Matrix to use for the inversion, twice the columns of m */
	Matrix<T> augmented {2 * m.getCols(), m.getRows(), 0};
	/* Populate the augmented Matrix */
	for(size_t row = 0; row < augmented.getRows(); ++row) {
	    /* Copying over left half */
	    for(size_t col = 0; col < m.getCols(); ++col) {
		augmented.at(col, row) = m.at(col, row);
	    }
	    /* Setting the correct pivot one in the right half */
	    augmented.at(m.getCols() + row, row) = 1;
	}
	/* Reduce to RREF */
	if(!toRREF(augmented))
	    return false;
	/* Check that the left is the identity matrix */
	for(size_t row = 0; row < m.getRows(); ++row) {
	    for(size_t col = 0; col < m.getCols(); ++col) {
		if(augmented.at(col, row) != (row == col ? 1 : 0))
		    return false;
	    }
	}
	/* The left is the identity, overwrite m with the right half and return true */
	for(size_t row = 0; row < m.getRows(); ++row) {
	    for(size_t col = 0; col < m.getCols(); ++col) {
		m.at(col, row) = augmented.at(m.getCols() + col, row);
	    }
	}
	return true;
    }

} /* namespace MatrixReduce */


#endif /* MATRIX_UTIL_H */
