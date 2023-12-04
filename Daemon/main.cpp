#define __CL_ENABLE_EXCEPTIONS
#include <CL/opencl.hpp>

int main(int argc, char *argv[]){

    cl::Context context(CL_DEVICE_TYPE_DEFAULT);
    cl::CommandQueue queue(context);
    cl::Program program(context, "", true);

    return 0;
}