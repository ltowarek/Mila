#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <CL/cl.h>
#include <fstream>

#include "lodepng.h"

void ReadPNGFile(const char *file_name, int &width, int &height, std::vector<cl_float4> &pixels) {
    std::vector<unsigned char> image;

    unsigned int w;
    unsigned int h;
    unsigned int error = lodepng::decode(image, w, h, file_name);
    if (error) {
        printf("Failed to read input file: %s", lodepng_error_text(error));
    }
    width = static_cast<int>(w);
    height = static_cast<int>(h);

    for (int channel = 0; channel < image.size(); channel+=4) {
        cl_float4 p = {
                static_cast<float>(image[channel]),
                static_cast<float>(image[channel + 1]),
                static_cast<float>(image[channel + 2]),
                static_cast<float>(image[channel + 3])
        };
        pixels.push_back(p);
    }
}

void WritePNGFile(const char *file_name, const int &width, const int &height, std::vector<cl_float4> &pixels) {
    std::vector<unsigned char> image;

    for (int pixel = 0; pixel < pixels.size(); ++pixel) {
        image.push_back(static_cast<unsigned char>(pixels[pixel].s[0]));
        image.push_back(static_cast<unsigned char>(pixels[pixel].s[1]));
        image.push_back(static_cast<unsigned char>(pixels[pixel].s[2]));
        image.push_back(static_cast<unsigned char>(pixels[pixel].s[3]));
    }

    unsigned int error = lodepng::encode(file_name, image, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
    if (error) {
        printf("Failed to save output file: %s", lodepng_error_text(error));
    }
}

int main() {
    const float kBandwidth = 10.0f;
    const float kEpsilon = 0.1f;
    const int kMaxIterations = 100;
    const std::string kInputFileName = "input.png";
    const std::string kOutputFileName = "output.png";
    int width = 0;
    int height = 0;
    std::vector<cl_float4> points;

    ReadPNGFile(kInputFileName.c_str(), width, height, points);

    cl_int error = 0;
    cl_uint number_of_platforms;

    error = clGetPlatformIDs(0, nullptr, &number_of_platforms);
    if (error) {
        printf("Failed to get number of available platforms\n");
        return error;
    }

    std::vector<cl_platform_id> platforms(number_of_platforms);

    error = clGetPlatformIDs(number_of_platforms, platforms.data(), nullptr);
    if (error) {
        printf("Failed to get platform ids\n");
        return error;
    }

    const size_t platform_id = 0;
    cl_platform_id platform = platforms.at(platform_id);

    cl_uint number_of_devices = 0;
    const cl_device_type device_type = CL_DEVICE_TYPE_ALL;
    error = clGetDeviceIDs(platform, device_type, 0, nullptr, &number_of_devices);
    if (error) {
        printf("Failed to get number of available devices\n");
        return error;
    }

    std::vector<cl_device_id> devices(number_of_devices);

    error = clGetDeviceIDs(platform, device_type, number_of_devices, devices.data(), nullptr);
    if (error) {
        printf("Failed to get device ids\n");
        return error;
    }

    const size_t device_id = 0;
    cl_device_id device = devices.at(device_id);
    devices.clear();
    devices.push_back(device);

    size_t device_name_length = 0;
    error = clGetDeviceInfo(device, CL_DEVICE_NAME, 0, nullptr, &device_name_length);
    if (error) {
        printf("Failed to get device name size\n");
        return error;
    }

    std::vector<char> device_name(device_name_length);

    error = clGetDeviceInfo(device, CL_DEVICE_NAME, device_name_length, device_name.data(), nullptr);
    if (error) {
        printf("Failed to get device name\n");
        return error;
    }

    printf("Device name: %s\n", device_name.data());

    const std::vector<cl_context_properties> properties = {CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(platform), 0};

    cl_context context = clCreateContext(properties.data(), devices.size(), devices.data(), nullptr, nullptr, &error);
    if (error) {
        printf("Failed to create the context\n");
        return error;
    }

    cl_command_queue_properties queue_properties = CL_QUEUE_PROFILING_ENABLE;

    cl_command_queue queue = clCreateCommandQueue(context, device, queue_properties, &error);
    if (error) {
        printf("Failed to create the command queue\n");
        return error;
    }

    // Get source file content
    const std::string source_file_name = "mean_shift.cl";
    std::ifstream in(source_file_name);
    std::vector<char> source_program((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    source_program.push_back('\0');

    const size_t source_program_size = source_program.size();
    const char* strings = source_program.data();
    cl_program program = clCreateProgramWithSource(context, 1, &strings, &source_program_size, &error);
    if (error) {
        printf("Failed to create the source program\n");
        return error;
    }

    const std::string options = "";
    error = clBuildProgram(program, devices.size(), devices.data(), options.data(), nullptr, nullptr);
    if (error) {
        printf("Failed to build the program\n");

        if (error == CL_BUILD_PROGRAM_FAILURE) {
            size_t build_log_length = 0;
            error = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_length);
            if (error) {
                printf("Failed to get build log length\n");
                return error;
            }

            std::vector<char> build_log(build_log_length);
            error = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, build_log_length, build_log.data(), nullptr);
            if (error) {
                printf("Failed to get build log\n");
                return error;
            }

            printf("%s\n", build_log.data());
        }

        return error;
    }

    const std::string kernel_name = "MeanShift";
    cl_kernel kernel = clCreateKernel(program, kernel_name.data(), &error);
    if (error) {
        printf("Failed to create the kernel\n");
        return error;
    }

    const cl_int kNumberOfPoints = points.size();

    cl_mem actual_points_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, kNumberOfPoints * sizeof(points[0]), points.data(), &error);
    if (error) {
        printf("Failed to create the actual points buffer\n");
        return error;
    }

    cl_mem shifted_points_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, kNumberOfPoints * sizeof(points[0]), points.data(), &error);
    if (error) {
        printf("Failed to create the shifted points buffer\n");
        return error;
    }

    std::vector<cl_float> distances(kNumberOfPoints, 0.0f);

    cl_mem distances_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, kNumberOfPoints * sizeof(distances[0]), nullptr, &error);
    if (error) {
        printf("Failed to create the distances buffer\n");
        return error;
    }

    std::vector<size_t> global_work_size = {static_cast<size_t>(kNumberOfPoints)};

    float difference_distance = 0.0f;
    int iteration = 0;

    do {
        clEnqueueCopyBuffer(queue, shifted_points_buffer, actual_points_buffer, 0, 0, kNumberOfPoints * sizeof(points[0]), 0, nullptr, nullptr);
        if (error) {
            printf("Failed to copy the shifted_points_buffer to the actual_points_buffer\n");
            return error;
        }

        error = clSetKernelArg(kernel, 0, sizeof(actual_points_buffer), &actual_points_buffer);
        if (error) {
            printf("Failed to set the actual_points_buffer as a kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 1, sizeof(kNumberOfPoints), &kNumberOfPoints);
        if (error) {
            printf("Failed to set the kNumberOfPoints as a kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 2, sizeof(kBandwidth), &kBandwidth);
        if (error) {
            printf("Failed to set the kBandwidth as a kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 3, sizeof(shifted_points_buffer), &shifted_points_buffer);
        if (error) {
            printf("Failed to set the shifted_points_buffer as a kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 4, sizeof(distances_buffer), &distances_buffer);
        if (error) {
            printf("Failed to set the distances_buffer as a kernel argument\n");
            return error;
        }

        error = clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, global_work_size.data(), nullptr, 0, nullptr, nullptr);
        if (error) {
            printf("Failed to enqueue the kernel\n");
            return error;
        }

        error = clFinish(queue);
        if (error) {
            printf("Failed to wait for results\n");
            return error;
        }

        error = clEnqueueReadBuffer(queue, distances_buffer, CL_TRUE, 0, kNumberOfPoints * sizeof(distances[0]), distances.data(), 0, nullptr, nullptr);
        if (error) {
            printf("Failed to read the distances_buffer\n");
            return error;
        }

        error = clFinish(queue);
        if (error) {
            printf("Failed to wait for results\n");
            return error;
        }

        difference_distance = *std::max_element(distances.begin(), distances.end());
        ++iteration;
    } while ((difference_distance > kEpsilon) && (iteration < kMaxIterations));

    error = clEnqueueReadBuffer(queue, shifted_points_buffer, CL_TRUE, 0, kNumberOfPoints * sizeof(points[0]), points.data(), 0, nullptr, nullptr);
    if (error) {
        printf("Failed to read the shifted_points_buffer\n");
        return error;
    }

    clReleaseMemObject(actual_points_buffer);
    clReleaseMemObject(shifted_points_buffer);
    clReleaseMemObject(distances_buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    WritePNGFile(kOutputFileName.c_str(), width, height, points);

    return 0;
}

