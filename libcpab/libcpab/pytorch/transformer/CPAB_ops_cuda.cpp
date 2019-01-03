#include <torch/torch.h>

// Cuda forward declaration
at::Tensor cpab_cuda_forward(at::Tensor points_in, at::Tensor trels_in,  
                             at::Tensor nstepsolver_in, at::Tensor nc_in, 
														 at::Tensor output);
at::Tensor cpab_cuda_backward(at::Tensor points_in, at::Tensor As_in, 
                              at::Tensor Bs_in, at::Tensor nstepsolver_in,
                              at::Tensor nc, at::Tensor output);
                              
// Shortcuts for checking
#define CHECK_CUDA(x) AT_ASSERTM(x.type().is_cuda(), #x " must be a CUDA tensor")
#define CHECK_CONTIGUOUS(x) AT_ASSERTM(x.is_contiguous(), #x " must be contiguous")
#define CHECK_INPUT(x) CHECK_CUDA(x); CHECK_CONTIGUOUS(x)

// Function declaration
at::Tensor cpab_forward(at::Tensor points_in, //[ndim, n_points]
                        at::Tensor trels_in,  //[batch_size, nC, ndim, ndim+1]
                        at::Tensor nstepsolver_in, // scalar
                        at::Tensor nc_in){ // ndim length tensor
    // Do input checking
    CHECK_INPUT(points_in);
    CHECK_INPUT(trels_in);
    CHECK_INPUT(nstepsolver_in);
    CHECK_INPUT(nc_in);
    
		// Problem size
    const auto ndim = points_in.size(0);
    const auto nP = points_in.size(1);
    const auto batch_size = trels_in.size(0);

    // Allocate output
    auto output = at::zeros(torch::CUDA(at::kFloat), {batch_size, ndim, nP}); // [batch_size, ndim, nP]   

    // Call kernel launcher
    return cpab_cuda_forward(points_in, trels_in, nstepsolver_in, nc_in, output);
}

at::Tensor cpab_backward(at::Tensor points_in, // [ndim, nP]
                         at::Tensor As_in, // [n_theta, nC, ndim, ndim+1]
                         at::Tensor Bs_in, // [d, nC, ndim, ndim+1]
                         at::Tensor nstepsolver_in, // scalar
                         at::Tensor nc_in){ // ndim length tensor
    // Do input checking
    CHECK_INPUT(points_in);
    CHECK_INPUT(As_in);
    CHECK_INPUT(Bs_in);
    CHECK_INPUT(nstepsolver_in);
    CHECK_INPUT(nc_in);

		// Problem size
    const auto n_theta = As_in.size(0);
    const auto d = Bs_in.size(0);
    const auto ndim = points_in.size(0);
    const auto nP = points_in.size(1);
    
    // Allocate output
    auto output = at::zeros(torch::CUDA(at::kFloat), {d, n_theta, ndim, nP});

    // Call kernel launcher
    return cpab_cuda_backward(points_in, As_in, Bs_in, nstepsolver_in, nc_in, output);
}

// Binding
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
    m.def("forward", &cpab_forward, "Cpab transformer forward (CUDA)");
    m.def("backward", &cpab_backward, "Cpab transformer backward (CUDA)");
}
