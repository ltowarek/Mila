#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <CL/cl.h>
#include <fstream>

void DoubleToHex(const float input, const int precision, std::string &output) {
    const std::string hex = "0123456789ABCDEF";

    float tmp = fabsf(input);

    for (int i = 0; i < precision; ++i) {
        tmp = 16.0f * (tmp - floorf(tmp));
        output[i] = hex[(int)tmp];
    }

    output[precision] = 0;
}

int main() {
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
    const std::string source_file_name = "bbp.cl";
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

    const std::string kernel_name = "bbp";
    cl_kernel kernel = clCreateKernel(program, kernel_name.data(), &error);
    if (error) {
        printf("Failed to create the kernel\n");
        return error;
    }

    const size_t number_of_digits = 1000;
    cl_mem output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, number_of_digits * sizeof(cl_float), nullptr, &error);
    if (error) {
        printf("Failed to create the output buffer\n");
        return error;
    }


    error = clSetKernelArg(kernel, 0, sizeof(output_buffer), &output_buffer);
    if (error) {
        printf("Failed to set kernel arguments\n");
        return error;
    }

    std::vector<size_t> global_work_size = {number_of_digits};

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

    std::vector<cl_float> output(number_of_digits);
    error = clEnqueueReadBuffer(queue, output_buffer, CL_TRUE, 0, output.size() * sizeof(output.at(0)), output.data(), 0, nullptr, nullptr);
    if (error) {
        printf("Failed to read the output buffer\n");
        return error;
    }

    clReleaseMemObject(output_buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    std::string output_string = "";
    for (int i = 0; i < number_of_digits; ++i) {
        std::string hex = "";
        DoubleToHex(output.at(i), 10, hex);
        output_string += hex[0];
    }
    output_string[number_of_digits] = 0;
    printf("%s\n", output_string.c_str());

    return 0;
}
