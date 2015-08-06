#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <CL/cl.h>
#include <fstream>

int main() {
    const float kBandwidth = 2.0f;
    std::vector<cl_float2> points = {
        {10.91079038931762f,8.3894120169044477f},
        {9.8750016454811416f,9.9092509004598295f},
        {7.8481223001749516f,10.431748303674949f},
        {8.5341229316176186f,9.5590856089969289f},
        {10.383168456491791f,9.6187908570774621f},
        {8.1106159523273558f,9.7747176075388005f},
        {10.021194678890739f,9.5387796220292351f},
        {9.3770585195414959f,9.7085399085745756f},
        {7.6701703352949329f,9.6031523057064874f},
        {10.943082872936237f,11.762073488528063f},
        {9.2473082328068106f,10.902105550317518f},
        {9.5473972897412729f,11.361701761466367f},
        {7.8333436673622323f,10.363033995676176f},
        {10.870459222776201f,9.213348127988457f},
        {8.2285133843786014f,10.467911020064905f},
        {12.482990276816189f,9.4212281474469677f},
        {6.5572296581531369f,11.059353487844673f},
        {7.2642592211498576f,9.9842567369139612f},
        {4.8017215916997493f,7.5579129268206504f},
        {6.8612486478820385f,7.8370069734131782f},
        {13.627244186857192f,10.948300307681397f},
        {13.655256501255671f,9.9249837167692654f},
        {9.6060906991873658f,10.291987945224598f},
        {12.435657157664703f,8.8134392580786756f},
        {10.072065604999597f,9.1605715886878656f},
        {8.3067030281298777f,10.441164603848748f},
        {8.772436599131483f,10.845790913201405f},
        {9.8414161582677995f,9.8483072024049196f},
        {15.111691841743767f,12.489897865895333f},
        {10.277424100451077f,9.8565701101092902f},
        {10.134807602975544f,8.8927749442282966f},
        {8.4265860927835678f,11.300233449798775f},
        {9.191199876775725f,9.9898699491718599f},
        {5.933268578018577f,10.21740003776546f},
        {9.6660554561100884f,10.688149455362304f},
        {5.7620912159378284f,10.12453435639654f},
        {5.224273745954072f,9.9849255904770313f},
        {10.268685374305592f,10.316054753347371f},
        {10.923767076101779f,10.933515119668936f},
        {8.9357996776517705f,9.181397457544719f},
        {2.9782144270032109f,3.8354704347019952f},
        {4.9174420096569609f,2.6743399911354335f},
        {3.0245572560941096f,4.80750921258515f},
        {3.0192261574192036f,4.0418118812507169f},
        {4.1315215453218732f,2.5206046528572816f},
        {0.41134584239056782f,3.655696596939725f},
        {5.2664435674092225f,5.5948820412037197f},
        {4.6235409897637085f,1.3759190611881271f},
        {5.6786434200947413f,2.7579731226577313f},
        {3.9054627121390175f,2.1416250788315363f},
        {8.0853526460883955f,2.5883371297676727f},
        {6.8520355834556366f,3.6103190528792766f},
        {4.2308466631394683f,3.5633771154938372f},
        {6.0429053248443729f,2.3588868528912594f},
        {4.2007728899791053f,2.3823879459798203f},
        {4.2840378930654133f,7.0511425527350866f},
        {3.8206408839932244f,4.6073850522736173f},
        {5.4176851106148423f,3.4363391644029351f},
        {8.2114630301315117f,3.5706098853491399f},
        {6.5430955441931129f,-0.15007118536956821f},
        {9.2172488607385894f,2.4019367504963922f},
        {6.6730381024092011f,3.3076125390184363f},
        {4.043040860929537f,4.8498363880848245f},
        {3.7041032664462255f,2.2526297941030902f},
        {4.9081622710571251f,3.8703906812050439f},
        {5.656217904432566f,2.2435522745351482f},
        {5.0917970663533181f,3.5095001337758487f},
        {6.334045597831155f,3.517609974216283f},
        {6.8205875674927334f,3.871837205598184f},
        {7.2094404370342788f,2.8531108870521447f},
        {2.0997237752780311f,2.2560279923847917f},
        {4.7202055872439743f,2.6207007161418723f},
        {6.2219865739446796f,4.6651911155018073f},
        {5.0769925338297881f,2.3590399274401812f},
        {3.2630277690380556f,0.65206989910121349f},
        {3.6392194745531983f,2.0504866855077974f},
        {7.2501132055579918f,2.6331909348456235f},
        {4.2869377402538857f,0.74184103396503032f},
        {4.4891766334584409f,1.8473897844375247f},
        {6.2234763142026619f,2.226009921680304f},
        {2.7326843843717614f,4.02671123644833f},
        {6.7041261547308046f,1.2413786866869945f},
        {6.4067309223606088f,6.4308164268410692f},
        {3.0821624446670679f,3.6035317581130513f},
        {3.7194311239776887f,5.345215168143298f},
        {6.190401932612164f,6.9225942411420576f},
        {8.1018832467977369f,4.2838830625944286f},
        {2.6667381509229711f,1.2512486723265959f},
        {5.1562537071314836f,2.9578251206128776f},
        {6.8322086640419437f,3.0047411942450042f},
        {-1.5236684825741538f,6.8709391759421514f},
        {-6.2780454543447775f,5.0545207505005338f},
        {-4.1300898667418302f,3.3089677763715279f},
        {-2.298773883120611f,2.5243375533828245f},
        {-0.18637298645602085f,5.059834391378498f},
        {-5.1840778445536886f,5.3276147704699222f},
        {-5.2606186558919212f,6.3733369937801498f},
        {-4.0679106911345349f,4.5645019898631807f},
        {-4.8563984442990948f,3.9437116901867326f},
        {-5.169024045849862f,7.1996507954789211f},
        {-2.8187170159076471f,6.7754752644632017f},
        {-3.013197129388995f,5.3073726666286722f},
        {-1.8402582226879556f,2.4730162158653011f},
        {-3.8060164949652995f,3.0993836417365723f},
        {-1.3538731975579088f,4.6000878698600136f},
        {-5.4228296068901809f,5.5406320643563971f},
        {-3.5718995489738825f,6.3905298035588247f},
        {-4.0379782733195757f,4.7056809900741836f},
        {-1.110354346282433f,4.8094055369659765f},
        {-3.8378779004609926f,6.0290987530782898f},
        {-6.5503857799488543f,5.5118092525106581f},
        {-5.8163449709681689f,7.8139376678657921f},
        {-4.6268949267968766f,8.9798801775265158f},
        {-3.2307793551051933f,3.2955805817816426f},
        {-4.3335692243804544f,5.5933643385669578f},
        {-3.2828968288374156f,6.5901857967844855f},
        {-7.6468921093719153f,7.527347420982772f},
        {-6.4618228471303887f,5.6294483598572249f},
        {-6.3682164249984439f,7.083861848873501f},
        {-4.28475872927197f,3.8425763273570248f},
        {-2.2962665903547554f,7.2885769990473017f},
        {1.1012781986923459f,6.5487961272094948f},
        {-5.9279427268249059f,8.6550877749077486f},
        {-3.9546023112993969f,5.7336401880655785f},
        {-3.1608765392801774f,4.2674094149250283f}
    };

    printf("Original points\n");
    for (int i = 0; i < points.size(); ++i) {
        printf("[%d] = %f, %f\n", i, points[i].s[0], points[i].s[1]);
    }

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

    std::vector<size_t> global_work_size = {kNumberOfPoints};

    const float kEpsilon = 1e-2;
    float difference_distance = 0.0f;

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
    } while (difference_distance > kEpsilon);

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

    printf("Shifted points\n");
    for (int i = 0; i < points.size(); ++i) {
        printf("[%d] = %f, %f\n", i, points[i].s[0], points[i].s[1]);
    }

    return 0;
}

