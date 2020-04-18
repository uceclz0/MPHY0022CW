/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "ccmpiMyFunctions.h"
#include <iostream>
#include <omp.h>
#include <algorithm>
namespace ccmpi {

//-----------------------------------------------------------------------------
void GetFirstAndLastIndex(const int& numberOfThreads,
                          const unsigned long int& i,
                          const double& elementsPerThread,
                          const unsigned long int& numberOfElements,
                          unsigned long int& first,
                          unsigned long int& last)
{
  first = i * elementsPerThread + 1;
  last = ((i + 1) * elementsPerThread + 1) - 1;
  if (last < first) last = first;
  if (last > numberOfElements) last = numberOfElements;
  if (i + 1 == numberOfThreads) last = numberOfElements;
}


//-----------------------------------------------------------------------------
std::vector<std::pair<unsigned long int, unsigned long int> >
GetVectorOfSeriesIndexPairs(const unsigned int& numberOfThreads,
                            const unsigned long int& numberOfElements
                           )
{

  double elementsPerThread = static_cast<double>(numberOfElements)
                           / static_cast<double>(numberOfThreads);

  std::vector<std::pair<unsigned long int, unsigned long int> > v;
  for (int i = 0; i < numberOfThreads; i++)
  {
    unsigned long int first = 0;
    unsigned long int last = 0;
    GetFirstAndLastIndex(numberOfThreads, i, elementsPerThread, numberOfElements, first, last);
    v.push_back(std::pair<unsigned long int, unsigned long int>(first, last));

    std::cout << "For " << numberOfElements << " elements, "
              << " spread over " << numberOfThreads << " processes/threads, "
              << " the i=" << i << " block "
              << " started at " << first
              << " and finished at " << last << std::endl;
  }
  return v;
}


//-----------------------------------------------------------------------------
void FillSeries(unsigned long int* const values, unsigned long int const& numberOfValues)
{
  if (!values) {
    return;
  }
  unsigned long int j = 1;
  for (int i = 0; i < numberOfValues; ++i) {
    values[i] = j++;
  }
}


//-----------------------------------------------------------------------------
unsigned long int SumSeries(const unsigned long int* const values,
                            unsigned long int const & numberOfValues)
{
  if (!values) {
    return 0;
  }
  unsigned long int sum = 0;
  for (int i = 0; i < numberOfValues; ++i) {
    sum += values[i];
  }
  return sum;
}


//-----------------------------------------------------------------------------
double EvaluateGregoryLeibnizSeries(unsigned long int startingTermNumber,
                                    unsigned long int finishingTermNumber
                                   )
{
  double a = 0;
  if (startingTermNumber > finishingTermNumber) {
    std::swap(startingTermNumber, finishingTermNumber);
  }
  bool add = startingTermNumber % 2 == 1;
  for (unsigned long i = startingTermNumber; i <= finishingTermNumber; ++i) {
    if (add) {
      a += 1.0 / (2 * i - 1);
    } else {
      a -= 1.0 / (2 * i - 1);
    }
    add = !add;
  }
  return a;
}


//-----------------------------------------------------------------------------
double EvaluatePiUsingOpenMP(unsigned long int numberOfElements)
{
  int threadnum = 0;
  int numthreads = 0;  
  std::vector<std::pair<unsigned long int, unsigned long int> > v;
  double result = 0;
  #pragma omp parallel shared(numthreads), private(threadnum)
  {
    #ifdef _OPENMP
        threadnum = omp_get_thread_num();
        #pragma omp single
        {
            numthreads = omp_get_num_threads();
        }
    #endif

    if (threadnum == 0) {
      v = GetVectorOfSeriesIndexPairs(numthreads, numberOfElements);
    }
    #pragma omp barrier
    double k = EvaluateGregoryLeibnizSeries(v[threadnum].first, v[threadnum].second);
    #pragma omp critical
    result += k;
  }
  return result * 4;
}

} // end namespace
