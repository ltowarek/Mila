# The BBP Algorithm for Pi
The Bailey–Borwein–Plouffe formula is an algorithm for computing the _n_-th digit of pi without calculating all of the preceding digits.

## Usage
Sequential and parallel implementations of the BBP formula are available. Both of them allows for computation of _n_ digits of pi starting from _p_ position. Computed digits are returned in hexadecimal numbers.

### Sequential
Sequential implementation of the BBP formula accepts as an input the following parameters:

1. Number of digits - how many digits of pi should be computed;
1. Starting position - where computation should be started;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Parallel
Parallel implementation of the BBP formula accepts as an input the following parameters:

1. Number of digits - how many digits of pi should be computed;
1. Starting position - where computation should be started;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - how many times the test should be repeated for performance measurements.

## Examples
### Sequential
Example input and output of the sequential implementation which computes 100 digits of pi starting from 500-th digit with 2 iterations:

    mila bbp_sequential 100 500 2
    INFO     Version: 0.4.0
    INFO     Number of digits: 100
    INFO     Starting position: 500
    INFO     Number of iterations: 2
    INFO     Digits: 86AF7C72E993B3EE1411636FBC2A2BA9C55D741822F6CE5C3E169514B01EA082D7420C4F4CEC7A2242A6912284AB255EF85C
    INFO     Throughput mean: 1428.863037 digits/s
    INFO     Throughput median: 1428.863037 digits/s
    INFO     Throughput standard deviation: 29.372379 digits/s
    INFO     Throughput coefficient of variation: 0.020556
    INFO     Compute digits duration mean: 70000.500000 us
    INFO     Compute digits duration median: 70000.500000 us
    INFO     Compute digits duration standard deviation: 1438.962280 us
    INFO     Compute digits duration coefficient of variation: 0.020556

### Parallel
Example input and output of the parallel implementation which computes 100 digits of pi starting from 500-th digit on OpenCL platform 0, device 0 and with 2 iterations:

    mila bbp_parallel 100 500 0 0 2
    INFO     Version: 0.4.0
    INFO     Number of digits: 100
    INFO     Starting position: 500
    INFO     Number of iterations: 2
    INFO     Platform id: 0
    INFO     Device id: 0
    INFO     Platform name: NVIDIA CUDA
    INFO     Device name: GeForce GTX 960
    INFO     Digits: 86AF7C72E993B3EE1411636FBC2A2BA9C55D741822F6CE5C3E169514B01EA082D7420C4F4CEC7A2242A6912284AB255EF85C
    INFO     Bandwidth mean: 0.000060 GB/s
    INFO     Bandwidth median: 0.000060 GB/s
    INFO     Bandwidth standard deviation: 0.000000 GB/s
    INFO     Bandwidth coefficient of variation: 0.000106
    INFO     Throughput mean: 15002.625000 digits/s
    INFO     Throughput median: 15002.625000 digits/s
    INFO     Throughput standard deviation: 1.590990 digits/s
    INFO     Throughput coefficient of variation: 0.000106
    INFO     Initialize duration mean: 474.000000 us
    INFO     Initialize duration median: 474.000000 us
    INFO     Initialize duration standard deviation: 9.899495 us
    INFO     Initialize duration coefficient of variation: 0.020885
    INFO     Compute digits duration mean: 6665.500000 us
    INFO     Compute digits duration median: 6665.500000 us
    INFO     Compute digits duration standard deviation: 0.707107 us
    INFO     Compute digits duration coefficient of variation: 0.000106
    INFO     Enqueue ND range duration mean: 6321.000000 us
    INFO     Enqueue ND range duration median: 6321.000000 us
    INFO     Enqueue ND range duration standard deviation: 0.000000 us
    INFO     Enqueue ND range duration coefficient of variation: 0.000000
    INFO     Read buffer duration mean: 3.000000 us
    INFO     Read buffer duration median: 3.000000 us
    INFO     Read buffer duration standard deviation: 0.000000 us
    INFO     Read buffer duration coefficient of variation: 0.000000

## References
1. http://www.davidhbailey.com/dhbpapers/bbp-alg.pdf
1. http://www.experimentalmath.info/bbp-codes/piqpr8.c
