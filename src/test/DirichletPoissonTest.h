/*
 * author Connor Walsh
 * file   DirichletPoissonTest.h
 * brief  Class to represent a set of unit tests for DirichletPoisson class
 */

#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "../linear_algebra/matrix_solver/GaussianEliminationSolver.h"
#include "../linear_algebra/matrix_solver/QRSolver.h"
#include "../linear_algebra/MathVector.h"
#include "../linear_algebra/math_matrix/MathMatrix.h"
#include "../linear_algebra/DirichletPoisson.h"
#include "../linear_algebra/PoissonFunctions.h"

class DirichletPoissonTest : public ::testing::Test {};

double FnZero(double x, double y)
{
  return x * y * 0;
}

double FnOne(double x)
{
  return x*0 + 1.0;
}

TEST_F(DirichletPoissonTest, Generate)
{
  GaussianEliminationSolver<double> mySolver;
  DirichletPoisson<double> dirichlet(0, 0, 1.0, mySolver, 4);

  MathMatrix<double> A(9, 9);
  MathVector<double> b(9);

  dirichlet.generate<FnOne, FnOne, FnOne, FnOne, FnZero>(A, b);

//  std::cout << "A:\n" << A << "\nb:\n" << b << std::endl;

  DirichletPoisson<double> dirichlet2(0, 0, 1.0, mySolver, 3);

  MathMatrix<double> A2(4, 4);
  MathVector<double> b2(4);

  dirichlet2.generate<FnOne, FnOne, FnOne, FnOne, FnZero>(A2, b2);

//  std::cout << "A:\n" << A2 << "\nb:\n" << b2 << std::endl;
}

TEST_F(DirichletPoissonTest, Solve)
{
  GaussianEliminationSolver<double> mySolver;
  DirichletPoisson<double> dirichlet(0, 0, 1.0, mySolver);

  MathVector<double> b = dirichlet.getSolution
    <lowerBound, upperBound, leftBound, rightBound, forcingFunction>(4);

//  std::cout << "b:\n" << b << std::endl;

  QRSolver<double> qrSolver;
  DirichletPoisson<double> dirichlet2(0, 0, 1.0, qrSolver);

  MathVector<double> b2 = dirichlet2.getSolution
    <lowerBound, upperBound, leftBound, rightBound, forcingFunction>(4);

//  std::cout << "b(QR):\n" << b2 << std::endl;

  MathVector<double> actual = dirichlet.getActualSolution<Solution>(4);
//  std::cout << "actual:\n" << actual << std::endl;
}

TEST_F(DirichletPoissonTest, LargeSolve)
{
  GaussianEliminationSolver<double> mySolver;
  DirichletPoisson<double> dirichlet(0, 0, 1.0, mySolver);

  MathVector<double> b = dirichlet.getSolution
    <lowerBound, upperBound, leftBound, rightBound, forcingFunction>(25);

 // std::cout << "b:\n" << b << std::endl;

  MathVector<double> actual = dirichlet.getActualSolution<Solution>(25);
//  std::cout << "actual:\n" << actual << std::endl;
}
