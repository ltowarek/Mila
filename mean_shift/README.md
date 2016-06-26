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
    Initial results
    Duration [us]: 6724879
    Input file: test_image.png
    Output file: test_image_output.png
    Iterations
    Bandwidth: 25.000000
    Iteration: 0, Duration [us]: 6553131
    Iteration: 1, Duration [us]: 6547231
    Statistics
    Mean: 6550181.000000
    Median: 6550181.000000
    Variance: 17405000.000000
    Standard Deviation: 4171.930009
    Coefficient of Variation: 0.000637

### Parallel
Example input and output of the parallel implementation which uses mean shift with 25.0 bandwidth on OpenCL platform 0, device 0 and with 2 iterations:

    mean_shift_parallel test_image.png test_image_output.png 25.0 0 0 2
    Initial results
    Duration [us]: 562988
    Platform: NVIDIA CUDA
    Device: GeForce GTX 960
    Input file: test_image.png
    Output file: test_image_output.png
    Bandwidth: 25.000000
    Iterations
    Iteration: 0, Duration [us]: 235837
    Iteration: 1, Duration [us]: 242808
    Statistics
    Mean: 239322.500000
    Median: 239322.500000
    Variance: 24297420.000000
    Standard Deviation: 4929.241321
    Coefficient of Variation: 0.020597

## References
1. https://spin.atomicobject.com/2015/05/26/mean-shift-clustering/
1. https://spin.atomicobject.com/2015/06/02/opencl-c-mac-osx/
