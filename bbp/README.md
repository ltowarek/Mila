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

    bbp_sequential 100 500 2
    Initial results
    Duration [us]: 107241
    Number of Digits: 100
    Starting Position: 500
    PI in hex: 86AF7C72E993B3EE1411636FBC2A2BA9C55D741822F6CE5C3E169514B01EA082D7420C4F4CEC7A2242A6912284AB255EF85C
    Iterations
    Iteration: 0, Duration [us]: 88984
    Iteration: 1, Duration [us]: 94996
    Statistics
    Mean: 91990.000000
    Median: 91990.000000
    Variance: 18072072.000000
    Standard Deviation: 4251.125968
    Coefficient of Variation: 0.046213

### Parallel
Example input and output of the parallel implementation which computes 100 digits of pi starting from 500-th digit on OpenCL platform 0, device 0 and with 2 iterations:

    bbp_parallel 100 500 0 0 2
    Initial results
    Duration [us]: 760707
    Platform: NVIDIA CUDA
    Device: GeForce GTX 960
    Number of Digits: 100
    Starting Position: 500
    PI in hex: 86AF7C72E993B3EE1411636FBC2A2BA9C55D741822F6CE5C3E169514B01EA082D7420C4F4CEC7A2242A6912284AB255EF85C
    Iterations
    Iteration: 0, Duration [us]: 92535
    Iteration: 1, Duration [us]: 83312
    Statistics
    Mean: 87923.500000
    Median: 87923.500000
    Variance: 42531864.000000
    Standard Deviation: 6521.645805
    Coefficient of Variation: 0.074174

## References
1. http://www.davidhbailey.com/dhbpapers/bbp-alg.pdf
1. http://www.experimentalmath.info/bbp-codes/piqpr8.c
