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
#include <omp.h>

static int fcmp(double a, double b, double eps) { /* floating point compare, returns -1, 0, 1*/
  return (a < b - eps) - (a > b + eps);
}

TEST_CASE( "4. OpenMP Pi Test", "[CW2]" ) {
  omp_set_num_threads(4);
  double result = ccmpi::EvaluatePiUsingOpenMP(100);
  double pi = acos(-1.0);
  REQUIRE(fcmp(result, pi, 1e-2) == 0);
}

TEST_CASE( "4. OpenMP Pi Test, can't get the right answer when threads > the total numberOfElements", "[CW2]" ) {
  omp_set_num_threads(104);
  double result = ccmpi::EvaluatePiUsingOpenMP(100);
  double pi = acos(-1.0);
  REQUIRE(fcmp(result, pi, 1e-2) != 0);
}
