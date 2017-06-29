#include <OpenCL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

#define ADD_PATH "/Users/vladislavmolcanov/Documents/ITMO/3_course/6_semester/Parallel_programming/Parallel/Parallel/add.cl"
#define MULT_PATH "/Users/vladislavmolcanov/Documents/ITMO/3_course/6_semester/Parallel_programming/Parallel/Parallel/mult.cl"
#define LOCAL_MULT_PATH "/Users/vladislavmolcanov/Documents/ITMO/3_course/6_semester/Parallel_programming/Parallel/Parallel/localmult.cl"

#define ADD_KERNEL "add"
#define MULT_KERNEL "mult"


typedef unsigned int uint;
typedef struct Platform Platform;


struct Platform
{
    char *profile;
    char *version;
    char *name;
    char *vendor;
    char *extensions;
};





cl_platform_id* getPlatformIDs(cl_uint *platformIDsCount)
{
    clGetPlatformIDs(0, NULL, platformIDsCount);
    
    size_t platformsSize = *platformIDsCount * sizeof(cl_platform_id);
    cl_platform_id *platformsIds = (cl_platform_id*) malloc(platformsSize);
    
    clGetPlatformIDs(*platformIDsCount, platformsIds, NULL);
    
    return platformsIds;
}





char* getPlatformInfo(const cl_platform_id platformsIds, const cl_platform_info paramName)
{
    size_t dataSize;
    
    clGetPlatformInfo(platformsIds, paramName, 0, NULL, &dataSize);
    char *paramValue = (char*) malloc(dataSize * sizeof(char));
    clGetPlatformInfo(platformsIds, paramName, dataSize, paramValue, NULL);
    
    return paramValue;
}





cl_device_id* getDeviceIds(cl_uint *deviceIDsCount, const cl_platform_id platform)
{
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, deviceIDsCount);
    cl_device_id *deviceIDs = (cl_device_id*) malloc(*deviceIDsCount * sizeof(cl_device_id));
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, *deviceIDsCount, deviceIDs, NULL);
    
    return deviceIDs;
}





char* getDeviceName(const cl_device_id deviceId)
{
    size_t dataSize;
    
    clGetDeviceInfo(deviceId, CL_DEVICE_NAME, 0, NULL, &dataSize);
    char *deviceName = (char*) malloc(dataSize * sizeof(char));
    clGetDeviceInfo(deviceId, CL_DEVICE_NAME, dataSize, deviceName, NULL);
    
    return deviceName;
}





void error(const char *msg)
{
    printf("%s\n", msg);
    exit(-1);
}





cl_context getContext(const cl_device_id deviceID)
{
    cl_int err;
    cl_context context = clCreateContext(NULL, 1, &deviceID, NULL, NULL, &err);
    
    if (err != 0)
        error("Error: context is not created");
    
    return context;
}





cl_command_queue getQueue(const cl_context context, const cl_device_id deviceID)
{
    cl_int err;
    cl_command_queue queue = clCreateCommandQueue(context,
                                                  deviceID,
                                                  CL_QUEUE_PROFILING_ENABLE,
                                                  &err);
    
    if (err != 0)
        error("Error: queue is not created");
    
    return queue;
}





cl_program getProgram(const char *path, const cl_context context)
{
    cl_int err;
    FILE *sourceFile = fopen(path, "r");
    
    fseek(sourceFile, 0, SEEK_END);
    size_t sourceFileSize = ftell(sourceFile);
    
    fseek(sourceFile, 0, 0);
    const char *sourceCode = (char*) malloc(sourceFileSize * sizeof(char));
    fread((char*)sourceCode, sizeof(char), sourceFileSize, sourceFile);
    
    fclose(sourceFile);
    
    cl_program program = clCreateProgramWithSource(context,
                                                   1,
                                                   &sourceCode,
                                                   &sourceFileSize,
                                                   &err);
    if (err != 0)
        error("Error: program is not created");
    
    return program;
}





void buildProgram(const cl_program program, const cl_device_id deviceID)
{
    cl_int err = clBuildProgram(program, 1, &deviceID, "", NULL, NULL);
    if (err == CL_SUCCESS)
    {
        size_t logSize;
        
        clGetProgramBuildInfo(program, deviceID, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
        
        char *log = (char*) malloc(logSize * sizeof(char));
        
        clGetProgramBuildInfo(program, deviceID, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
        printf("log: %s\n", log);
    }
}





cl_kernel createKernel(const cl_program program, const char *kernelName)
{
    cl_int err;
    cl_kernel kernel = clCreateKernel(program, kernelName, &err);
    
    if (err != 0)
        error("Error: kernel is not created");
    
    return kernel;
}





cl_mem createBuffer(const cl_context context, const size_t size)
{
    cl_int err;
    cl_mem buf = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &err);
    
    if (err != 0)
        error("Error: buffer is not created");
    
    return buf;
}





void enqueueWriteBuffer(const cl_command_queue queue,
                        const cl_mem buf,
                        const size_t size,
                        const int *vector)
{
    clEnqueueWriteBuffer(queue, buf, CL_FALSE, 0, size, vector, 0, NULL, NULL);
}





cl_ulong getTime(cl_event event, cl_profiling_info paramName)
{
    //    size_t size;
    cl_ulong time;
    //    clGetEventProfilingInfo(event, paramName, NULL, &time, &size);
    //    clGetEventProfilingInfo(event, paramName, sizeof(time), &time, NULL);
    
    return time;
}





void mult(const cl_kernel kernel, const cl_command_queue queue, const cl_context context)
{
    const int N = 4;
    const int M = 4;
    const int L = 4;
    
    const cl_mem bufX =      createBuffer(context, N * M * sizeof(int));
    const cl_mem bufY =      createBuffer(context, M * L * sizeof(int));
    const cl_mem bufResult = createBuffer(context, N * L * sizeof(int));
    
    int x[N * M];
    int y[M * L];
    int result[N * L];
    
    // random fill
        for (uint i = 0; i < N; i++)
        {
            for (uint j = 0; j < M; j++)
            {
                x[i * M + j] = rand() % 100 + 1;
            }
        }
        for (uint i = 0; i < M; i++)
        {
            for (uint j = 0; j < L; j++)
            {
                y[i * L + j] = rand() % 100 + 1;
            }
        }
    
    clSetKernelArg(kernel, 0, sizeof(bufX),      &bufX);
    clSetKernelArg(kernel, 1, sizeof(bufY),      &bufY);
    clSetKernelArg(kernel, 2, sizeof(bufResult), &bufResult);
    clSetKernelArg(kernel, 3, sizeof(N),         &N);
    clSetKernelArg(kernel, 4, sizeof(M),         &M);
    clSetKernelArg(kernel, 5, sizeof(L),         &L);
    
    // arguments
    enqueueWriteBuffer(queue, bufX,      N * M * sizeof(int), x);
    enqueueWriteBuffer(queue, bufY,      M * L * sizeof(int), y);
    enqueueWriteBuffer(queue, bufResult, N * L * sizeof(int), result);
    
    const int TREADS_COUNT = 2;
    size_t globalTreads[TREADS_COUNT] = { N, L };
    cl_event event;
    clEnqueueNDRangeKernel(queue, kernel, TREADS_COUNT, 0, globalTreads, NULL, 0, NULL, &event);
    
    clEnqueueReadBuffer(queue, bufResult, CL_TRUE, 0, N * L * sizeof(int), result, 0, NULL, NULL);
    
    // output
    for (uint i = 0; i < N; i++)
    {
        for (uint j = 0; j < L; j++)
        {
            printf("%d ", result[i * L + j]);
        }
        printf("\n");
    }
    
    // calculation of time
    cl_ulong startTime = getTime(event, CL_PROFILING_COMMAND_START);
    cl_ulong finishTime = getTime(event, CL_PROFILING_COMMAND_END);
    cl_ulong processTime = finishTime - startTime;
    printf("\nTime: %llu\n", processTime);
    printf("Flops: %f GFlops\n", (double)N * L * (2 * M - 1) / processTime);
    
    clReleaseMemObject(bufX);
    clReleaseMemObject(bufY);
    clReleaseMemObject(bufResult);
}





int main(void)
{
    cl_uint platformIDsCount;
    cl_platform_id *platformsIds = getPlatformIDs(&platformIDsCount);
    
    Platform *platforms = (Platform*) malloc(platformIDsCount * sizeof(Platform));
    
    for (uint i = 0; i < platformIDsCount; i++)
    {
        platforms[i].profile =    getPlatformInfo(platformsIds[i], CL_PLATFORM_PROFILE);
        platforms[i].version =    getPlatformInfo(platformsIds[i], CL_PLATFORM_VERSION);
        platforms[i].name =       getPlatformInfo(platformsIds[i], CL_PLATFORM_NAME);
        platforms[i].vendor =     getPlatformInfo(platformsIds[i], CL_PLATFORM_VENDOR);
        platforms[i].extensions = getPlatformInfo(platformsIds[i], CL_PLATFORM_EXTENSIONS);
    }
    
    for (uint i = 0; i < platformIDsCount; i++)
    {
        printf("platform[%d]: %s\n", i, platforms[i].profile);
        printf("platform[%d]: %s\n", i, platforms[i].version);
        printf("platform[%d]: %s\n", i, platforms[i].name);
        printf("platform[%d]: %s\n", i, platforms[i].vendor);
        printf("platform[%d]: %s\n\n\n", i, platforms[i].extensions);
    }
    
    cl_uint *deviceIDsCount = (cl_uint*) malloc(platformIDsCount * sizeof(cl_uint));
    cl_device_id **deviceIDs = (cl_device_id**) malloc(platformIDsCount * sizeof(cl_device_id*));
    
    for (uint i = 0; i < platformIDsCount; i++)
    {
        deviceIDs[i] = getDeviceIds(&deviceIDsCount[i], platformsIds[i]);
    }
    
    char ***devicesNames = (char***) malloc(platformIDsCount * sizeof(char**));
    for (uint i = 0; i < platformIDsCount; i++)
    {
        devicesNames[i] = (char**) malloc(deviceIDsCount[i] * sizeof(char*));
    }
    
    for (uint i = 0; i < platformIDsCount; i++)
    {
        for (uint j = 0; j < deviceIDsCount[i]; j++)
        {
            devicesNames[i][j] = getDeviceName(deviceIDs[i][j]);
        }
    }
    
    for (uint i = 0; i < platformIDsCount; i++)
    {
        for (uint j = 0; j < deviceIDsCount[i]; j++)
        {
            printf("%s\n", devicesNames[i][j]);
        }
    }
    
    cl_context context = getContext(deviceIDs[0][0]);
    
    cl_command_queue queue = getQueue(context, deviceIDs[0][0]);
    
    cl_program multKernelProgram = getProgram(MULT_PATH, context);
    
    buildProgram(multKernelProgram, deviceIDs[0][0]);
    
    
    
    /***************************************************************************
     * MAIN
     **************************************************************************/
    
    
    
    cl_kernel multKernel = createKernel(multKernelProgram, MULT_KERNEL);
    
    mult(multKernel, queue, context);
    
    clReleaseKernel(multKernel);
    
    clReleaseProgram(multKernelProgram);
    
    clReleaseContext(context);
    
    return 0;
}
