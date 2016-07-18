# The mean shift algorithm
The mean shift is an algorithm for locating the maxima of a density function, which is often used for clustering and image processing.

## Usage
Sequential and parallel implementations of the mean shift algorithm are available. Both of them allows image segmentation based on pixels values which results in the pastel effect.

### Sequential
Sequential implementation of the mean shift algorithm accepts as an input the following parameters:

1. Input file - path to the input file in PNG format;
1. Output file - path where the output file in PNG format will be saved;
1. Bandwidth - mean shift bandwidth;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Parallel
Parallel implementation of the mean shift algorithm accepts as an input the following parameters:

1. Input file - path to the input file in PNG format;
1. Output file - path where the output file in PNG format will be saved;
1. Bandwidth - mean shift bandwidth;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - how many times the test should be repeated for performance measurements.

## Examples
### Sequential
Example input and output of the sequential implementation which uses mean shift with 25.0 bandwidth and 2 iterations:

    mean_shift_sequential test_image.png test_image_output.png 25.0 2
    Mila version: 0.3.0
    Initial results
    Pixels per second: 163.291626
    Duration [us]: 1837203.000000
    Input file: test_image.png
    Output file: test_image_output.png
    Bandwidth: 25.000000
    Iterations
    Iteration: 0, Pixels per second: 165.736603, Duration [us]: 1810101.000000
    Iteration: 1, Pixels per second: 165.032837, Duration [us]: 1817820.000000
    Statistics
    Mean: 1813960.500000
    Median: 1813960.500000
    Variance: 29791480.000000
    Standard Deviation: 5458.157227
    Coefficient of Variation: 0.003009

### Parallel
Example input and output of the parallel implementation which uses mean shift with 25.0 bandwidth on OpenCL platform 0, device 0 and with 2 iterations:

    mean_shift_parallel test_image.png test_image_output.png 25.0 0 0 2
    Mila version: 0.3.0
    Initial results
    Pixels per second: 1221.169800
    Duration [us]: 245666.000000
    Platform: NVIDIA CUDA
    Device: GeForce GTX 960
    Input file: test_image.png
    Output file: test_image_output.png
    Bandwidth: 25.000000
    Iterations
    Iteration: 0
    Host statistics:
    Duration: 193581.000000 us, Pixels per second: 1549.733276
    OpenCL statistics:
    Build kernel: 107 us, Copy buffer: 1098 us, Read buffer: 108427 us, Enqueue ND range: 507 us
    Iteration: 1
    Host statistics:
    Duration: 182951.000000 us, Pixels per second: 1639.774658
    OpenCL statistics:
    Build kernel: 108 us, Copy buffer: 1202 us, Read buffer: 103034 us, Enqueue ND range: 505 us
    Statistics
    Mean: 188266.000000
    Median: 188266.000000
    Variance: 56498448.000000
    Standard Deviation: 7516.544922
    Coefficient of Variation: 0.039925

## References
1. https://spin.atomicobject.com/2015/05/26/mean-shift-clustering/
1. https://spin.atomicobject.com/2015/06/02/opencl-c-mac-osx/
