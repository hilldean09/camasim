
add_library( csim_cuda particle_cloud.cu )

target_compile_features( csim_cuda PUBLIC )
set_target_properties( csim_cuda PROPERTIES 
  CUDA_SEPERABLE_COMPILATION ON 
  CUDA_STANDARD 20
  CUDA_STANDARD_REQUIRED ON
)

target_link_libraries( csim_cuda )


