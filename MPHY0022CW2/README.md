CMakeCatchMPI
------------------

[![Build Status](https://travis-ci.org/MattClarkson/CMakeCatchMPI.svg?branch=master)](https://travis-ci.org/MattClarkson/CMakeCatchMPI)
[![Build Status](https://ci.appveyor.com/api/projects/status/5pm89ej732c1ekf0/branch/master)](https://ci.appveyor.com/project/MattClarkson/cmakecatchmpi)


Purpose
-------

This is a demo project to demonstrate a reasonable structure for [CMake](https://cmake.org/) based projects,
that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2),
specifically demonstrating some uses of MPI.


Credits
-------

This project was developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).


Prepare
-------
If mpi is not installed, in a debian-like system, type:
```
api install -y libopenmpi-dev mpi
```


Build
------
```
mkdir build
cd build
cmake ..
make
```

Testing
--------
To run each non-MPI tests, for individual tests, in directory `build` type:
```
./bin/ccmpiMyFunctionsTest
./bin/ccmpiPiSeriesOMPTest
```

To run MPI tests, use `mpiexec`
```
mpiexec -n 5 ccmpiPiSeriesMPITest
mpiexec -n 5 ccmpiTriangleNumberSeriesMPITest
```

If root must be used, `mpiexec` needs `--allow-run-as-root` as:
```
mpiexec --allow-run-as-root -n 5 ccmpiPiSeriesMPITest
mpiexec --allow-run-as-root -n 5 ccmpiTriangleNumberSeriesMPITest
```

