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
    Initial results
    Duration [us]: 21952178
    Input file: sample_input.txt
    Number of particles: 500
    Iterations
    Iteration: 0, Duration [us]: 21725207
    Iteration: 1, Duration [us]: 21718238
    Statistics
    Mean: 21721723.000000
    Median: 21721724.000000
    Variance: 24290452.000000
    Standard Deviation: 4928.534468
    Coefficient of Variation: 0.000227

### Parallel
Example input and output of the parallel implementation which uses 500 particles on OpenCL platform 0, device 0 and with 2 iterations:

    n_body_parallel sample_input.txt 500 0 0 2
    Initial results
    Duration [us]: 23336967
    Platform: NVIDIA CUDA
    Device: GeForce GTX 960
    Input file: sample_input.txt
    Number of particles: 500
    Iterations
    Iteration: 0, Duration [us]: 21875894
    Iteration: 1, Duration [us]: 21864887
    Statistics
    Mean: 21870391.000000
    Median: 21870392.000000
    Variance: 60566020.000000
    Standard Deviation: 7782.417362
    Coefficient of Variation: 0.000356

## References
1. https://vimeo.com/7298380
1. http://http.developer.nvidia.com/GPUGems3/gpugems3_ch31.html
