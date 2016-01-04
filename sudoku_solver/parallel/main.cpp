#include <vector>
#include <fstream>
#include <sstream>
#include <CL/cl.h>

int main() {
    const int kN = 9;
    const std::vector<int> kSolution {
            5, 3, 4, 6, 7, 8, 9, 1, 2,
            6, 7, 2, 1, 9, 5, 3, 4, 8,
            1, 9, 8, 3, 4, 2, 5, 6, 7,
            8, 5, 9, 7, 6, 1, 4, 2, 3,
            4, 2, 6, 8, 5, 3, 7, 9, 1,
            7, 1, 3, 9, 2, 4, 8, 5, 6,
            9, 6, 1, 5, 3, 7, 2, 8, 4,
            2, 8, 7, 4, 1, 9, 6, 3, 5,
            3, 4, 5, 2, 8, 6, 1, 7, 9
    };
    std::vector<int> grid {
            5, 3, 0, 0, 7, 0, 0, 0, 0,
            6, 0, 0, 1, 9, 5, 0, 0, 0,
            0, 9, 8, 0, 0, 0, 0, 6, 0,
            8, 0, 0, 0, 6, 0, 0, 0, 3,
            4, 0, 0, 8, 0, 3, 0, 0, 1,
            7, 0, 0, 0, 2, 0, 0, 0, 6,
            0, 6, 0, 0, 0, 0, 2, 8, 0,
            0, 0, 0, 4, 1, 9, 0, 0, 5,
            0, 0, 0, 0, 8, 0, 0, 7, 9
    };

    const int kNumberOfGrids = 1;
    std::vector<int> grids(kNumberOfGrids * kN * kN);
    grids = grid;

    cl_int is_solved = 0;

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
    const std::string source_file_name = "sudoku_solver.cl";
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

    std::stringstream string_stream;
    string_stream << "-D kN=" << kN;
    const std::string options = string_stream.str();
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

    const std::string kernel_name = "SudokuSolver";
    cl_kernel kernel = clCreateKernel(program, kernel_name.data(), &error);
    if (error) {
        printf("Failed to create the kernel\n");
        return error;
    }

    cl_mem input_grids_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, grids.size() * sizeof(grids[0]), grids.data(), &error);
    if (error) {
        printf("Failed to create the input grids buffer\n");
        return error;
    }

    cl_mem output_grid_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, grid.size() * sizeof(grid[0]), nullptr, &error);
    if (error) {
        printf("Failed to create the output grid buffer\n");
        return error;
    }

    cl_mem is_solved_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(is_solved), &is_solved, &error);
    if (error) {
        printf("Failed to create the is_solved buffer\n");
        return error;
    }

    std::vector<size_t> global_work_size = {kNumberOfGrids};

    error = clSetKernelArg(kernel, 0, sizeof(input_grids_buffer), &input_grids_buffer);
    if (error) {
        printf("Failed to set the input_grids_buffer as a kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 1, sizeof(kNumberOfGrids), &kNumberOfGrids);
    if (error) {
        printf("Failed to set the kNumberOfGrids as a kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 2, sizeof(output_grid_buffer), &output_grid_buffer);
    if (error) {
        printf("Failed to set the output_grid_buffer as a kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 3, sizeof(is_solved_buffer), &is_solved_buffer);
    if (error) {
        printf("Failed to set the is_solved_buffer as a kernel argument\n");
        return error;
    }

    error = clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, global_work_size.data(), nullptr, 0, nullptr, nullptr);
    if (error) {
        printf("Failed to enqueue the kernel\n");
        return error;
    }

    error = clEnqueueReadBuffer(queue, output_grid_buffer, CL_TRUE, 0, grid.size() * sizeof(grid[0]), grid.data(), 0, nullptr, nullptr);
    if (error) {
        printf("Failed to read the output_grid_buffer\n");
        return error;
    }

    error = clEnqueueReadBuffer(queue, is_solved_buffer, CL_TRUE, 0, sizeof(is_solved), &is_solved, 0, nullptr, nullptr);
    if (error) {
        printf("Failed to read the is_solved_buffer\n");
        return error;
    }

    error = clFinish(queue);
    if (error) {
        printf("Failed to wait for results\n");
        return error;
    }

    clReleaseMemObject(input_grids_buffer);
    clReleaseMemObject(output_grid_buffer);
    clReleaseMemObject(is_solved_buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    if (grid != kSolution) {
        printf("Wrong solution!");
    } else {
        printf("Correct solution!");
    }

    return 0;
}