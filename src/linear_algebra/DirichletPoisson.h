/*
 * author Connor Walsh
 * file   DirichletPoisson.h
 * brief  This class uses the Dirichlet method to approximate points in the 
 *        chosen domain for the Poisson equation
 */

#ifndef DIRICHLET_POISSON_H
#define DIRICHLET_POISSON_H

#pragma once

#include "math_matrix/IMathMatrix.h"
#include "matrix_solver/IMatrixSolver.h"
#include "MathVector.h"

/*
 * class DirichletPoisson
 * brief  This class is used to generate and solve the Poisson equation 
 *        given the boundary conditions, area, number of divisions to make,
 *        and a IMatrixSolver to use
 */
template <class T>
class DirichletPoisson
{
  private:
    T xLow, yLow, length;
    int numDivs;
    IMatrixSolver<T>& mySolver;

    /*
     * brief  Function to get the index in a vector of the point in h coordinates
     * pre    x and y are positive
     * post   returns the index of the point given by input coordinates
     */
    int getPointOffset(int x, int y) const;
  
  public:
    /*
     * brief  This constructor takes the lower left point along with a solver
     *        to use for solving for the points and a default number of divisions
     * post   Creates a DirichletPoisson problem that is ready to solve
     */
    DirichletPoisson(T lowX, T lowY, T plength, IMatrixSolver<T>& solver,
        int numDivisions = 2) : xLow(lowX), yLow(lowY), length(plength), 
        numDivs(numDivisions), mySolver(solver) {};

    /*
     * brief  This function generates the A matrix and b vector in the equation
     *        Ax = b for the current problem with the current number of divisions
     * pre    A and b are of appropriate sizes for the current divisions
     *        i.e dimension length is equal to (#divisions - 1)^2
     * post   A is now equal to the coefficients for solving the poisson equation
     *        and b holds the constants for the given template parameters
     */
    template <T fnLow(T), T fnHigh(T), T fnLeft(T), T fnRight(T), T fnForce(T, T)>
    void generate(IMathMatrix<T>& A, MathVector<T>& b) const;

    /*
     * brief  This function calculates the solution for a Dirichlet Poisson problem
     * pre    numDivs must be greater than 1
     * post   returns a vector containing the inner points approximated by the
     *        Dirichlet process
     */
    template <T fnLow(T), T fnHigh(T), T fnLeft(T), T fnRight(T), T fnForce(T, T)>
    MathVector<T> getSolution(int numDivs);

    /*
     * brief  Function for determing the correct answer points for the Poisson
     *        equation given the known solution function
     * pre    solution is defined for the domain of the Dirichlet problem
     * post   Outputs a vector with the inner points correct values to
     *        be compared to theose given by getSolution
     */
    template <T solution(T, T)>
    MathVector<T> getActualSolution(int numDivs);
};

#include "DirichletPoisson.hpp"

#endif
