#include <stdio.h>
#include <CL/cl.h>

int main() {
    cl_int error = 0;
    cl_uint number_of_platforms;

    error = clGetPlatformIDs(0, NULL, &number_of_platforms);
    if (CL_SUCCESS == error) {
        printf("Detected OpenCL platforms: %d", number_of_platforms);
    } else {
        printf("Error calling clGetPlatformIDs. Error code: %d", error);
    }

    return 0;
}
