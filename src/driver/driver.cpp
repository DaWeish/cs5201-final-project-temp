/*
 * author Connor Walsh
 * file   driver.cpp
 * brief  this file profides simple testing of the DirichletPoisson class
 *        using two different types of solvers, Gaussian and QR
 */

#include <iostream>
#include <chrono>
#include <sstream>

#include "../linear_algebra/matrix_solver/GaussianEliminationSolver.h"
#include "../linear_algebra/matrix_solver/QRSolver.h"

#include "../linear_algebra/DirichletPoisson.h"
#include "../linear_algebra/PoissonFunctions.h"

using namespace std;

int main (int argc, char** argv) {

  int startDivisions = 5;
  int endDivisions =25;
  int increment = 1;
  int fileOutput = 0;

  if (argc != 1 && argc != 4 && argc != 5)
  {
    std::cout << "Usage: driver [start  end  increment] [file friendly]"
      << std::endl;
    return 0;
  } 
  else if (argc >= 4)
  {
    istringstream ss(argv[1]);
    if (!(ss >> startDivisions) || startDivisions < 1)
    {
      std::cout << "Invalid start number!" << std::endl;
      return 0;
    }
    istringstream ss2(argv[2]);
    if (!(ss2 >> endDivisions) || endDivisions < startDivisions)
    {
      std::cout << "Invalid end number! Must be larger than start" << std::endl;
      return 0;
    }
    istringstream ss3(argv[3]);
    if (!(ss3 >> increment) || increment < 1)
    {
      std::cout << "Invalid increment number! Must be positive" << std::endl;
      return 0;
    }
  }
  if (argc == 5)
  {
    istringstream ss(argv[4]);
    if (!(ss >> fileOutput))
    {
      std::cout << "File output parameter must be a valid number (0=false)" 
        << std::endl;
    }
  }

  bool fileFriendly = (fileOutput == 0) ? false : true;

  std::streamsize prePrecision = std::cout.precision();
  cout << std::setprecision(5);
  cout << std::fixed;
  cout << std::showpoint;
  cout << std::right;

  if (!fileFriendly)
  {
    cout << "== Parameters ==\n\tStart:\t\t" << startDivisions << "\n\tEnd:\t\t"
      << endDivisions << "\n\tIncrement:\t" << increment << std::endl;
    cout << "== Testing Solvers (Gaussian|QR) ==\n";
  }

  GaussianEliminationSolver<double> gauss;
  QRSolver<double> qr;

  DirichletPoisson<double> dirichletGauss(0.0, 0.0, 1.0, gauss);
  DirichletPoisson<double> dirichletQR(0.0, 0.0, 1.0, qr);
  
  for (int i = startDivisions; i <= endDivisions; i += increment)
  {
    if (!fileFriendly)
    {
      cout << "== Solving for " << i << " divisions: ";
      cout.flush();
    }
    else
    {
      cout << i << ", ";
      cout.flush();
    }
    auto begin = std::chrono::high_resolution_clock::now();

    dirichletGauss.getSolution
    <lowerBound, upperBound, leftBound, rightBound, forcingFunction>(i);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>
      (end-begin).count();
    if (!fileFriendly)
    {
      std::cout << "\t" << elapsed / 1000000 << " ms";
    }
    else
    {
      std::cout << elapsed / 1000000 << ", ";
    }
    cout.flush();

    begin = std::chrono::high_resolution_clock::now();

    dirichletQR.getSolution
    <lowerBound, upperBound, leftBound, rightBound, forcingFunction>(i);

    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>
      (end-begin).count();
    if (!fileFriendly)
    {
      std::cout << "\t\t | " << elapsed / 1000000 << " ms" << std::endl;
    }
    else
    {
      std::cout << elapsed / 1000000 << std::endl;
    }
  }

  cout.precision(prePrecision);
  return 0;
}
