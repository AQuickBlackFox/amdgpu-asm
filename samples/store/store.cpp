#include <iostream>
#include <vector>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

constexpr unsigned x = 4;
constexpr unsigned y = 4;
constexpr unsigned z = 4;

int main() {
    float *hA;
    hipInit(0);
    hipDevice_t device;
    hipCtx_t context;
    hipDeviceGet(&device, 0);
    hipCtxCreate(&context, 0, device);
    hipModule_t Module;
    hipFunction_t Function;
    hipHostMalloc(&hA, sizeof(float) * x * y * z * x * y * z);
    hipModuleLoad(&Module, "store.co");
    hipModuleGetFunction(&Function, Module, "hello_world");
    struct {
        void *Ad;
    } args;

    args.Ad = hA;
    size_t size = sizeof(args);

    void *config[] = {
        HIP_LAUNCH_PARAM_BUFFER_POINTER, &args,
        HIP_LAUNCH_PARAM_BUFFER_SIZE, &size,
        HIP_LAUNCH_PARAM_END
    };

    hipModuleLaunchKernel(Function,x,y,z,x,y,z,0,0,NULL,(void**)&config);
    hipDeviceSynchronize();
    for(int bz=0;bz<z;bz++) {
        for(int by=0;by<y;by++) {
            for(int bx=0;bx<x;bx++) {
                for(int tz=0;tz<z;tz++) {
                    for(int ty=0;ty<y;ty++) {
                        for(int tx=0;tx<x;tx++) {
                            std::cout<<hA[tx + ty * 4 + tz * 4 * 4 + bx * 4 * 4 * 4 + by * 4 * 4 * 4 * 4 + bz * 4 * 4 * 4 * 4 * 4]<<" ";
                        }
                    }
                }
                std::cout<<std::endl;
            }
        }
    }
}
