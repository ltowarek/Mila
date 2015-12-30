#include <cstdio>
#include <iterator>
#include <sstream>
#include <vector>
#include <CL/cl.h>
#include "lasote/json11/json11.hpp"

std::string Join(std::vector<std::string> strings, std::string separator) {
    std::string output = "";
    if (strings.size() == 0) {
        output = "";
    } else if (strings.size() == 1) {
        output = strings[0];
    } else {
        std::ostringstream os;
        std::copy(strings.begin(), strings.end()-1, std::ostream_iterator<std::string>(os, separator.c_str()));
        os << *strings.rbegin();
        output = os.str();
    }
    return output;
}

std::string PlatformInfoToString(cl_platform_info param_name) {
    std::string output = "NULL";
    if (param_name == CL_PLATFORM_PROFILE) {
        output = "CL_PLATFORM_PROFILE";
    } else if (param_name == CL_PLATFORM_VERSION) {
        output = "CL_PLATFORM_VERSION";
    } else if (param_name == CL_PLATFORM_NAME) {
        output = "CL_PLATFORM_NAME";
    } else if (param_name == CL_PLATFORM_VENDOR) {
        output = "CL_PLATFORM_VENDOR";
    } else if (param_name == CL_PLATFORM_EXTENSIONS) {
        output = "CL_PLATFORM_EXTENSIONS";
    }
    return output;
}

template <typename T>
cl_int GetPlatformInfo(cl_platform_id &platform, cl_platform_info param_name, T &param_value) {
    cl_int error = CL_SUCCESS;
    error |= clGetPlatformInfo(platform, param_name, sizeof(T), &param_value, nullptr);
    if (error) {
        printf("Failed to get param value\n");
        printf("Failed to get %s\n", PlatformInfoToString(param_name).c_str());
    }
    return error;
}

template <typename T>
cl_int GetPlatformInfo(cl_platform_id &platform, cl_platform_info param_name, std::vector<T> &param_value) {
    cl_int error = CL_SUCCESS;
    size_t size = 0;

    error |= clGetPlatformInfo(platform, param_name, 0, nullptr, &size);
    if (error) {
        printf("Failed to get param value size\n");
    }

    param_value.resize(size / sizeof(T));

    error |= clGetPlatformInfo(platform, param_name, size, param_value.data(), nullptr);
    if (error) {
        printf("Failed to get param value\n");
        printf("Failed to get %s\n", PlatformInfoToString(param_name).c_str());
    }

    return error;
}

std::string CommandQueuePropertiesToString(cl_command_queue_properties properties) {
    std::vector<std::string> tmp;
    if (properties % CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) {
        tmp.push_back("CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE");
    }
    if (properties % CL_QUEUE_PROFILING_ENABLE) {
        tmp.push_back("CL_QUEUE_PROFILING_ENABLE");
    }
    std::string output = Join(tmp, " | ");
    return output;
}

std::string DeviceExecCapabilitiesToString(cl_device_exec_capabilities capabilities) {
    std::vector<std::string> tmp;
    if (capabilities % CL_EXEC_KERNEL) {
        tmp.push_back("CL_EXEC_KERNEL");
    }
    if (capabilities % CL_EXEC_NATIVE_KERNEL) {
        tmp.push_back("CL_EXEC_NATIVE_KERNEL");
    }
    std::string output = Join(tmp, " | ");
    return output;
}

std::string DeviceLocalMemTypeToString(cl_device_local_mem_type type) {
    std::string output = "NULL";
    if (type == CL_LOCAL) {
        output = "CL_LOCAL";
    } else if (type == CL_GLOBAL) {
        output = "CL_GLOBAL";
    }
    return output;
}

std::string DeviceMemCacheTypeToString(cl_device_mem_cache_type type) {
    std::string output = "NULL";
    if (type == CL_NONE) {
        output = "CL_NONE";
    } else if (type == CL_READ_ONLY_CACHE) {
        output = "CL_READ_ONLY_CACHE";
    } else if (type == CL_READ_WRITE_CACHE) {
        output = "CL_READ_WRITE_CACHE";
    }
    return output;
}

std::string DeviceFPConfigToString(cl_device_fp_config config) {
    std::vector<std::string> tmp;
    if (config & CL_FP_DENORM) {
        tmp.push_back("CL_FP_DENORM");
    }
    if (config & CL_FP_INF_NAN) {
        tmp.push_back("CL_FP_INF_NAN");
    }
    if (config & CL_FP_ROUND_TO_NEAREST) {
        tmp.push_back("CL_FP_ROUND_TO_NEAREST");
    }
    if (config & CL_FP_ROUND_TO_ZERO) {
        tmp.push_back("CL_FP_ROUND_TO_ZERO");
    }
    if (config & CL_FP_ROUND_TO_INF) {
        tmp.push_back("CL_FP_ROUND_TO_INF");
    }
    if (config & CL_FP_FMA) {
        tmp.push_back("CL_FP_FMA");
    }
    if (config & CL_FP_SOFT_FLOAT) {
        tmp.push_back("CL_FP_SOFT_FLOAT");
    }

    std::string output = Join(tmp, " | ");
    return output;
}

std::string DeviceTypeToString(cl_device_type type) {
    std::string output = "NULL";
    if (type == CL_DEVICE_TYPE_CPU) {
        output = "CL_DEVICE_TYPE_CPU";
    } else if (type == CL_DEVICE_TYPE_GPU) {
        output = "CL_DEVICE_TYPE_GPU";
    } else if (type == CL_DEVICE_TYPE_ACCELERATOR) {
        output = "CL_DEVICE_TYPE_ACCELERATOR";
    } else if (type == CL_DEVICE_TYPE_DEFAULT) {
        output = "CL_DEVICE_TYPE_DEFAULT";
    }
    return output;
}

std::string DeviceInfoToString(cl_device_info param_name) {
    std::string output = "NULL";
    if (param_name == CL_DEVICE_TYPE) {
        output = "CL_DEVICE_TYPE";
    } else if (param_name == CL_DEVICE_VENDOR_ID) {
        output = "CL_DEVICE_VENDOR_ID";
    } else if (param_name == CL_DEVICE_MAX_COMPUTE_UNITS) {
        output = "CL_DEVICE_MAX_COMPUTE_UNITS";
    } else if (param_name == CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS) {
        output = "CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS";
    } else if (param_name == CL_DEVICE_MAX_WORK_ITEM_SIZES) {
        output = "CL_DEVICE_MAX_WORK_ITEM_SIZES";
    } else if (param_name == CL_DEVICE_MAX_WORK_GROUP_SIZE) {
        output = "CL_DEVICE_MAX_WORK_GROUP_SIZE";
    } else if (param_name == CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR) {
        output = "CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR";
    } else if (param_name == CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT) {
        output = "CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT";
    } else if (param_name == CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT) {
        output = "CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT";
    } else if (param_name == CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG) {
        output = "CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG";
    } else if (param_name == CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT) {
        output = "CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT";
    } else if (param_name == CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE) {
        output = "CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE";
    } else if (param_name == CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF) {
        output = "CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF";
    } else if (param_name == CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR) {
        output = "CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR";
    } else if (param_name == CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT) {
        output = "CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT";
    } else if (param_name == CL_DEVICE_NATIVE_VECTOR_WIDTH_INT) {
        output = "CL_DEVICE_NATIVE_VECTOR_WIDTH_INT";
    } else if (param_name == CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG) {
        output = "CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG";
    } else if (param_name == CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT) {
        output = "CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT";
    } else if (param_name == CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE) {
        output = "CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE";
    } else if (param_name == CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF) {
        output = "CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF";
    } else if (param_name == CL_DEVICE_MAX_CLOCK_FREQUENCY) {
        output = "CL_DEVICE_MAX_CLOCK_FREQUENCY";
    } else if (param_name == CL_DEVICE_ADDRESS_BITS) {
        output = "CL_DEVICE_ADDRESS_BITS";
    } else if (param_name == CL_DEVICE_MAX_MEM_ALLOC_SIZE) {
        output = "CL_DEVICE_MAX_MEM_ALLOC_SIZE";
    } else if (param_name == CL_DEVICE_IMAGE_SUPPORT) {
        output = "CL_DEVICE_IMAGE_SUPPORT";
    } else if (param_name == CL_DEVICE_MAX_READ_IMAGE_ARGS) {
        output = "CL_DEVICE_MAX_READ_IMAGE_ARGS";
    } else if (param_name == CL_DEVICE_MAX_WRITE_IMAGE_ARGS) {
        output = "CL_DEVICE_MAX_WRITE_IMAGE_ARGS";
    } else if (param_name == CL_DEVICE_IMAGE2D_MAX_WIDTH) {
        output = "CL_DEVICE_IMAGE2D_MAX_WIDTH";
    } else if (param_name == CL_DEVICE_IMAGE2D_MAX_HEIGHT) {
        output = "CL_DEVICE_IMAGE2D_MAX_HEIGHT";
    } else if (param_name == CL_DEVICE_IMAGE3D_MAX_WIDTH) {
        output = "CL_DEVICE_IMAGE3D_MAX_WIDTH";
    } else if (param_name == CL_DEVICE_IMAGE3D_MAX_HEIGHT) {
        output = "CL_DEVICE_IMAGE3D_MAX_HEIGHT";
    } else if (param_name == CL_DEVICE_IMAGE3D_MAX_DEPTH) {
        output = "CL_DEVICE_IMAGE3D_MAX_DEPTH";
    } else if (param_name == CL_DEVICE_MAX_SAMPLERS) {
        output = "CL_DEVICE_MAX_SAMPLERS";
    } else if (param_name == CL_DEVICE_MAX_PARAMETER_SIZE) {
        output = "CL_DEVICE_MAX_PARAMETER_SIZE";
    } else if (param_name == CL_DEVICE_MEM_BASE_ADDR_ALIGN) {
        output = "CL_DEVICE_MEM_BASE_ADDR_ALIGN";
    } else if (param_name == CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE) {
        output = "CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE";
    } else if (param_name == CL_DEVICE_SINGLE_FP_CONFIG) {
        output = "CL_DEVICE_SINGLE_FP_CONFIG";
    } else if (param_name == CL_DEVICE_GLOBAL_MEM_CACHE_TYPE) {
        output = "CL_DEVICE_GLOBAL_MEM_CACHE_TYPE";
    } else if (param_name == CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE) {
        output = "CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE";
    } else if (param_name == CL_DEVICE_GLOBAL_MEM_CACHE_SIZE) {
        output = "CL_DEVICE_GLOBAL_MEM_CACHE_SIZE";
    } else if (param_name == CL_DEVICE_GLOBAL_MEM_SIZE) {
        output = "CL_DEVICE_GLOBAL_MEM_SIZE";
    } else if (param_name == CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE) {
        output = "CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE";
    } else if (param_name == CL_DEVICE_MAX_CONSTANT_ARGS) {
        output = "CL_DEVICE_MAX_CONSTANT_ARGS";
    } else if (param_name == CL_DEVICE_LOCAL_MEM_TYPE) {
        output = "CL_DEVICE_LOCAL_MEM_TYPE";
    } else if (param_name == CL_DEVICE_LOCAL_MEM_SIZE) {
        output = "CL_DEVICE_LOCAL_MEM_SIZE";
    } else if (param_name == CL_DEVICE_ERROR_CORRECTION_SUPPORT) {
        output = "CL_DEVICE_ERROR_CORRECTION_SUPPORT";
    } else if (param_name == CL_DEVICE_HOST_UNIFIED_MEMORY) {
        output = "CL_DEVICE_HOST_UNIFIED_MEMORY";
    } else if (param_name == CL_DEVICE_PROFILING_TIMER_RESOLUTION) {
        output = "CL_DEVICE_PROFILING_TIMER_RESOLUTION";
    } else if (param_name == CL_DEVICE_ENDIAN_LITTLE) {
        output = "CL_DEVICE_ENDIAN_LITTLE";
    } else if (param_name == CL_DEVICE_AVAILABLE) {
        output = "CL_DEVICE_AVAILABLE";
    } else if (param_name == CL_DEVICE_COMPILER_AVAILABLE) {
        output = "CL_DEVICE_COMPILER_AVAILABLE";
    } else if (param_name == CL_DEVICE_EXECUTION_CAPABILITIES) {
        output = "CL_DEVICE_EXECUTION_CAPABILITIES";
    } else if (param_name == CL_DEVICE_QUEUE_PROPERTIES) {
        output = "CL_DEVICE_QUEUE_PROPERTIES";
    } else if (param_name == CL_DEVICE_PLATFORM) {
        output = "CL_DEVICE_PLATFORM";
    } else if (param_name == CL_DEVICE_NAME) {
        output = "CL_DEVICE_NAME";
    } else if (param_name == CL_DEVICE_VENDOR) {
        output = "CL_DEVICE_VENDOR";
    } else if (param_name == CL_DRIVER_VERSION) {
        output = "CL_DRIVER_VERSION";
    } else if (param_name == CL_DEVICE_PROFILE) {
        output = "CL_DEVICE_PROFILE";
    } else if (param_name == CL_DEVICE_VERSION) {
        output = "CL_DEVICE_VERSION";
    } else if (param_name == CL_DEVICE_OPENCL_C_VERSION) {
        output = "CL_DEVICE_OPENCL_C_VERSION";
    } else if (param_name == CL_DEVICE_EXTENSIONS) {
        output = "CL_DEVICE_EXTENSIONS";
    }
    return output;
}

template <typename T>
cl_int GetDeviceInfo(cl_device_id &device, cl_device_info param_name, T &param_value) {
    cl_int error = CL_SUCCESS;
    error |= clGetDeviceInfo(device, param_name, sizeof(T), &param_value, nullptr);
    if (error) {
        printf("Failed to get param value\n");
        printf("Failed to get %s\n", DeviceInfoToString(param_name).c_str());
    }
    return error;
}

template <typename T>
cl_int GetDeviceInfo(cl_device_id &device, cl_device_info param_name, std::vector<T> &param_value) {
    cl_int error = CL_SUCCESS;
    size_t size = 0;

    error |= clGetDeviceInfo(device, param_name, 0, nullptr, &size);
    if (error) {
        printf("Failed to get param value size\n");
    }

    param_value.resize(size / sizeof(T));

    error |= clGetDeviceInfo(device, param_name, size, param_value.data(), nullptr);
    if (error) {
        printf("Failed to get param value\n");
        printf("Failed to get %s\n", DeviceInfoToString(param_name).c_str());
    }

    return error;
}

int main() {
    cl_int error = CL_SUCCESS;

    json11::Json platforms_json;
    std::vector<json11::Json> platform_jsons;
    json11::Json devices_json;
    std::vector<json11::Json> device_jsons;

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

    for (int i = 0; i < platforms.size(); ++i) {
        const size_t platform_id = static_cast<size_t>(i);
        cl_platform_id platform = platforms.at(platform_id);

        std::vector<char> platform_profile;
        error = GetPlatformInfo(platform, CL_PLATFORM_PROFILE, platform_profile);
        if (error) {
            return error;
        }

        std::vector<char> platform_version;
        error = GetPlatformInfo(platform, CL_PLATFORM_VERSION, platform_version);
        if (error) {
            return error;
        }

        std::vector<char> platform_name;
        error = GetPlatformInfo(platform, CL_PLATFORM_NAME, platform_name);
        if (error) {
            return error;
        }

        std::vector<char> platform_vendor;
        error = GetPlatformInfo(platform, CL_PLATFORM_VENDOR, platform_vendor);
        if (error) {
            return error;
        }

        std::vector<char> platform_extensions;
        error = GetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, platform_extensions);
        if (error) {
            return error;
        }

        json11::Json platform_json = json11::Json::object({
                                                                  {PlatformInfoToString(CL_PLATFORM_PROFILE), platform_profile.data()},
                                                                  {PlatformInfoToString(CL_PLATFORM_VERSION), platform_version.data()},
                                                                  {PlatformInfoToString(CL_PLATFORM_NAME), platform_name.data()},
                                                                  {PlatformInfoToString(CL_PLATFORM_VENDOR), platform_vendor.data()},
                                                                  {PlatformInfoToString(CL_PLATFORM_EXTENSIONS), platform_extensions.data()},
                                                          });
        platform_jsons.push_back(platform_json);

        cl_uint number_of_devices = 0;
        error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &number_of_devices);
        if (error) {
            printf("Failed to get number of available devices\n");
            return error;
        }

        std::vector<cl_device_id> devices(number_of_devices);

        error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, number_of_devices, devices.data(), nullptr);
        if (error) {
            printf("Failed to get device ids\n");
            return error;
        }

        for (int j = 0; j < devices.size(); ++j) {
            const size_t device_id = static_cast<size_t>(j);
            cl_device_id device = devices.at(device_id);

            cl_device_type device_type = 0;
            error = GetDeviceInfo(device, CL_DEVICE_TYPE, device_type);
            if (error) {
                return error;
            }

            cl_uint device_vendor_id = 0;
            error = GetDeviceInfo(device, CL_DEVICE_VENDOR_ID, device_vendor_id);
            if (error) {
                return error;
            }

            cl_uint device_max_compute_units = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, device_max_compute_units);
            if (error) {
                return error;
            }

            cl_uint device_max_work_item_dimensions = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, device_max_work_item_dimensions);
            if (error) {
                return error;
            }

            std::vector<size_t> device_max_work_item_sizes;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, device_max_work_item_sizes);
            if (error) {
                return error;
            }

            cl_uint device_max_work_group_size = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, device_max_work_group_size);
            if (error) {
                return error;
            }

            cl_uint device_preferred_vector_width_char = 0;
            error = GetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, device_preferred_vector_width_char);
            if (error) {
                return error;
            }

            cl_uint device_preferred_vector_width_short = 0;
            error = GetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, device_preferred_vector_width_short);
            if (error) {
                return error;
            }

            cl_uint device_preferred_vector_width_int = 0;
            error = GetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, device_preferred_vector_width_int);
            if (error) {
                return error;
            }

            cl_uint device_preferred_vector_width_long = 0;
            error = GetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, device_preferred_vector_width_long);
            if (error) {
                return error;
            }

            cl_uint device_preferred_vector_width_float = 0;
            error = GetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, device_preferred_vector_width_float);
            if (error) {
                return error;
            }

            cl_uint device_preferred_vector_width_double = 0;
            error = GetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, device_preferred_vector_width_double);
            if (error) {
                return error;
            }

            cl_uint device_preferred_vector_width_half = 0;
            error = GetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, device_preferred_vector_width_half);
            if (error) {
                return error;
            }

            cl_uint device_native_vector_width_char = 0;
            error = GetDeviceInfo(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, device_native_vector_width_char);
            if (error) {
                return error;
            }

            cl_uint device_native_vector_width_short = 0;
            error = GetDeviceInfo(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, device_native_vector_width_short);
            if (error) {
                return error;
            }

            cl_uint device_native_vector_width_int = 0;
            error = GetDeviceInfo(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, device_native_vector_width_int);
            if (error) {
                return error;
            }

            cl_uint device_native_vector_width_long = 0;
            error = GetDeviceInfo(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, device_native_vector_width_long);
            if (error) {
                return error;
            }

            cl_uint device_native_vector_width_float = 0;
            error = GetDeviceInfo(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, device_native_vector_width_float);
            if (error) {
                return error;
            }

            cl_uint device_native_vector_width_double = 0;
            error = GetDeviceInfo(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, device_native_vector_width_double);
            if (error) {
                return error;
            }

            cl_uint device_native_vector_width_half = 0;
            error = GetDeviceInfo(device, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, device_native_vector_width_half);
            if (error) {
                return error;
            }

            cl_uint device_max_clock_frequency = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, device_max_clock_frequency);
            if (error) {
                return error;
            }

            cl_uint device_address_bits = 0;
            error = GetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, device_address_bits);
            if (error) {
                return error;
            }

            cl_ulong device_max_mem_alloc_size = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, device_max_mem_alloc_size);
            if (error) {
                return error;
            }

            cl_bool device_image_support = CL_TRUE;
            error = GetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, device_image_support);
            if (error) {
                return error;
            }

            cl_uint device_max_read_image_args = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_READ_IMAGE_ARGS, device_max_read_image_args);
            if (error) {
                return error;
            }

            cl_uint device_max_write_image_args = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, device_max_write_image_args);
            if (error) {
                return error;
            }

            size_t device_image2d_max_width = 0;
            error = GetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, device_image2d_max_width);
            if (error) {
                return error;
            }

            size_t device_image2d_max_height = 0;
            error = GetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, device_image2d_max_height);
            if (error) {
                return error;
            }

            size_t device_image3d_max_width = 0;
            error = GetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_WIDTH, device_image3d_max_width);
            if (error) {
                return error;
            }

            size_t device_image3d_max_height = 0;
            error = GetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT, device_image3d_max_height);
            if (error) {
                return error;
            }

            size_t device_image3d_max_depth = 0;
            error = GetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_DEPTH, device_image3d_max_depth);
            if (error) {
                return error;
            }

            cl_uint device_max_samplers = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_SAMPLERS, device_max_samplers);
            if (error) {
                return error;
            }

            size_t device_max_parameter_size = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_PARAMETER_SIZE, device_max_parameter_size);
            if (error) {
                return error;
            }

            cl_uint device_mem_base_addr_align = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MEM_BASE_ADDR_ALIGN, device_mem_base_addr_align);
            if (error) {
                return error;
            }

            cl_uint device_min_data_type_align = 0;
            error = GetDeviceInfo(device, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, device_min_data_type_align);
            if (error) {
                return error;
            }

            cl_device_fp_config device_single_fp_config;
            error = GetDeviceInfo(device, CL_DEVICE_SINGLE_FP_CONFIG, device_single_fp_config);
            if (error) {
                return error;
            }

            cl_device_mem_cache_type device_global_mem_cache_type;
            error = GetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, device_global_mem_cache_type);
            if (error) {
                return error;
            }

            cl_uint device_global_mem_cacheline_size;
            error = GetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, device_global_mem_cacheline_size);
            if (error) {
                return error;
            }

            cl_ulong device_global_mem_cache_size;
            error = GetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, device_global_mem_cache_size);
            if (error) {
                return error;
            }

            cl_ulong device_global_mem_size;
            error = GetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, device_global_mem_size);
            if (error) {
                return error;
            }

            cl_ulong device_max_constant_buffer_size;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, device_max_constant_buffer_size);
            if (error) {
                return error;
            }

            cl_uint device_max_constant_args;
            error = GetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_ARGS, device_max_constant_args);
            if (error) {
                return error;
            }

            cl_device_local_mem_type device_local_mem_type;
            error = GetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE, device_local_mem_type);
            if (error) {
                return error;
            }

            cl_ulong device_local_mem_size;
            error = GetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, device_local_mem_size);
            if (error) {
                return error;
            }

            cl_bool device_error_correction_support;
            error = GetDeviceInfo(device, CL_DEVICE_ERROR_CORRECTION_SUPPORT, device_error_correction_support);
            if (error) {
                return error;
            }

            size_t device_profiling_timer_resolution;
            error = GetDeviceInfo(device, CL_DEVICE_PROFILING_TIMER_RESOLUTION, device_profiling_timer_resolution);
            if (error) {
                return error;
            }

            cl_bool device_endian_little;
            error = GetDeviceInfo(device, CL_DEVICE_ENDIAN_LITTLE, device_endian_little);
            if (error) {
                return error;
            }

            cl_bool device_available;
            error = GetDeviceInfo(device, CL_DEVICE_AVAILABLE, device_available);
            if (error) {
                return error;
            }

            cl_bool device_compiler_available;
            error = GetDeviceInfo(device, CL_DEVICE_COMPILER_AVAILABLE, device_compiler_available);
            if (error) {
                return error;
            }

            cl_device_exec_capabilities device_execution_capabilities;
            error = GetDeviceInfo(device, CL_DEVICE_EXECUTION_CAPABILITIES, device_execution_capabilities);
            if (error) {
                return error;
            }

            cl_command_queue_properties device_queue_properties;
            error = GetDeviceInfo(device, CL_DEVICE_QUEUE_PROPERTIES, device_queue_properties);
            if (error) {
                return error;
            }

            cl_platform_id device_platform;
            error = GetDeviceInfo(device, CL_DEVICE_PLATFORM, device_platform);
            if (error) {
                return error;
            }

            std::vector<char> device_name;
            error = GetDeviceInfo(device, CL_DEVICE_NAME, device_name);
            if (error) {
                return error;
            }

            std::vector<char> device_vendor;
            error = GetDeviceInfo(device, CL_DEVICE_VENDOR, device_vendor);
            if (error) {
                return error;
            }

            std::vector<char> driver_version;
            error = GetDeviceInfo(device, CL_DRIVER_VERSION, driver_version);
            if (error) {
                return error;
            }

            std::vector<char> device_profile;
            error = GetDeviceInfo(device, CL_DEVICE_PROFILE, device_profile);
            if (error) {
                return error;
            }

            std::vector<char> device_version;
            error = GetDeviceInfo(device, CL_DEVICE_VERSION, device_version);
            if (error) {
                return error;
            }

            std::vector<char> device_opencl_c_version;
            error = GetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, device_opencl_c_version);
            if (error) {
                return error;
            }

            std::vector<char> device_extensions;
            error = GetDeviceInfo(device, CL_DEVICE_EXTENSIONS, device_extensions);
            if (error) {
                return error;
            }

            //TODO: Do not cast long to int as it causes issues with CL_DEVICE_GLOBAL_MEM_SIZE
            json11::Json device_json = json11::Json::object({
                                                                    {DeviceInfoToString(CL_DEVICE_TYPE), DeviceTypeToString(device_type)},
                                                                    {DeviceInfoToString(CL_DEVICE_VENDOR_ID), static_cast<int>(device_vendor_id)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_COMPUTE_UNITS), static_cast<int>(device_max_compute_units)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS), static_cast<int>(device_max_work_item_dimensions)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_WORK_ITEM_SIZES), std::vector<int>(device_max_work_item_sizes.begin(), device_max_work_item_sizes.end())},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_WORK_GROUP_SIZE), static_cast<int>(device_max_work_group_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR), static_cast<int>(device_preferred_vector_width_char)},
                                                                    {DeviceInfoToString(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT), static_cast<int>(device_preferred_vector_width_short)},
                                                                    {DeviceInfoToString(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT), static_cast<int>(device_preferred_vector_width_int)},
                                                                    {DeviceInfoToString(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG), static_cast<int>(device_preferred_vector_width_long)},
                                                                    {DeviceInfoToString(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT), static_cast<int>(device_preferred_vector_width_float)},
                                                                    {DeviceInfoToString(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE), static_cast<int>(device_preferred_vector_width_double)},
                                                                    {DeviceInfoToString(CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF), static_cast<int>(device_preferred_vector_width_half)},
                                                                    {DeviceInfoToString(CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR), static_cast<int>(device_native_vector_width_char)},
                                                                    {DeviceInfoToString(CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT), static_cast<int>(device_native_vector_width_short)},
                                                                    {DeviceInfoToString(CL_DEVICE_NATIVE_VECTOR_WIDTH_INT), static_cast<int>(device_native_vector_width_int)},
                                                                    {DeviceInfoToString(CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG), static_cast<int>(device_native_vector_width_long)},
                                                                    {DeviceInfoToString(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT), static_cast<int>(device_native_vector_width_float)},
                                                                    {DeviceInfoToString(CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE), static_cast<int>(device_native_vector_width_double)},
                                                                    {DeviceInfoToString(CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF), static_cast<int>(device_native_vector_width_half)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_CLOCK_FREQUENCY), static_cast<int>(device_max_clock_frequency)},
                                                                    {DeviceInfoToString(CL_DEVICE_ADDRESS_BITS), static_cast<int>(device_address_bits)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_MEM_ALLOC_SIZE), static_cast<int>(device_max_mem_alloc_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_IMAGE_SUPPORT), static_cast<bool>(device_image_support)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_READ_IMAGE_ARGS), static_cast<int>(device_max_read_image_args)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_WRITE_IMAGE_ARGS), static_cast<int>(device_max_write_image_args)},
                                                                    {DeviceInfoToString(CL_DEVICE_IMAGE2D_MAX_WIDTH), static_cast<int>(device_image2d_max_width)},
                                                                    {DeviceInfoToString(CL_DEVICE_IMAGE2D_MAX_HEIGHT), static_cast<int>(device_image2d_max_height)},
                                                                    {DeviceInfoToString(CL_DEVICE_IMAGE3D_MAX_WIDTH), static_cast<int>(device_image3d_max_width)},
                                                                    {DeviceInfoToString(CL_DEVICE_IMAGE3D_MAX_HEIGHT), static_cast<int>(device_image3d_max_height)},
                                                                    {DeviceInfoToString(CL_DEVICE_IMAGE3D_MAX_DEPTH), static_cast<int>(device_image3d_max_depth)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_SAMPLERS), static_cast<int>(device_max_samplers)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_PARAMETER_SIZE), static_cast<int>(device_max_parameter_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_MEM_BASE_ADDR_ALIGN), static_cast<int>(device_mem_base_addr_align)},
                                                                    {DeviceInfoToString(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE), static_cast<int>(device_min_data_type_align)},
                                                                    {DeviceInfoToString(CL_DEVICE_SINGLE_FP_CONFIG), DeviceFPConfigToString(device_single_fp_config)},
                                                                    {DeviceInfoToString(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE), DeviceMemCacheTypeToString(device_global_mem_cache_type)},
                                                                    {DeviceInfoToString(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE), static_cast<int>(device_global_mem_cacheline_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE), static_cast<int>(device_global_mem_cache_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_GLOBAL_MEM_SIZE), static_cast<int>(device_global_mem_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE), static_cast<int>(device_max_constant_buffer_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_MAX_CONSTANT_ARGS), static_cast<int>(device_max_constant_args)},
                                                                    {DeviceInfoToString(CL_DEVICE_LOCAL_MEM_TYPE), DeviceLocalMemTypeToString(device_local_mem_type)},
                                                                    {DeviceInfoToString(CL_DEVICE_LOCAL_MEM_SIZE), static_cast<int>(device_local_mem_size)},
                                                                    {DeviceInfoToString(CL_DEVICE_ERROR_CORRECTION_SUPPORT), static_cast<bool>(device_error_correction_support)},
                                                                    {DeviceInfoToString(CL_DEVICE_PROFILING_TIMER_RESOLUTION), static_cast<int>(device_profiling_timer_resolution)},
                                                                    {DeviceInfoToString(CL_DEVICE_ENDIAN_LITTLE), static_cast<bool>(device_endian_little)},
                                                                    {DeviceInfoToString(CL_DEVICE_AVAILABLE), static_cast<bool>(device_available)},
                                                                    {DeviceInfoToString(CL_DEVICE_COMPILER_AVAILABLE), static_cast<bool>(device_compiler_available)},
                                                                    {DeviceInfoToString(CL_DEVICE_EXECUTION_CAPABILITIES), DeviceExecCapabilitiesToString(device_execution_capabilities)},
                                                                    {DeviceInfoToString(CL_DEVICE_QUEUE_PROPERTIES), CommandQueuePropertiesToString(device_queue_properties)},
                                                                    //{DeviceInfoToString(CL_DEVICE_PLATFORM), static_cast<int>(device_platform)},
                                                                    {DeviceInfoToString(CL_DEVICE_NAME), device_name.data()},
                                                                    {DeviceInfoToString(CL_DEVICE_VENDOR), device_vendor.data()},
                                                                    {DeviceInfoToString(CL_DRIVER_VERSION), driver_version.data()},
                                                                    {DeviceInfoToString(CL_DEVICE_PROFILE), device_profile.data()},
                                                                    {DeviceInfoToString(CL_DEVICE_VERSION), device_version.data()},
                                                                    {DeviceInfoToString(CL_DEVICE_OPENCL_C_VERSION), device_opencl_c_version.data()},
                                                                    {DeviceInfoToString(CL_DEVICE_EXTENSIONS), device_extensions.data()},
                                                            });

            device_jsons.push_back(device_json);
        }
    }

    devices_json = json11::Json::array(device_jsons);
    platforms_json = json11::Json::array(platform_jsons);

    json11::Json platforms_and_devices_json = json11::Json::object({
                                                                           {"PLATFORMS", platforms_json},
                                                                           {"DEVICES", devices_json},
                                                                   });
    printf("%s\n", platforms_and_devices_json.dump().c_str());

    return 0;
}
