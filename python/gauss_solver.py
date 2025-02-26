# Gauss-Jordan Elimination Solver - contains functions to reduce a matrix to REF and RREF

# Matrix definition:
# 2D list, list of rows, where each row is a list of elements

import sys

# Checks if the given list is a valid matrix (any N by M) and returns an array of its dimensions if so
def matValid(matrix: list):
    # Check that the matrix has rows
    if len(matrix) <= 0:
        return False
    # Check that the matrix row length is consistent
    n: int = len(matrix)
    m: int = len(matrix[0])
    for row in range(1, n):
        if len(matrix[row]) != m:
            return False
    # Return dimensions if all checks passed
    return [n, m]

# Checks if the given matrix is valid and in Row Echelon Form and returns an array of its dimensions and its last 1.0 column if so
def matValidREF(matrix: list):
    # Check that matrix valid and get dimensions
    dim = matValid(matrix)
    if not dim:
        return False
    # Go through rows, check that the diagonal is 1 with leading 0s
    col = 0
    for row in matrix:
        if all(x == 0 for x in row):
            continue
        for idx in range(col):
            if row[idx] != 0.0:
                return False
        if row[col] != 1.0:
            return False
        col += 1
    # Return dimensions if all checks passed
    dim.append(col-1)
    return dim

# row1 - a*row2
def matRowSub(matrix: list, row1Idx: int, a: float, row2Idx: int):
    row1 = matrix[row1Idx]
    row2 = matrix[row2Idx]
    # Subtraction
    for i in range(len(row1)):
        row1[i] -= round(a * row2[i], 8)

# row * scalar
def matRowMul(matrix: list, rowIdx: int, scalar: float):
    row = matrix[rowIdx]
    for i in range(len(row)):
        if row[i] != 0:
            row[i] = round(row[i] * scalar, 8)

# row1 <-> row2
def matRowSwap(matrix: list, row1Idx: int, row2Idx: int):
    row1 = matrix[row1Idx]
    row2 = matrix[row2Idx]
    for i in range(len(row1)):
        tmp = row1[i]
        row1[i] = row2[i]
        row2[i] = tmp

# Prints the matrix in a pretty format
def matPrint(matrix: list):
    for row in matrix:
        for col in row:
            print(round(col, 2), end="\t")
        print("")

# Reduce to Row Echelon Form, return success status
def matREF(matrix: list):
    # Check validity of the matrix
    dim = matValid(matrix)
    if not dim:
        print("matREF Error: Matrix to reduce not valid")
        return False
    # Get matrix rows and columns
    rows: int = dim[0]
    cols: int = dim[1]
    # Initialize the first column
    col: int = 0
    # Go through the matrix row by row, until last valid column on diagonal reached
    while col < rows:
        # Initialize the row to zero by default
        n: int = 0
        # Find next row with scalar at correct point on the diagonal
        for n in range(col, len(matrix)):
            if matrix[n][col] != 0:
                break
        # Swap row into the correct position if not already correct
        if n != col:
            matRowSwap(matrix, n, col)
            n = col
        # If row non-zero, reduce the start of the row to be zero
        for x in range(col):
            if matrix[n][x] != 0:
                scale = matrix[n][x]
                matRowSub(matrix, n, scale, x)
        # Reduce row diagonal to 1
        divisor: float = matrix[n][col]
        if divisor != 0 and divisor != 1:
            matRowMul(matrix, n, 1.0/divisor)
        # Move to the next column
        col += 1
    return True

# Reduce from Row Echelon Form to Reduced Row Echelon Form, return success status
# NOTE: BUG: Make this ignore empty rows
def matRREF(matrix: list):
    # Check that the matrix is in REF
    dim = matValidREF(matrix)
    if not dim:
        print("matRREF Error: Matrix must be in REF")
        return False
    # Get the column index of the last 1.0 on the diagonal
    rows: int = dim[0]
    cols: int = dim[1]
    lastIdx: int = dim[2]
    # Go through the matrix from the bottom up and reduce trailing numbers to 0
    for idx in range(rows-1):
        rowIdx = rows - (idx + 2)
        for x in range(idx+1):
            scale = matrix[rowIdx][lastIdx - x]
            if scale != 0.0:
                matRowSub(matrix, rowIdx, scale, rows - 1 - x)
    # Return true once reduced
    return True

# Returns a list of string expressions for each variable, considering a matrix in RREF to represent a system of linear equations
def getVars(matrix: list):
    # Go through matrix from the bottom up, get expression for each variable
    result = []
    for row in reversed(matrix):
        if all(x == 0 for x in row):
            continue
        oneIdx = next(x for x in range(len(row)) if row[x] == 1.0)
        expr = "X_" + str(oneIdx+1) + " = " + str(round(row[-1], 2))
        for idx in range(oneIdx+1, len(row)-1, 1):
            if row[idx] != 0:
                expr += ("+" if row[idx] < 0 else "") + str(round(-1*row[idx], 2)) + "*X_" + str(idx+1)
        result.insert(0, expr)
    # Add free variables if any exist
    for i in range(len(matrix[0])-1):
        if len(result) <= i:
            result.append("X_" + str(i+1))
    # Return the resulting strings
    return result

# Allow user to input matrix if called as main
if __name__ == "__main__":
    # Greeting text
    print("=== Gauss-Jordan Elimination Matrix Solver ===")
    print("INFO: To enter matrix, separate numbers using spaces, use enter to insert next line, press CTRL+D on blank line to end matrix input")
    print("Enter matrix:")
    # Matrix input
    matrix = []
    for line in sys.stdin:
        num = line.strip().split(" ")
        matrix.append([float(n) for n in num])
    # Validate matrix
    if not matValid(matrix):
        print("Error: Matrix invalid\nEntered matrix:")
        matPrint(matrix)
        exit(1)
    # Solve and print REF and RREF
    print("-> Row Echelon Form (REF):")
    if matREF(matrix):
        matPrint(matrix)
    print("-> Reduced Row Echelon Form (RREF):")
    if matRREF(matrix):
        matPrint(matrix)
    print("-> Linear system solution:")
    print(getVars(matrix))
    exit(0)
