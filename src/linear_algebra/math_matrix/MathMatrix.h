/*
 * author Connor Walsh
 * file   MathMatrix.h
 * brief  Standard Math Matrix following the IMathMatrix interface
 */

#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#pragma once

#include <stddef.h>
#include <iostream>

#include "../../containers/Array.h"
#include "../MathVector.h"
#include "BaseMathMatrix.h"
#include "IMathMatrix.h"

/*
 * class  MathMatrix
 * brief  This class represents a matrix. This class implements the IMathMatrix
 *        interface and also includes operators for working with other
 *        matrices that derive from IMathMatrix. It also includes the
 *        transpose function
 */
template <class T>
class MathMatrix : public BaseMathMatrix<T, MathMatrix>
{
  public:
    /*
     * brief  Creates a MathMatrix with default parameters
     * post   Created matrix represents an empty matrix
     */
    MathMatrix() : myColumns(0) {}

    /*
     * brief  This constructor is used to create a matrix of a given size input
     * pre    rows must be a positive value greater than zero
     *        cols must be a positive value greater than zero
     * post   creates a MathMatrix of size [rows, cols]
     */
    explicit MathMatrix(size_t rows, size_t cols = 1);

    /*
     * brief  Copy constructor
     * post   Creates a matrix that is a copy of other
     */
    MathMatrix(const MathMatrix& other);

    /*
     * brief  Move Constructor
     * pre    Other must be a matrix whose values can be moved
     * post   This contains the data from other and other is set to be a
     *        default MathMatrix
     */ 
    MathMatrix(MathMatrix&& other);

    /*
     * brief  Destructor
     * post   All member data is cleared and object ready to be deleted
     */
    ~MathMatrix();

    /*
     * brief  Assigns the values of rhs to this
     * post   This now contains copies of the values in rhs
     */
    MathMatrix<T>& operator=(MathMatrix rhs);

    using IMathMatrix<T>::operator==;
    using IMathMatrix<T>::operator!=;

    /*
     * brief  Implements the equality operator for the IMathMatrix interface
     * pre    T must have the equality operation defined
     * post   Returns true if this matrix has the same values as rhs otherwise
     *        returns false
     */
    bool opEquality(const IMathMatrix<T>& rhs) const;

    /*
     * brief  Equality operator for two LowTriangleMathMatrices
     * pre    T must have the equality operator defined
     * post   Returns true if this matrix has the same representation
     *        as rhs, false otherwise
     */
    bool operator==(const MathMatrix& rhs) const;

    /*
     * brief  Inequality operator for two LowTrianleMathMatrices
     * pre    T must have the equality operator defined
     * post   Returns false if this matrix has the same representation
     *        as rhs, true otherwise
     */
    bool operator!=(const MathMatrix& rhs) const;

    /*
     * brief  Implementation method for the += operator in IMathMatrix
     * pre    T must have the += operation defined and IMathMatrix
     *        must be the same size as this or exception is thrown
     * post   This is equal to the previous values plus rhs values
     */
    MathMatrix& opPlusEquals(const IMathMatrix<T>& rhs);

    /*
     * brief  Implementation method for the -= operator in IMathMatrix
     * pre    T must have the += operation defined and IMathMatrix
     *        must be the same size as this or exception is thrown
     * post   This is equal to the previous values minus rhs values
     */
    MathMatrix& opMinusEquals(const IMathMatrix<T>& rhs);

    /*
     * brief  Implementation method for the *= operator in IMathMatrix
     * pre    T must have the *= operation defined and IMathMatrix
     *        must have the correct dimensions else exception is thrown
     * post   This is equal to the previous values times rhs values
     */
    MathMatrix& opTimesEquals(const IMathMatrix<T>& rhs);

    /*
     * brief  Implementation method for the *= operator in ImathMatrix
     * pre    T must have the *= operation defined
     * post   This is equal to the previous values times scaler
     */
    MathMatrix& opTimesEquals(const T& scaler);

    /*
     * brief  Operator for adding this matrix to another similar matrix
     * pre    T must have the + operator defined
     * post   Returns a new MathMatrix equal to this + rhs
     */
    MathMatrix operator+(const IMathMatrix<T>& rhs) const;

    /*
     * brief  Operator for subtracting rhs from this matrix
     * pre    T must have thte - operator defined
     * post   Returns a new MathMatrix equal to this - rhs
     */
    MathMatrix operator-(const IMathMatrix<T>& rhs) const;

    /*
     * brief  Operator for returning the negative of this matrix
     * post   Returns a new matrix equal to -(*this);
     */
    MathMatrix operator-() const;

    /*
     * brief  Operator for returning the multiplication of two matrices
     * pre    T must have the multiplication and addition operator defined
     *        and must be of correct dimensions else exception is thrown
     * post   Returns a new matrix of correct type equal to the multiplication
     *        of this by rhs
     */
    MathMatrix operator*(const IMathMatrix<T>& rhs) const;

    /*
     * brief  Operator for multiplying this matrix by a scaler
     * pre    T must implement the multiplication operator
     * post   Returns a new matrix equal to this scaled by scaler
     */
    MathMatrix operator*(const T& scaler) const;

    /*
     * brief  Operator for getting the product of this and a vector
     * pre    T must have the multiplication operator defined and rhs
     *        must have size equal to columns else exception is thrown
     * post   Returns a new MathVector equal to this * rhs
     */
    MathVector<T> operator*(const MathVector<T>& rhs) const;

    /*
     * brief  Operator for returning the row vector from this matrix
     * pre    index must be a valid row index else exception is thrown
     * post   returns a reference to the row vector specified by index
     */
    MathVector<T>& operator[](size_t index);
    const MathVector<T>& operator[](size_t index) const;

    /*
     * brief  Operator for getting the transpose of this matrix
     * pre    This matrix must have a size equal to or greater than 1
     * post   Returns a new UpTriangleMathMatrix representhing this' transpose
     */
    MathMatrix transpose() const;

    /*
     * brief  Function to swap two rows of this matrix
     * pre    row1 and row2 must specify valid rows of the matrix
     * post   this now has rows1 and row2 swapped
     */
    MathMatrix swapRows(size_t row1, size_t row2);

    /*
     * brief  Operators for returning an element in the matrix
     * pre    row and column must specify valid coordinates else exception
     *        is thrown
     * post   returns a reference to the element specified
     */
    T& at(size_t row, size_t column);
    const T& at(size_t row, size_t column) const;

    /*
     * brief  Method for getting the number of rows/cols in this matrix
     * post   Returns a size_t holding the number of rows/cols in this matrix
     */
    size_t getRows() const;
    size_t getCols() const;

    /*
     * brief  Function to swap the values of this Matrix with another
     * post   This now has the values of other and vice versa
     */
    void swap(MathMatrix& other);

    /*
     * brief  This function places a represntation of this matrix on the 
     *        given stream
     * pre    T must have the << operator defined
     * post   os contains a represntation of this matrix on it
     */
    void printToStream(std::ostream& os) const;

    /*
     * brief  This function is included in the IMathMatrix interface
     * post   Throws exception because it currently does not make sense
     *        to read a Triangular matrix from a stream
     */
    void readFromStream(std::istream& is);

  private:
    Array<MathVector<T>*> myRows;
    size_t myColumns;
};

/*
 * brief  Operator for commutative scaler multiplication
 * pre    T must implement the multiplication operator
 * post   Returns a new matrix equal to this scaled by scaler
 */
template <class T>
MathMatrix<T> operator*(const T& scaler, MathMatrix<T> matrix)
{
  return matrix *= scaler;
}

#include "MathMatrix.hpp"

#endif
