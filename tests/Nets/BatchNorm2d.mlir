#map = affine_map<(d0, d1, d2, d3) -> (d0, d1, d2, d3)>
#map1 = affine_map<(d0, d1, d2, d3) -> (d1)>
module attributes {torch.debug_module_name = "net_bached_bacthnorm2d"} {
  ml_program.global private mutable @global_seed(dense<0> : tensor<i64>) : tensor<i64>
  func.func @forward(%arg0: tensor<1x3x224x224xf32>) -> tensor<1x3x224x224xf32> {
    %false = arith.constant false
    %cst = arith.constant dense<1.000000e+00> : tensor<3xf32>
    %cst_0 = arith.constant dense<0.000000e+00> : tensor<3xf32>
    %cst_1 = arith.constant 1.000000e-05 : f64
    %0 = arith.cmpi eq, %false, %false : i1
    cf.assert %0, "training is not supported for now"
    %1 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%arg0, %cst, %cst_0, %cst_0, %cst : tensor<1x3x224x224xf32>, tensor<3xf32>, tensor<3xf32>, tensor<3xf32>, tensor<3xf32>) outs(%arg0 : tensor<1x3x224x224xf32>) {
    ^bb0(%in: f32, %in_2: f32, %in_3: f32, %in_4: f32, %in_5: f32, %out: f32):
      %2 = arith.truncf %cst_1 : f64 to f32
      %3 = arith.addf %in_5, %2 : f32
      %4 = math.rsqrt %3 : f32
      %5 = arith.subf %in, %in_4 : f32
      %6 = arith.mulf %5, %4 : f32
      %7 = arith.mulf %6, %in_2 : f32
      %8 = arith.addf %7, %in_3 : f32
      linalg.yield %8 : f32
    } -> tensor<1x3x224x224xf32>
    return %1 : tensor<1x3x224x224xf32>
  }
}
