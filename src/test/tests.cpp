#include "gtest/gtest.h"

#include "MathVectorTest.h"
#include "ArrayTest.h"
#include "MathMatrixTest.h"
#include "UpTriangleMathMatrixTest.h"
#include "GaussianEliminationSolverTest.h"
#include "QRSolverTest.h"
#include "DirichletPoissonTest.h"

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
