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

template <class T>
class DirichletPoisson
{
  private:
    T xLow, yLow, length;
    int numDivs;
    IMatrixSolver<T>& mySolver;

    int getPointOffset(int x, int y) const;
  
  public:
    DirichletPoisson(T lowX, T lowY, T plength, IMatrixSolver<T>& solver,
        int numDivisions = 2) : xLow(lowX), yLow(lowY), length(plength), 
        numDivs(numDivisions), mySolver(solver) {};

    template <T fnLow(T), T fnHigh(T), T fnLeft(T), T fnRight(T), T fnForce(T, T)>
    void generate(IMathMatrix<T>& A, MathVector<T>& b) const;

    template <T fnLow(T), T fnHigh(T), T fnLeft(T), T fnRight(T), T fnForce(T, T)>
    MathVector<T> getSolution(int numDivs);

    template <T solution(T, T)>
    MathVector<T> getActualSolution(int numDivs);
};

#include "DirichletPoisson.hpp"

#endif
