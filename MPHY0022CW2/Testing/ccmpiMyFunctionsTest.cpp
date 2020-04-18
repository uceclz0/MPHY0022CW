/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "ccmpiCatchMain.h"
#include "ccmpiMyFunctions.h"

TEST_CASE( "2. FillSeries Test", "[CW2]" ) {
    unsigned long int values[10] = {42};
    ccmpi::FillSeries(values, 5);
    unsigned long int result[10] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 10; ++i) {
      REQUIRE(values[i] == result[i]);
    }
}


TEST_CASE( "2. FillSeries Test, should leave elements unchanged after numberOfValues", "[CW2]" ) {
    unsigned long int values[10] = {42};
    ccmpi::FillSeries(values, 0);
    REQUIRE(values[0] == 42);
}

TEST_CASE( "2. FillSeries Test, should leave null array alone.", "[CW2]" ) {
    ccmpi::FillSeries(NULL, 10);
    REQUIRE(1 == 1);
}

TEST_CASE( "2. SumSeries Test", "[CW2]" ) {
  unsigned long int values[10] = {42};
  ccmpi::FillSeries(values, 5);
  unsigned long int ret = ccmpi::SumSeries(values, 5);
  REQUIRE(ret == 15);
}

TEST_CASE( "2. SumSeries Test, numberOfValues = 0", "[CW2]" ) {
  unsigned long int values[10] = {42};
  ccmpi::FillSeries(values, 5);
  unsigned long int ret = ccmpi::SumSeries(values, 0);
  REQUIRE(ret == 0);
}

TEST_CASE( "2. SumSeries Test, array = NULL", "[CW2]" ) {
  unsigned long int ret = ccmpi::SumSeries(NULL, 0);
  REQUIRE(ret == 0);
}

static int fcmp(double a, double b, double eps) { /* floating point compare, returns -1, 0, 1*/
  return (a < b - eps) - (a > b + eps);
}

TEST_CASE( "3. EvaluateGregoryLeibnizSeries Test, [1, 1], it should equal to 1", "[CW2]" ) {
  double e = ccmpi::EvaluateGregoryLeibnizSeries(1, 1);
  REQUIRE(fcmp(e, 1, 1e-6) == 0);
}

TEST_CASE( "3. EvaluateGregoryLeibnizSeries Test, for first 100 term, it should equals Pi/4 within a EPS = 1e-2", "[CW2]" ) {
  double sum1 = ccmpi::EvaluateGregoryLeibnizSeries(1, 20);
  double sum2 = ccmpi::EvaluateGregoryLeibnizSeries(21, 40);
  double sum3 = ccmpi::EvaluateGregoryLeibnizSeries(41, 60);
  double sum4 = ccmpi::EvaluateGregoryLeibnizSeries(61, 80);
  double sum5 = ccmpi::EvaluateGregoryLeibnizSeries(81, 100);
  double approx =  4 * (sum1 + sum2 + sum3 + sum4 + sum5);
  double pi = acos(-1.0); // a relative precise value
  REQUIRE(fcmp(approx, acos(-1.0), 1e-2) == 0);
}

TEST_CASE( "3. EvaluateGregoryLeibnizSeries Test, it can calculate the same value when swapped", "[CW2]" ) {
  double sum1 = ccmpi::EvaluateGregoryLeibnizSeries(20, 1);
  double sum2 = ccmpi::EvaluateGregoryLeibnizSeries(1, 20);
  REQUIRE(fcmp(sum1, sum2, 1e-12) == 0);
}

TEST_CASE( "3. EvaluateGregoryLeibnizSeries Test, it can calculate large numbers not fit in a 32-bit integer", "[CW2]" ) {
  double sum1 = ccmpi::EvaluateGregoryLeibnizSeries(10000000000uLL, 10000000002uLL);
  double sum2 = 1 / (2e10 - 1) - 1 / (2e10 + 1) + 1 / (2e10 + 3);
  REQUIRE(fcmp(sum1, sum2, 1e-12));
}
