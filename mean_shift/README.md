# The mean shift algorithm
The mean shift is an algorithm for locating the maxima of a density function, which is often used for clustering and image processing.

## Usage
Sequential and parallel implementations of the mean shift algorithm are available. Basic implementation allows shifting input points using given bandwidth. Image segmentation is also available using input image which results in effect of pastel colors.

### Sequential
Sequential implementation of the mean shift algorithm accepts as an input the following parameters:

1. Number of points - number of input points which will be processed;
1. List of points - list of input points represented as 4 floats separated by space;
1. Bandwidth - mean shift bandwidth;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Parallel
Parallel implementation of the mean shift algorithm accepts as an input the following parameters:

1. Number of points - number of input points which will be processed;
1. List of points - list of input points represented as 4 floats separated by space;
1. Bandwidth - mean shift bandwidth;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Sequential image processing
Sequential image processing accepts as an input the following parameters:

1. Input file - path to the input file in PNG format;
1. Output file - path where the output file in PNG format will be saved;
1. Bandwidth - mean shift bandwidth;
1. Number of iterations - how many times the test should be repeated for performance measurements.

### Parallel image processing
Parallel image processing accepts as an input the following parameters:

1. Input file - path to the input file in PNG format;
1. Output file - path where the output file in PNG format will be saved;
1. Bandwidth - mean shift bandwidth;
1. Platform ID - OpenCL platform id;
1. Device ID - OpenCL device id;
1. Number of iterations - how many times the test should be repeated for performance measurements.

## Examples
### Sequential
Example input and output of the sequential implementation of mean shift algorithm which uses 2 points with 3.0 bandwidth and 2 iterations:

    mila mean_shift_sequential 2 0.0 1.0 0.0 0.0 2.0 3.0 0.0 0.0 3.0 2
    INFO     Version: 0.4.0
    INFO     Points:
    0.000000 1.000000 0.000000 0.000000
    2.000000 3.000000 0.000000 0.000000

    INFO     Bandwidth: 3.000000
    INFO     Number of iterations: 2
    INFO     Output:
    0.999999 1.999999 0.000000 0.000000
    1.000001 2.000001 0.000000 0.000000

    INFO     Throughput mean: 500000.000000 points/s
    INFO     Throughput median: 500000.000000 points/s
    INFO     Throughput standard deviation: 0.000000 points/s
    INFO     Throughput coefficient of variation: 0.000000
    INFO     Mean shift duration mean: 4.000000 us
    INFO     Mean shift duration median: 4.000000 us
    INFO     Mean shift duration standard deviation: 0.000000 us
    INFO     Mean shift duration coefficient of variation: 0.000000

### Parallel
Example input and output of the parallel implementation of mean shift algorithm which uses 2 points with 3.0 bandwidth on OpenCL platform 0, device 0 and 2 iterations:

    mila mean_shift_parallel 2 0.0 1.0 0.0 0.0 2.0 3.0 0.0 0.0 3.0 0 0 2
    INFO     Version: 0.4.0
    INFO     Points:
    0.000000 1.000000 0.000000 0.000000
    2.000000 3.000000 0.000000 0.000000

    INFO     Bandwidth: 3.000000
    INFO     Number of iterations: 2
    INFO     Platform id: 0
    INFO     Device id: 0
    INFO     Platform name: NVIDIA CUDA
    INFO     Device name: GeForce GTX 960
    INFO     Output:
    0.999999 1.999999 0.000000 0.000000
    1.000001 2.000001 0.000000 0.000000

    INFO     Bandwidth mean: 0.000236 GB/s
    INFO     Bandwidth median: 0.000236 GB/s
    INFO     Bandwidth standard deviation: 0.000008 GB/s
    INFO     Bandwidth coefficient of variation: 0.034328
    INFO     Throughput mean: 1592.661377 points/s
    INFO     Throughput median: 1592.661377 points/s
    INFO     Throughput standard deviation: 54.673283 points/s
    INFO     Throughput coefficient of variation: 0.034328
    INFO     Initialize duration mean: 179.500000 us
    INFO     Initialize duration median: 179.500000 us
    INFO     Initialize duration standard deviation: 23.334524 us
    INFO     Initialize duration coefficient of variation: 0.129997
    INFO     Mean shift duration mean: 1256.500000 us
    INFO     Mean shift duration median: 1256.500000 us
    INFO     Mean shift duration standard deviation: 43.133514 us
    INFO     Mean shift duration coefficient of variation: 0.034328
    INFO     Read buffer with output duration mean: 2.000000 us
    INFO     Read buffer with output duration median: 2.000000 us
    INFO     Read buffer with output duration standard deviation: 0.000000 us
    INFO     Read buffer with output duration coefficient of variation: 0.000000
    INFO     Read buffer with distances durations mean: 87.500000 us
    INFO     Read buffer with distances durations median: 87.500000 us
    INFO     Read buffer with distances durations standard deviation: 3.535534 us
    INFO     Read buffer with distances durations coefficient of variation: 0.040406
    INFO     Single read buffer with distances duration mean: 9.722222 us
    INFO     Single read buffer with distances duration median: 10.000000 us
    INFO     Single read buffer with distances duration standard deviation: 0.669113 us
    INFO     Single read buffer with distances duration coefficient of variation: 0.068823
    INFO     Copy buffer durations mean: 70.500000 us
    INFO     Copy buffer durations median: 70.500000 us
    INFO     Copy buffer durations standard deviation: 2.121320 us
    INFO     Copy buffer durations coefficient of variation: 0.030090
    INFO     Single copy buffer duration mean: 7.833333 us
    INFO     Single copy buffer duration median: 7.000000 us
    INFO     Single copy buffer duration standard deviation: 2.281640 us
    INFO     Single copy buffer duration coefficient of variation: 0.291273
    INFO     Enqueue ND range durations mean: 19.000000 us
    INFO     Enqueue ND range durations median: 19.000000 us
    INFO     Enqueue ND range durations standard deviation: 0.000000 us
    INFO     Enqueue ND range durations coefficient of variation: 0.000000
    INFO     Single enqueue ND range duration mean: 2.111111 us
    INFO     Single enqueue ND range duration median: 2.000000 us
    INFO     Single enqueue ND range duration standard deviation: 0.323381 us
    INFO     Single enqueue ND range duration coefficient of variation: 0.153180

### Sequential image processing
Example input and output of the sequential image processing which uses mean shift with 25.0 bandwidth and 2 iterations:

    mila mean_shift_sequential_image_processing test_image.png test_image_output.png 25.0 2
    INFO     Version: 0.4.0
    INFO     Input file: test_image.png
    INFO     Output file: test_image_output.png
    INFO     Bandwidth: 25.000000
    INFO     Number of iterations: 2
    INFO     Throughput mean: 250.587799 pixels/s
    INFO     Throughput median: 250.587799 pixels/s
    INFO     Throughput standard deviation: 0.137772 pixels/s
    INFO     Throughput coefficient of variation: 0.000550
    INFO     Mean shift image processing duration mean: 4788741.500000 us
    INFO     Mean shift image processing duration median: 4788741.500000 us
    INFO     Mean shift image processing duration standard deviation: 2632.558594 us
    INFO     Mean shift image processing duration coefficient of variation: 0.000550

### Parallel image processing
Example input and output of the parallel image processing which uses mean shift with 25.0 bandwidth on OpenCL platform 0, device 0 and with 2 iterations:

    mila mean_shift_parallel_image_processing test_image.png test_image_output.png 25.0 0 0 2
    INFO     Version: 0.4.0
    INFO     Input file: test_image.png
    INFO     Output file: test_image_output.png
    INFO     Bandwidth: 25.000000
    INFO     Number of iterations: 2
    INFO     Platform id: 0
    INFO     Device id: 0
    INFO     Platform name: NVIDIA CUDA
    INFO     Device name: GeForce GTX 960
    INFO     Throughput mean: 10263.517578 pixels/s
    INFO     Throughput median: 10263.517578 pixels/s
    INFO     Throughput standard deviation: 281.576965 pixels/s
    INFO     Throughput coefficient of variation: 0.027435
    INFO     Mean shift image processing duration mean: 116963.000000 us
    INFO     Mean shift image processing duration median: 116963.000000 us
    INFO     Mean shift image processing duration standard deviation: 3208.850586 us
    INFO     Mean shift image processing duration coefficient of variation: 0.027435

## References
1. https://spin.atomicobject.com/2015/05/26/mean-shift-clustering/
1. https://spin.atomicobject.com/2015/06/02/opencl-c-mac-osx/
