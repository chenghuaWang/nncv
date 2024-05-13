mlir-translate -mlir-to-llvmir res.mlir -o res18.ll
llc -filetype=obj res18.ll -o libres18.o
clang++ main.cpp libres18.o -no-pie -O3 -lmlir_runner_utils -lmlir_c_runner_utils -lomp -L. -lnncv_rt -I./third_party/stb_image
