#include <iostream>
#include <vector>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

constexpr unsigned x = 16;

int main() {
    float *hA;
    hipInit(0);
    hipDevice_t device;
    hipCtx_t context;
    hipDeviceGet(&device, 0);
    hipCtxCreate(&context, 0, device);
    hipModule_t Module;
    hipFunction_t Function;
    hipHostMalloc(&hA, sizeof(float) * x);
    for(int i=0;i<x;i++) {
        hA[i] = 0.0f;
    }
    hipModuleLoad(&Module, "for.co");
    hipModuleGetFunction(&Function, Module, "hello_world");
    struct {
        void *Ad;
        unsigned k;
    } args;

    args.Ad = hA;
    args.k = 32;
    size_t size = sizeof(args);

    void *config[] = {
        HIP_LAUNCH_PARAM_BUFFER_POINTER, &args,
        HIP_LAUNCH_PARAM_BUFFER_SIZE, &size,
        HIP_LAUNCH_PARAM_END
    };

    hipModuleLaunchKernel(Function,1,1,1,x,1,1,0,0,NULL,(void**)&config);
    hipDeviceSynchronize();

    for(unsigned i=0;i<x;i++) {
        std::cout<<hA[i]<<" ";
    }

    std::cout<<std::endl;
}
