
#include <iostream>
#include <fstream>

#include "../linear_algebra/math_matrix/IMathMatrix.h"
#include "../linear_algebra/math_matrix/BaseMathMatrix.h"
#include "../linear_algebra/math_matrix/MathMatrix.h"
#include "../linear_algebra/math_matrix/TriDiagMathMatrix.h"
#include "../linear_algebra/math_matrix/DiagonalMathMatrix.h"
#include "../linear_algebra/math_matrix/UpTriangleMathMatrix.h"
#include "../linear_algebra/math_matrix/LowTriangleMathMatrix.h"

#include "../linear_algebra/QRDecompositor.h"

using namespace std;

// Functions for initializing test data
// Pre: matrix must point to a created matrix object of size 4x4
// Post: matrix now has values equal to the initialized values
void initializeTridiaonalMatrix1(IMathMatrix<double>* matrix);
void initializeTridiaonalMatrix2(IMathMatrix<double>* matrix);
void initializeDiagonalMatrix1(IMathMatrix<double>* matrix);
void initializeDiagonalMatrix2(IMathMatrix<double>* matrix);
void initializeUpTriangleMatrix1(IMathMatrix<double>* matrix);
void initializeUpTriangleMatrix2(IMathMatrix<double>* matrix);

int main (int argc, char** argv) {
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " input_file " << endl;
    return 1;
  }

  ifstream inputFile;
  int numRows = 0;

  IMathMatrix<double>* input;
  IMathMatrix<double>* matrix;
  IMathMatrix<double>* orthonormal;
  IMathMatrix<double>* triangle;

  QRDecompositor<double> QRMethod;
  int numIter = 30;

  std::streamsize prePrecision = std::cout.precision();
  cout << std::setprecision(5);
  cout << std::fixed;
  cout << std::showpoint;
  cout << std::right;

  IMathMatrix<double>* testOne;
  IMathMatrix<double>* testTwo;
  IMathMatrix<double>* result;

  cout << "== Testing TriDiagonal * Tridiagonal ==\n";
  testOne = new MathMatrix<double>(4, 4);
  testTwo = new MathMatrix<double>(4, 4);

  initializeTridiaonalMatrix1(testOne);
  initializeTridiaonalMatrix2(testTwo);

  cout << "== First Matrix ==\n" << (*testOne) << endl;
  cout << "== Second Matrix ==\n" << (*testTwo) << endl;

  cout << "== Result ==\n";
  result = (*testOne) * (*testTwo);
  cout << (*result) << endl;

  delete testOne;
  delete testTwo;
  delete result;

  cout << "== Testing Diagonal * Diagonal ==\n";
  testOne = new DiagonalMathMatrix<double>(4, 4);
  testTwo = new DiagonalMathMatrix<double>(4, 4);

  initializeDiagonalMatrix1(testOne);
  initializeDiagonalMatrix2(testTwo);

  cout << "== First Matrix ==\n" << (*testOne) << endl;
  cout << "== Second Matrix ==\n" << (*testTwo) << endl;

  cout << "== Result ==\n";
  result = (*testOne) * (*testTwo);
  cout << (*result) << endl;

  delete testOne;
  delete testTwo;
  delete result;

  cout << "== Testing Upper Triangular * Upper Triangular ==\n";
  testOne = new UpTriangleMathMatrix<double>(4, 4);
  testTwo = new UpTriangleMathMatrix<double>(4, 4);

  initializeUpTriangleMatrix1(testOne);
  initializeUpTriangleMatrix2(testTwo);

  cout << "== First Matrix ==\n" << (*testOne) << endl;
  cout << "== Second Matrix ==\n" << (*testTwo) << endl;

  cout << "== Result ==\n";
  result = (*testOne) * (*testTwo);
  cout << (*result) << endl;

  delete testOne;
  delete testTwo;
  delete result;

  inputFile.open(argv[1]);
  if (inputFile.is_open())
  {
    for (int count = 1; count <= 2; ++count)
    {
      inputFile >> numRows;
      if (numRows < 0)
      {
        cout << "Cannot work on a negative number of rows!" << endl;
        return 1;
      }

      input = new MathMatrix<double>(numRows, numRows);
      orthonormal = new MathMatrix<double>(numRows, numRows);
      triangle = new LowTriangleMathMatrix<double>(numRows, numRows);

      inputFile.ignore();
      try
      {
        inputFile >> (*input);
      }
      catch (std::domain_error de)
      {
        cout << de.what() << endl;
      }

      matrix = input->clone();
      cout << "\n=== Iteration 5 - Matrix " << count << " ===\n";
      numIter = 5;
      QRMethod(matrix, orthonormal, triangle, numIter);
      cout << (*matrix) << endl;
      delete matrix;

      matrix = input->clone();
      cout << "=== Iteration 10 - Matrix " << count << " ===\n";
      numIter = 10;
      QRMethod(matrix, orthonormal, triangle, numIter);
      cout << (*matrix) << endl;
      delete matrix;

      matrix = input->clone();
      cout << "=== Final Iteration - Matrix " << count << " ===\n";
      numIter = 35;
      QRMethod(matrix, orthonormal, triangle, numIter);
      cout << (*matrix) << endl;

      cout << "=== Reason - Matrix " << count << " ===\n";
      cout << "QR Method reached final iteration number " << numIter << endl;

      cout << "\n=== Eigenvalues - Matrix " << count << " ===\n";
      for (int i = 0; i < numRows; ++i)
      {
        cout << (*matrix)(i, i) << "  ";
      }
      cout << endl;

      delete input;
      delete matrix;
      delete orthonormal;
      delete triangle;
    }
  }
  else 
  {
    cout << "Unable to Open file, exiting..." << argv[1] << "\n";
    return 1;
  }
  
  cout << "\n=== End Assignment 6 Output ===" << endl;
  cout.precision(prePrecision);

  inputFile.close();
  return 0;
}

void initializeTridiaonalMatrix1(IMathMatrix<double>* matrix)
{
  (*matrix)(0, 0) = 2;
  (*matrix)(0, 1) = 3;
  (*matrix)(0, 2) = 0;
  (*matrix)(0, 3) = 0;
  (*matrix)(1, 0) = 5;
  (*matrix)(1, 1) = 4;
  (*matrix)(1, 2) = 5;
  (*matrix)(1, 3) = 0;
  (*matrix)(2, 0) = 0;
  (*matrix)(2, 1) = 4;
  (*matrix)(2, 2) = 3;
  (*matrix)(2, 3) = 1;
  (*matrix)(3, 0) = 0;
  (*matrix)(3, 1) = 0;
  (*matrix)(3, 2) = 5;
  (*matrix)(3, 3) = 2;
}

void initializeTridiaonalMatrix2(IMathMatrix<double>* matrix2)
{
  (*matrix2)(0, 0) = 1;
  (*matrix2)(0, 1) = 2;
  (*matrix2)(0, 2) = 0;
  (*matrix2)(0, 3) = 0;
  (*matrix2)(1, 0) = 3;
  (*matrix2)(1, 1) = 8;
  (*matrix2)(1, 2) = 4;
  (*matrix2)(1, 3) = 0;
  (*matrix2)(2, 0) = 0;
  (*matrix2)(2, 1) = 4;
  (*matrix2)(2, 2) = 2;
  (*matrix2)(2, 3) = 8;
  (*matrix2)(3, 0) = 0;
  (*matrix2)(3, 1) = 0;
  (*matrix2)(3, 2) = 9;
  (*matrix2)(3, 3) = 1;

}

void initializeDiagonalMatrix1(IMathMatrix<double>* matrix1)
{
  for (int i = 0; i < 4; ++i)
  {
    (*matrix1)(i, i) = ((i + 4) * 4) % 10;
  }
}

void initializeDiagonalMatrix2(IMathMatrix<double>* matrix2)
{
  for (int i = 0; i < 4; ++i)
  {
    (*matrix2)(i, i) = ((i + 3) * 13) % 10;
  }
}

void initializeUpTriangleMatrix1(IMathMatrix<double>* matrix)
{
  (*matrix)(0, 0) = 2;
  (*matrix)(0, 1) = 1;
  (*matrix)(0, 2) = 1;
  (*matrix)(0, 3) = 7;
  (*matrix)(1, 1) = 4;
  (*matrix)(1, 2) = 2;
  (*matrix)(1, 3) = 8;
  (*matrix)(2, 2) = 2;
  (*matrix)(2, 3) = 1;
  (*matrix)(3, 3) = 4;
}

void initializeUpTriangleMatrix2(IMathMatrix<double>* matrix)
{
  (*matrix)(0, 0) = 4;
  (*matrix)(0, 1) = 5;
  (*matrix)(0, 2) = 9;
  (*matrix)(0, 3) = 1;
  (*matrix)(1, 1) = 5;
  (*matrix)(1, 2) = 2;
  (*matrix)(1, 3) = 3;
  (*matrix)(2, 2) = 4;
  (*matrix)(2, 3) = 8;
  (*matrix)(3, 3) = 6;
}
