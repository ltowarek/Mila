# The N-body simulation
The N-body simulation is a simulation of hundreds or thousands of particles under the influence of physical forces.

## Usage
Sequential and parallel implementations of the N-body simulation are available. Both of them allows for simulation of stable system of _n_ particles under influence of central, repulsion and damping forces. In addition, it is possible to display the system, record interaction with it and replay all movements for performance measurements.

### Sequential
Sequential implementation of the N-body simulation accepts as an input the following parameters:
1. Number of particles - how many particles will take a part in the simulation;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Parallel
Parallel implementation of the N-body simulation accepts as an input the following parameters:

1. Number of particles - how many particles will take a part in the simulation;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Sequential interactive view
Sequential interactive view accepts as an input the following parameters:

#### Recording
1. Number of particles - how many particles will take a part in the simulation;
1. Mouse's positions file - path to the file where the X and Y coordinates of the cursor in each frame will be saved;
1. Output file - path to the file where system's state from last frame will be saved;
1. Number of iterations - this value should be set to 0 as recording does not measure performance.

#### Replaying
1. Number of particles - how many particles will take a part in the simulation;
1. Mouse's positions file - path to the file with the X and Y coordinates of the cursor in each frame;
1. Reference file - path to the file with system's state from last frame;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Parallel interactive view
Parallel interactive view accepts as an input the following parameters:

#### Recording
1. Number of particles - how many particles will take a part in the simulation;
1. Mouse's positions file - path to the file where the X and Y coordinates of the cursor in each frame will be saved;
1. Output file - path to the file where system's state from last frame will be saved;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - this value should be set to 0 as recording does not measure performance.

#### Replaying
1. Number of particles - how many particles will take a part in the simulation;
1. Mouse's positions file - path to the file with the X and Y coordinates of the cursor in each frame;
1. Reference file - path to the file with system's state from last frame;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - how many times the test should be repeated for performance measurements.

## Examples
### Sequential
Example input and output of the sequential implementation which uses 500 particles and 2 iterations:

    mila n_body_sequential 500 2
    INFO     Version: 0.4.0
    INFO     Number of particles: 500
    INFO     Number of iterations: 2
    INFO     Throughput mean: 103571.734375 particles/s
    INFO     Throughput median: 103571.734375 particles/s
    INFO     Throughput standard deviation: 2926.720459 particles/s
    INFO     Throughput coefficient of variation: 0.028258
    INFO     Update particles duration mean: 4829.500000 us
    INFO     Update particles duration median: 4829.500000 us
    INFO     Update particles duration standard deviation: 136.471603 us
    INFO     Update particles duration coefficient of variation: 0.028258

### Parallel
Example input and output of the parallel implementation which uses 500 particles on OpenCL platform 0, device 0 and 2 iterations:

    mila n_body_parallel 500 0 0 2
    INFO     Version: 0.4.0
    INFO     Number of particles: 500
    INFO     Number of iterations: 2
    INFO     Platform id: 0
    INFO     Device id: 0
    INFO     Platform name: NVIDIA CUDA
    INFO     Device name: GeForce GTX 960
    INFO     Bandwidth mean: 7.869942 GB/s
    INFO     Bandwidth median: 7.869942 GB/s
    INFO     Bandwidth standard deviation: 0.079861 GB/s
    INFO     Bandwidth coefficient of variation: 0.010148
    INFO     Throughput mean: 652349.312500 particles/s
    INFO     Throughput median: 652349.312500 particles/s
    INFO     Throughput standard deviation: 5405.081055 particles/s
    INFO     Throughput coefficient of variation: 0.008286
    INFO     Initialize duration mean: 234.000000 us
    INFO     Initialize duration median: 234.000000 us
    INFO     Initialize duration standard deviation: 1.414214 us
    INFO     Initialize duration coefficient of variation: 0.006044
    INFO     Update particles duration mean: 766.500000 us
    INFO     Update particles duration median: 766.500000 us
    INFO     Update particles duration standard deviation: 7.778174 us
    INFO     Update particles duration coefficient of variation: 0.010148
    INFO     Read buffer duration mean: 10.000000 us
    INFO     Read buffer duration median: 10.000000 us
    INFO     Read buffer duration standard deviation: 0.000000 us
    INFO     Read buffer duration coefficient of variation: 0.000000
    INFO     Enqueue ND range duration mean: 169.000000 us
    INFO     Enqueue ND range duration median: 169.000000 us
    INFO     Enqueue ND range duration standard deviation: 0.000000 us
    INFO     Enqueue ND range duration coefficient of variation: 0.000000

### Sequential interactive view - recording
Example input and output of recording sequential interactive view which uses 500 particles:

    mila n_body_sequential_interactive_view record 500 mouse.txt output.txt 0
    INFO     Version: 0.4.0
    INFO     Mouse positions file: mouse.txt
    INFO     Particles file: output.txt
    INFO     Number of iterations: 0
    
### Sequential interactive view - replaying
Example input and output of replaying sequential interactive view which uses 500 particles and 2 iterations:

    mila n_body_sequential_interactive_view replay 500 mouse.txt output.txt 2
    INFO     Version: 0.4.0
    INFO     Mouse positions file: mouse.txt
    INFO     Particles file: output.txt
    INFO     Number of iterations: 2
    INFO     Output is equal to reference
    INFO     Output is equal to reference
    INFO     Output is equal to reference
    INFO     Throughput mean: 324.892700 frames/s
    INFO     Throughput median: 324.892700 frames/s
    INFO     Throughput standard deviation: 1.883388 frames/s
    INFO     Throughput coefficient of variation: 0.005797
    INFO     Replay duration mean: 5792779.000000 us
    INFO     Replay duration median: 5792779.000000 us
    INFO     Replay duration standard deviation: 33580.500000 us
    INFO     Replay duration coefficient of variation: 0.005797

### Parallel interactive view - recording
Example input and output of recording parallel interactive view which uses 500 particles on OpenCL platform 0, device 0:

    mila n_body_parallel_interactive_view record 500 mouse.txt output.txt 0 0 0
    INFO     Version: 0.4.0
    INFO     Mouse positions file: mouse.txt
    INFO     Particles file: output.txt
    INFO     Number of iterations: 0
    INFO     Platform id: 0
    INFO     Device id: 0
    INFO     Platform name: NVIDIA CUDA
    INFO     Device name: GeForce GTX 960

### Parallel interactive view - replaying
Example input and output of replaying parallel interactive view which uses 500 particles on OpenCL platform 0, device 0 and 2 iterations:

    mila n_body_parallel_interactive_view replay 500 mouse.txt output.txt 0 0 2
    INFO     Version: 0.4.0
    INFO     Mouse positions file: mouse.txt
    INFO     Particles file: output.txt
    INFO     Number of iterations: 2
    INFO     Platform id: 0
    INFO     Device id: 0
    INFO     Platform name: NVIDIA CUDA
    INFO     Device name: GeForce GTX 960
    INFO     Output is equal to reference
    INFO     Output is equal to reference
    INFO     Output is equal to reference
    INFO     Throughput mean: 997.765137 frames/s
    INFO     Throughput median: 997.765137 frames/s
    INFO     Throughput standard deviation: 0.128310 frames/s
    INFO     Throughput coefficient of variation: 0.000129
    INFO     Replay duration mean: 1886215.500000 us
    INFO     Replay duration median: 1886215.500000 us
    INFO     Replay duration standard deviation: 242.537628 us
    INFO     Replay duration coefficient of variation: 0.000129
    
## References
1. https://vimeo.com/7298380
1. http://http.developer.nvidia.com/GPUGems3/gpugems3_ch31.html
