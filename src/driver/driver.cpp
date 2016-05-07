/*
 * author Connor Walsh
 * file   driver.cpp
 * brief  this file profides simple testing of the DirichletPoisson class
 *        using two different types of solvers, Gaussian and QR
 */

#include <iostream>
#include <chrono>

#include "../linear_algebra/matrix_solver/GaussianEliminationSolver.h"

#include "../linear_algebra/DirichletPoisson.h"
#include "../linear_algebra/PoissonFunctions.h"

using namespace std;

int main () {
  std::streamsize prePrecision = std::cout.precision();
  cout << std::setprecision(5);
  cout << std::fixed;
  cout << std::showpoint;
  cout << std::right;

  cout << "== Testing Gaussian Elimination Solver ==\n";

  GaussianEliminationSolver<double> gauss;
  DirichletPoisson<double> dirichletGauss(0.0, 0.0, 1.0, gauss);
  
  for (int i = 5; i <= 35; ++i)
  {
    cout << "== Solving for " << i << " divisions of the plane: ";
    cout.flush();
    auto begin = std::chrono::high_resolution_clock::now();

    dirichletGauss.getSolution
    <lowerBound, upperBound, leftBound, rightBound, forcingFunction>(i);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>
      (end-begin).count();
    std::cout << "\t" << elapsed / 1000000 << " ms" << std::endl;
  }

  cout.precision(prePrecision);
  return 0;
}
