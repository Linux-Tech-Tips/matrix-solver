/**
 * @file Matrix.hh
 * @author Martin
 * @brief File containing the class representing an NxM matrix
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <stdexcept>
#include <memory>
#include <cstdint>
#include <initializer_list>
#include <functional>

/** Class representing an N by M matrix of any object */
template <typename T>
class Matrix {

    private:
	/** The number of columns in the matrix (width) */
	size_t m_cols;
	/** The number of rows in the matrix (height) */
	size_t m_rows;
	/** The data stored in the matrix, represented as a contiguous block of rows */
	std::unique_ptr<T[]> m_data;

	/** Calculates a flat index for the data array from a pair of (column, row) coords */
	size_t getFlatIndex(size_t column, size_t row) const {
	    return Matrix::getFlatIndex(column, row, m_cols, m_rows);
	}

	/** Calculates a flat index for a data array from a pair of (column, row) coords, given the amount of columns and rows */
	static size_t getFlatIndex(size_t column, size_t row, size_t columns, size_t rows) {
	    if(column < columns && row < rows)
		return (row * columns) + column;
	    else
		throw std::runtime_error {"Matrix Error: Index out of bounds!"};
	}

    public:
	/** Constructor, creates a matrix of shape (columns x rows) */
	Matrix(size_t columns, size_t rows) : m_cols{columns}, m_rows{rows} {
	    m_data = std::make_unique<T[]>(m_cols * m_rows);
	}
	/** Constructor, creates a matrix of shape (columns x rows) and populates it with the given value */
	Matrix(size_t columns, size_t rows, const T& value) : m_cols{columns}, m_rows{rows} {
	    m_data = std::make_unique_for_overwrite<T[]>(m_cols * m_rows);
	    /* Populating the array */
	    for(size_t idx = 0; idx < (m_cols * m_rows); ++idx) {
		m_data[idx] = value;
	    }
	}
	/** Constructor, creates a Matrix from a 2D initializer list, interpreted as a list of rows */
	Matrix(const std::initializer_list<std::initializer_list<T>>& list) : m_rows{list.size()} {
	    if(m_rows > 0) {
		/* Constructing Matrix out of initializer list if any rows provided */
		m_cols = list.begin()->size();
		/* Verify that the matrix is rectangular */
		for(auto row : list) {
		    if(row.size() != m_cols)
			throw std::runtime_error {"Matrix Error: Provided Initializer List in constructor not rectangular!"};
		}
		/* Initialize and populate Matrix data */
		m_data = std::make_unique_for_overwrite<T[]>(m_cols * m_rows);
		size_t idx = 0;
		for(auto row : list) {
		    for(auto element : row) {
			/* Runtime check to make sure data pointer not out of bounds */
			if(idx >= (m_cols * m_rows))
			    throw std::runtime_error {"Matrix Error: Invalid list initialization!"};
			m_data[idx++] = element;
		    }
		}

	    } else {
		m_cols = 0;
	    }
	}
	/** Empty constructor */
	Matrix(void) {
	    m_cols = 0;
	    m_rows = 0;
	}

	size_t getRows(void) const {
	    return m_rows;
	}

	size_t getCols(void) const {
	    return m_cols;
	}

    	/** Resizes the Matrix instance to a new width and height */
	void resize(size_t newCols, size_t newRows) {
	    /* Allocating new data block */
	    std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCols * newRows);
	    /* Copying old data to new block */
	    for(size_t row = 0; (row < m_rows && row < newRows); ++row) {
		for(size_t col = 0; (col < m_cols && col < newCols); ++col) {
		    newData[Matrix::getFlatIndex(col, row, newCols, newRows)] = m_data[getFlatIndex(col, row)];
		}
	    }
	    /* Overwriting existing data with new data */
	    m_cols = newCols;
	    m_rows = newRows;
	    m_data = std::move(newData);
	}

	/** Prints the Matrix instance in a fancy way, using the provided toString function to convert each element */
	std::string print(const std::function<std::string(T)>& toString) const {
	    std::string result;
	    for(size_t row = 0; row < m_rows; ++row) {
		result += "| ";
		for(size_t column = 0; column < m_cols; ++column) {
		    result += toString((this->at(column, row))) + "\t";
		}
		result += "|\n";
	    }
	    return result;
	}

	T& at(size_t column, size_t row) {
	    return m_data[getFlatIndex(column, row)];
	}

	const T& at(size_t column, size_t row) const {
	    return m_data[getFlatIndex(column, row)];
	}

	/* --- Operators --- */

	Matrix& operator=(const Matrix& other) {
	    /* Guard self-assignment */
	    if(this == &other) {
		return *this;
	    }

	    /* Copy rows, columns and data from other, then return self */
	    this->m_rows = other.m_rows;
	    this->m_cols = other.m_cols;
	    this->m_data = std::make_unique<T[]>(this->m_cols * this->m_rows);
	    for(size_t i = 0; i < this->m_cols * this->m_rows; ++i) {
		this->m_data[i] = other.m_data[i];
	    }
	    return *this;
	}

	friend bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
	    /* Checking equal dimensions */
	    if(!(lhs.getRows() == rhs.getRows() && lhs.getCols() == rhs.getCols()))
		return false;
	    /* Checking values */
	    for(size_t rowIdx = 0; rowIdx < lhs.getRows(); ++rowIdx) {
		for(size_t colIdx = 0; colIdx < lhs.getCols(); ++colIdx) {
		    if(lhs.at(colIdx, rowIdx) != rhs.at(colIdx, rowIdx))
			return false;
		}
	    }
	    return true;
	}

	friend bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
	    return !(lhs == rhs);
	}
};

#endif /* MATRIX_H */
