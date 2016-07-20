# The N-body simulation
The N-body simulation is a simulation of hundreds or thousands of particles under the influence of physical forces.

## Usage
Sequential and parallel implementations of the N-body simulation are available. Both of them allows for interaction with stable system of _n_ particles under influence of central, repulsion and damping forces.

### Sequential
Sequential implementation of the N-body simulation accepts as an input the following parameters:

1. Input file - path to the input file with the X and Y coordinates of the cursor in each frame;
1. Number of particles - how many particles will take a part in the simulation;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Parallel
Parallel implementation of the N-body simulation accepts as an input the following parameters:

1. Input file - path to the input file with the X and Y coordinates of the cursor in each frame;
1. Number of particles - how many particles will take a part in the simulation;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - how many times the test should be repeated for performance measurements.

## Examples
### Sequential
Example input and output of the sequential implementation which uses 500 particles and 2 iterations:

    n_body_sequential sample_input.txt 500 2
    Mila version: 0.3.0
    Initial results
    Frames per second: 59.157722
    Duration [us]: 21975152.000000
    Input file: sample_input.txt
    Number of particles: 500
    Iterations
    Iteration: 0, Frames per second: 59.092590, Duration [us]: 21999374.000000
    Iteration: 1, Frames per second: 59.178673, Duration [us]: 21967372.000000
    Statistics
    Mean: 21983372.000000
    Median: 21983372.000000
    Variance: 512064000.000000
    Standard Deviation: 22628.832031
    Coefficient of Variation: 0.001029

### Parallel
Example input and output of the parallel implementation which uses 500 particles on OpenCL platform 0, device 0 and with 2 iterations:

    n_body_parallel sample_input.txt 500 0 0 2
    Mila version: 0.3.0
    Initial results
    Frames per second: 58.904392
    Duration [us]: 22069662.000000
    Platform: NVIDIA CUDA
    Device: GeForce GTX 960
    Input file: sample_input.txt
    Number of particles: 500
    Iterations
    Iteration: 0
    Host statistics:
    Duration: 22000428.000000 us, Frames per second: 59.089760, Bandwidth: 67.561798 GB/s
    OpenCL statistics:
    Build kernel: 85 us, Read buffer: 10 us, Enqueue ND range: 178 us
    Iteration: 1
    Host statistics:
    Duration: 21972836.000000 us, Frames per second: 59.163963, Bandwidth: 75.162498 GB/s
    OpenCL statistics:
    Build kernel: 84 us, Read buffer: 10 us, Enqueue ND range: 160 us
    Statistics
    Mean: 21986632.000000
    Median: 21986632.000000
    Variance: 380659232.000000
    Standard Deviation: 19510.490234
    Coefficient of Variation: 0.000887

## References
1. https://vimeo.com/7298380
1. http://http.developer.nvidia.com/GPUGems3/gpugems3_ch31.html
