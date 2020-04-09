## This CMake function is used to dynamically link the input file
## Name : dynamic_link_input
## Params: path to input file
## Output: .so

function(dynamic_link_input
		 base_name 
		 cpp_name 
		 so_name
		 so_includes)
message(INFO "so_name = ${so_name}")
message(INFO "cpp_name = ${cpp_name}")
message(INFO "base_name = ${base_name}")
message(INFO "so_includes = ${so_includes}")

set(SO_LIB_REQS
    ${HMR}-lib
    ${COM}-lib
    ${WRK}-lib
    ${MORIS_PETSC_LIBS}
    ${MORIS_BOOST_LIBS}
    ${MORIS_ACML_LAPACK_MKL_OPENBLAS_LIBS}
#     ${MORIS_MPI_LIBS}
    ${MORIS_ARMADILLO_EIGEN_LIBS}
    ${MORIS_SUPERLU_LIBS}
    ${MORIS_LDLIBS}
    ${MORIS_TRILINOS_LIBS}
    ${MORIS_BASE_LIBS}
    )


add_library(${base_name} SHARED ${cpp_name})
target_include_directories(${base_name} PRIVATE ${SO_INCLUDES})    
target_link_libraries(${base_name} ${SO_LIB_REQS})
target_compile_definitions(${base_name} INTERFACE ${MORIS_DEFINITIONS})                                                                                                                                                                                                       
set_target_properties(${base_name} PROPERTIES OUTPUT_NAME ${base_name})

endfunction()




