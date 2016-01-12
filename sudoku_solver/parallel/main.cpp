#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <CL/cl.h>

void PrintGrids(const std::vector<int> &kGrids, const int kNumberOfGrids, const int kN) {
    for (int i = 0; i < kNumberOfGrids; ++i) {
        for (int j = 0; j < kN * kN; ++j) {
            if ((j % kN) == 0) {
                printf("\n");
            }
            printf("%d", kGrids[i * kN * kN + j]);
        }
        printf("\n");
    }
}

int main() {
    const int kN = 9;
    const std::vector<int> kSolution {
            9, 5, 4, 1, 3, 7, 6, 8, 2,
            2, 7, 3, 6, 8, 4, 1, 9, 5,
            1, 6, 8, 2, 9, 5, 7, 3, 4,
            4, 9, 5, 7, 2, 8, 3, 6, 1,
            6, 8, 1, 4, 5, 3, 2, 7, 9,
            3, 2, 7, 9, 6, 1, 5, 4, 8,
            7, 4, 9, 3, 1, 2, 8, 5, 6,
            5, 1, 6, 8, 7, 9, 4, 2, 3,
            8, 3, 2, 5, 4, 6, 9, 1, 7
    };
    std::vector<int> grid {
            0, 0, 0, 0, 3, 7, 6, 0, 0,
            0, 0, 0, 6, 0, 0, 0, 9, 0,
            0, 0, 8, 0, 0, 0, 0, 0, 4,
            0, 9, 0, 0, 0, 0, 0, 0, 1,
            6, 0, 0, 0, 0, 0, 0, 0, 9,
            3, 0, 0, 0, 0, 0, 0, 4, 0,
            7, 0, 0, 0, 0, 0, 8, 0, 0,
            0, 1, 0, 0, 0, 9, 0, 0, 0,
            0, 0, 2, 5, 4, 0, 0, 0, 0
    };

    const int kNumberOfFilledFields = 2;
    const int kGridSize = kN * kN;
    const unsigned int kNumberOfPossibleGrids = static_cast<unsigned int>(pow(static_cast<double>(kN), static_cast<double>(kNumberOfFilledFields)));

    std::vector<int> grids(kNumberOfPossibleGrids * kGridSize);
    for (int i = 0; i < grid.size(); ++i) {
        grids[i] = grid[i];
    }

    std::vector<int> empty_cells(kNumberOfPossibleGrids * kGridSize);
    std::vector<int> empty_cells_numbers(kNumberOfPossibleGrids);

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

    std::string kernel_name = "SudokuSolverBFS";
    cl_kernel kernel = clCreateKernel(program, kernel_name.data(), &error);
    if (error) {
        printf("Failed to create the kernel\n");
        return error;
    }

    cl_mem old_grids_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, grids.size() * sizeof(grids[0]), grids.data(), &error);
    if (error) {
        printf("Failed to create old_grids_buffer\n");
        return error;
    }

    int number_of_old_grids = 1;

    cl_mem number_of_old_grids_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(number_of_old_grids), &number_of_old_grids, &error);
    if (error) {
        printf("Failed to create number_of_old_grids_buffer\n");
        return error;
    }

    cl_mem new_grids_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, grids.size() * sizeof(grids[0]), nullptr, &error);
    if (error) {
        printf("Failed to create new_grids_buffer\n");
        return error;
    }

    int number_of_new_grids = 0;

    cl_mem number_of_new_grids_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(number_of_new_grids), &number_of_new_grids, &error);
    if (error) {
        printf("Failed to create number_of_new_grids_buffer\n");
        return error;
    }

    cl_mem empty_cells_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, empty_cells.size() * sizeof(empty_cells[0]), empty_cells.data(), &error);
    if (error) {
        printf("Failed to create empty_cells_buffer\n");
        return error;
    }

    cl_mem empty_cells_numbers_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, empty_cells_numbers.size() * sizeof(empty_cells_numbers[0]), empty_cells_numbers.data(), &error);
    if (error) {
        printf("Failed to create empty_cells_numbers_buffer\n");
        return error;
    }

    std::vector<size_t> global_work_size = {5};

    for (int i = 0; i < kNumberOfFilledFields; ++i) {
        error = clSetKernelArg(kernel, 0, sizeof(old_grids_buffer), &old_grids_buffer);
        if (error) {
            printf("Failed to set old_grids_buffer as kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 1, sizeof(number_of_old_grids_buffer), &number_of_old_grids_buffer);
        if (error) {
            printf("Failed to set number_of_old_grids_buffer as kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 2, sizeof(new_grids_buffer), &new_grids_buffer);
        if (error) {
            printf("Failed to set new_grids_buffer as kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 3, sizeof(number_of_new_grids_buffer), &number_of_new_grids_buffer);
        if (error) {
            printf("Failed to set number_of_new_grids_buffer as kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 4, sizeof(empty_cells_buffer), &empty_cells_buffer);
        if (error) {
            printf("Failed to set empty_cells_buffer as kernel argument\n");
            return error;
        }

        error = clSetKernelArg(kernel, 5, sizeof(empty_cells_numbers_buffer), &empty_cells_numbers_buffer);
        if (error) {
            printf("Failed to set empty_cells_numbers_buffer as kernel argument\n");
            return error;
        }

        error = clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, global_work_size.data(), nullptr, 0, nullptr, nullptr);
        if (error) {
            printf("Failed to enqueue kernel\n");
            return error;
        }

        error = clEnqueueCopyBuffer(queue, new_grids_buffer, old_grids_buffer, 0, 0, grids.size() * sizeof(grids[0]), 0, nullptr, nullptr);
        if (error) {
            printf("Failed to copy new_grids_buffer to old_grids_buffer\n");
            return error;
        }

        error = clEnqueueCopyBuffer(queue, number_of_new_grids_buffer, number_of_old_grids_buffer, 0, 0, sizeof(number_of_new_grids), 0, nullptr, nullptr);
        if (error) {
            printf("Failed to copy number_of_new_grids_buffer to number_of_old_grids_buffer\n");
            return error;
        }
    }

    kernel_name = "SudokuSolverDFS";
    kernel = clCreateKernel(program, kernel_name.data(), &error);
    if (error) {
        printf("Failed to create the kernel\n");
        return error;
    }

    cl_mem output_grid_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, grid.size() * sizeof(grid[0]), nullptr, &error);
    if (error) {
        printf("Failed to create output_grid_buffer\n");
        return error;
    }

    cl_mem is_solved_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(is_solved), &is_solved, &error);
    if (error) {
        printf("Failed to create is_solved_buffer\n");
        return error;
    }

    error = clSetKernelArg(kernel, 0, sizeof(old_grids_buffer), &old_grids_buffer);
    if (error) {
        printf("Failed to set old_grids_buffer as kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 1, sizeof(number_of_old_grids_buffer), &number_of_old_grids_buffer);
    if (error) {
        printf("Failed to set number_of_old_grids_buffer as kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 2, sizeof(empty_cells_buffer), &empty_cells_buffer);
    if (error) {
        printf("Failed to set empty_cells_buffer as kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 3, sizeof(empty_cells_numbers_buffer), &empty_cells_numbers_buffer);
    if (error) {
        printf("Failed to set empty_cells_numbers_buffer as kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 4, sizeof(output_grid_buffer), &output_grid_buffer);
    if (error) {
        printf("Failed to set the output_grid_buffer as a kernel argument\n");
        return error;
    }

    error = clSetKernelArg(kernel, 5, sizeof(is_solved_buffer), &is_solved_buffer);
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

    clReleaseMemObject(old_grids_buffer);
    clReleaseMemObject(number_of_old_grids_buffer);
    clReleaseMemObject(new_grids_buffer);
    clReleaseMemObject(number_of_new_grids_buffer);
    clReleaseMemObject(empty_cells_buffer);
    clReleaseMemObject(empty_cells_numbers_buffer);
    clReleaseMemObject(output_grid_buffer);
    clReleaseMemObject(is_solved_buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    PrintGrids(grid, 1, kN);

    if (is_solved) {
        printf("Sudoku solved successfully\n");

        if (grid != kSolution) {
            printf("Wrong solution!");
        } else {
            printf("Correct solution!\n");
        }
    } else {
        printf("Failed to solve sudoku!\n");
    }

    return 0;
}