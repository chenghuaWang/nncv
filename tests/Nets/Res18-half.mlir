#map = affine_map<(d0, d1, d2, d3) -> (d0, d1, d2, d3)>
#map1 = affine_map<(d0, d1, d2, d3) -> (d1)>
#map2 = affine_map<(d0, d1, d2, d3) -> (0, d1, d2, d3)>
#map3 = affine_map<(d0, d1) -> (d0, d1)>
#map4 = affine_map<(d0, d1) -> (d1, d0)>
#map5 = affine_map<(d0, d1) -> (0, d1)>
#map6 = affine_map<(d0, d1) -> (d1)>
module attributes {torch.debug_module_name = "ResNet"} {
  ml_program.global private mutable @global_seed(dense<0> : tensor<i64>) : tensor<i64>
  func.func @forward(%arg0: tensor<1x3x256x256xf16>) -> tensor<1x1000xf16> {
    %false = arith.constant false
    %cst = arith.constant dense_resource<__elided__> : tensor<1000xf16>
    %cst_0 = arith.constant dense_resource<__elided__> : tensor<1000x512xf16>
    %cst_1 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_2 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_3 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_4 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_5 = arith.constant dense_resource<__elided__> : tensor<512x512x3x3xf16>
    %cst_6 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_7 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_8 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_9 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_10 = arith.constant dense_resource<__elided__> : tensor<512x512x3x3xf16>
    %cst_11 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_12 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_13 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_14 = arith.constant dense_resource<__elided__> : tensor<512x256x1x1xf16>
    %cst_15 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_16 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_17 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_18 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_19 = arith.constant dense_resource<__elided__> : tensor<512x512x3x3xf16>
    %cst_20 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_21 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_22 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_23 = arith.constant dense_resource<__elided__> : tensor<512xf16>
    %cst_24 = arith.constant dense_resource<__elided__> : tensor<512x256x3x3xf16>
    %cst_25 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_26 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_27 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_28 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_29 = arith.constant dense_resource<__elided__> : tensor<256x256x3x3xf16>
    %cst_30 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_31 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_32 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_33 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_34 = arith.constant dense_resource<__elided__> : tensor<256x256x3x3xf16>
    %cst_35 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_36 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_37 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_38 = arith.constant dense_resource<__elided__> : tensor<256x128x1x1xf16>
    %cst_39 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_40 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_41 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_42 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_43 = arith.constant dense_resource<__elided__> : tensor<256x256x3x3xf16>
    %cst_44 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_45 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_46 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_47 = arith.constant dense_resource<__elided__> : tensor<256xf16>
    %cst_48 = arith.constant dense_resource<__elided__> : tensor<256x128x3x3xf16>
    %cst_49 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_50 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_51 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_52 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_53 = arith.constant dense_resource<__elided__> : tensor<128x128x3x3xf16>
    %cst_54 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_55 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_56 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_57 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_58 = arith.constant dense_resource<__elided__> : tensor<128x128x3x3xf16>
    %cst_59 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_60 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_61 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_62 = arith.constant dense_resource<__elided__> : tensor<128x64x1x1xf16>
    %cst_63 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_64 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_65 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_66 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_67 = arith.constant dense_resource<__elided__> : tensor<128x128x3x3xf16>
    %cst_68 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_69 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_70 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_71 = arith.constant dense_resource<__elided__> : tensor<128xf16>
    %cst_72 = arith.constant dense_resource<__elided__> : tensor<128x64x3x3xf16>
    %cst_73 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_74 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_75 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_76 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_77 = arith.constant dense_resource<__elided__> : tensor<64x64x3x3xf16>
    %cst_78 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_79 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_80 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_81 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_82 = arith.constant dense_resource<__elided__> : tensor<64x64x3x3xf16>
    %cst_83 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_84 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_85 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_86 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_87 = arith.constant dense_resource<__elided__> : tensor<64x64x3x3xf16>
    %cst_88 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_89 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_90 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_91 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_92 = arith.constant dense_resource<__elided__> : tensor<64x64x3x3xf16>
    %cst_93 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_94 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_95 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_96 = arith.constant dense_resource<__elided__> : tensor<64xf16>
    %cst_97 = arith.constant dense_resource<__elided__> : tensor<64x3x7x7xf16>
    %cst_98 = arith.constant 0.000000e+00 : f16
    %cst_99 = arith.constant 0xFC00 : f16
    %cst_100 = arith.constant 1.000000e-05 : f64
    %c3 = arith.constant 3 : index
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %cst_101 = arith.constant 6.400000e+01 : f16
    %padded = tensor.pad %arg0 low[0, 0, 3, 3] high[0, 0, 3, 3] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x3x256x256xf16> to tensor<1x3x262x262xf16>
    %0 = tensor.empty() : tensor<1x64x128x128xf16>
    %1 = linalg.fill ins(%cst_98 : f16) outs(%0 : tensor<1x64x128x128xf16>) -> tensor<1x64x128x128xf16>
    %2 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded, %cst_97 : tensor<1x3x262x262xf16>, tensor<64x3x7x7xf16>) outs(%1 : tensor<1x64x128x128xf16>) -> tensor<1x64x128x128xf16>
    %3 = arith.cmpi eq, %false, %false : i1
    cf.assert %3, "training is not supported for now"
    %4 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%2, %cst_94, %cst_93, %cst_96, %cst_95 : tensor<1x64x128x128xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>) outs(%2 : tensor<1x64x128x128xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x64x128x128xf16>
    %5 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%4 : tensor<1x64x128x128xf16>) outs(%0 : tensor<1x64x128x128xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x64x128x128xf16>
    %padded_102 = tensor.pad %5 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_99 : f16
    } : tensor<1x64x128x128xf16> to tensor<1x64x130x130xf16>
    %6 = tensor.empty() : tensor<1x64x64x64xf16>
    %7 = linalg.fill ins(%cst_99 : f16) outs(%6 : tensor<1x64x64x64xf16>) -> tensor<1x64x64x64xf16>
    %8 = tensor.empty() : tensor<3x3xf16>
    %9 = linalg.pooling_nchw_max {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_102, %8 : tensor<1x64x130x130xf16>, tensor<3x3xf16>) outs(%7 : tensor<1x64x64x64xf16>) -> tensor<1x64x64x64xf16>
    %padded_103 = tensor.pad %9 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x64x64x64xf16> to tensor<1x64x66x66xf16>
    %10 = linalg.fill ins(%cst_98 : f16) outs(%6 : tensor<1x64x64x64xf16>) -> tensor<1x64x64x64xf16>
    %11 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_103, %cst_92 : tensor<1x64x66x66xf16>, tensor<64x64x3x3xf16>) outs(%10 : tensor<1x64x64x64xf16>) -> tensor<1x64x64x64xf16>
    cf.assert %3, "training is not supported for now"
    %12 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%11, %cst_89, %cst_88, %cst_91, %cst_90 : tensor<1x64x64x64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>) outs(%11 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x64x64x64xf16>
    %13 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%12 : tensor<1x64x64x64xf16>) outs(%6 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x64x64x64xf16>
    %padded_104 = tensor.pad %13 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x64x64x64xf16> to tensor<1x64x66x66xf16>
    %14 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_104, %cst_87 : tensor<1x64x66x66xf16>, tensor<64x64x3x3xf16>) outs(%10 : tensor<1x64x64x64xf16>) -> tensor<1x64x64x64xf16>
    cf.assert %3, "training is not supported for now"
    %15 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%14, %cst_84, %cst_83, %cst_86, %cst_85 : tensor<1x64x64x64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>) outs(%14 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x64x64x64xf16>
    %16 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%15, %9 : tensor<1x64x64x64xf16>, tensor<1x64x64x64xf16>) outs(%6 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x64x64x64xf16>
    %17 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%16 : tensor<1x64x64x64xf16>) outs(%6 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x64x64x64xf16>
    %padded_105 = tensor.pad %17 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x64x64x64xf16> to tensor<1x64x66x66xf16>
    %18 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_105, %cst_82 : tensor<1x64x66x66xf16>, tensor<64x64x3x3xf16>) outs(%10 : tensor<1x64x64x64xf16>) -> tensor<1x64x64x64xf16>
    cf.assert %3, "training is not supported for now"
    %19 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%18, %cst_79, %cst_78, %cst_81, %cst_80 : tensor<1x64x64x64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>) outs(%18 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x64x64x64xf16>
    %20 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%19 : tensor<1x64x64x64xf16>) outs(%6 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x64x64x64xf16>
    %padded_106 = tensor.pad %20 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x64x64x64xf16> to tensor<1x64x66x66xf16>
    %21 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_106, %cst_77 : tensor<1x64x66x66xf16>, tensor<64x64x3x3xf16>) outs(%10 : tensor<1x64x64x64xf16>) -> tensor<1x64x64x64xf16>
    cf.assert %3, "training is not supported for now"
    %22 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%21, %cst_74, %cst_73, %cst_76, %cst_75 : tensor<1x64x64x64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>, tensor<64xf16>) outs(%21 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x64x64x64xf16>
    %23 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%22, %17 : tensor<1x64x64x64xf16>, tensor<1x64x64x64xf16>) outs(%6 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x64x64x64xf16>
    %24 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%23 : tensor<1x64x64x64xf16>) outs(%6 : tensor<1x64x64x64xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x64x64x64xf16>
    %padded_107 = tensor.pad %24 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x64x64x64xf16> to tensor<1x64x66x66xf16>
    %25 = tensor.empty() : tensor<1x128x32x32xf16>
    %26 = linalg.fill ins(%cst_98 : f16) outs(%25 : tensor<1x128x32x32xf16>) -> tensor<1x128x32x32xf16>
    %27 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_107, %cst_72 : tensor<1x64x66x66xf16>, tensor<128x64x3x3xf16>) outs(%26 : tensor<1x128x32x32xf16>) -> tensor<1x128x32x32xf16>
    cf.assert %3, "training is not supported for now"
    %28 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%27, %cst_69, %cst_68, %cst_71, %cst_70 : tensor<1x128x32x32xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>) outs(%27 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x128x32x32xf16>
    %29 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%28 : tensor<1x128x32x32xf16>) outs(%25 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x128x32x32xf16>
    %padded_108 = tensor.pad %29 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x128x32x32xf16> to tensor<1x128x34x34xf16>
    %30 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_108, %cst_67 : tensor<1x128x34x34xf16>, tensor<128x128x3x3xf16>) outs(%26 : tensor<1x128x32x32xf16>) -> tensor<1x128x32x32xf16>
    cf.assert %3, "training is not supported for now"
    %31 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%30, %cst_64, %cst_63, %cst_66, %cst_65 : tensor<1x128x32x32xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>) outs(%30 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x128x32x32xf16>
    %32 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%24, %cst_62 : tensor<1x64x64x64xf16>, tensor<128x64x1x1xf16>) outs(%26 : tensor<1x128x32x32xf16>) -> tensor<1x128x32x32xf16>
    cf.assert %3, "training is not supported for now"
    %33 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%32, %cst_59, %cst_63, %cst_61, %cst_60 : tensor<1x128x32x32xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>) outs(%32 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x128x32x32xf16>
    %34 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%31, %33 : tensor<1x128x32x32xf16>, tensor<1x128x32x32xf16>) outs(%25 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x128x32x32xf16>
    %35 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%34 : tensor<1x128x32x32xf16>) outs(%25 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x128x32x32xf16>
    %padded_109 = tensor.pad %35 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x128x32x32xf16> to tensor<1x128x34x34xf16>
    %36 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_109, %cst_58 : tensor<1x128x34x34xf16>, tensor<128x128x3x3xf16>) outs(%26 : tensor<1x128x32x32xf16>) -> tensor<1x128x32x32xf16>
    cf.assert %3, "training is not supported for now"
    %37 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %cst_55, %cst_54, %cst_57, %cst_56 : tensor<1x128x32x32xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>) outs(%36 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x128x32x32xf16>
    %38 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%37 : tensor<1x128x32x32xf16>) outs(%25 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x128x32x32xf16>
    %padded_110 = tensor.pad %38 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x128x32x32xf16> to tensor<1x128x34x34xf16>
    %39 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_110, %cst_53 : tensor<1x128x34x34xf16>, tensor<128x128x3x3xf16>) outs(%26 : tensor<1x128x32x32xf16>) -> tensor<1x128x32x32xf16>
    cf.assert %3, "training is not supported for now"
    %40 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%39, %cst_50, %cst_49, %cst_52, %cst_51 : tensor<1x128x32x32xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>, tensor<128xf16>) outs(%39 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x128x32x32xf16>
    %41 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%40, %35 : tensor<1x128x32x32xf16>, tensor<1x128x32x32xf16>) outs(%25 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x128x32x32xf16>
    %42 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%41 : tensor<1x128x32x32xf16>) outs(%25 : tensor<1x128x32x32xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x128x32x32xf16>
    %padded_111 = tensor.pad %42 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x128x32x32xf16> to tensor<1x128x34x34xf16>
    %43 = tensor.empty() : tensor<1x256x16x16xf16>
    %44 = linalg.fill ins(%cst_98 : f16) outs(%43 : tensor<1x256x16x16xf16>) -> tensor<1x256x16x16xf16>
    %45 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_111, %cst_48 : tensor<1x128x34x34xf16>, tensor<256x128x3x3xf16>) outs(%44 : tensor<1x256x16x16xf16>) -> tensor<1x256x16x16xf16>
    cf.assert %3, "training is not supported for now"
    %46 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%45, %cst_45, %cst_44, %cst_47, %cst_46 : tensor<1x256x16x16xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>) outs(%45 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x256x16x16xf16>
    %47 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%46 : tensor<1x256x16x16xf16>) outs(%43 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x256x16x16xf16>
    %padded_112 = tensor.pad %47 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x256x16x16xf16> to tensor<1x256x18x18xf16>
    %48 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_112, %cst_43 : tensor<1x256x18x18xf16>, tensor<256x256x3x3xf16>) outs(%44 : tensor<1x256x16x16xf16>) -> tensor<1x256x16x16xf16>
    cf.assert %3, "training is not supported for now"
    %49 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%48, %cst_40, %cst_39, %cst_42, %cst_41 : tensor<1x256x16x16xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>) outs(%48 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x256x16x16xf16>
    %50 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%42, %cst_38 : tensor<1x128x32x32xf16>, tensor<256x128x1x1xf16>) outs(%44 : tensor<1x256x16x16xf16>) -> tensor<1x256x16x16xf16>
    cf.assert %3, "training is not supported for now"
    %51 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%50, %cst_35, %cst_39, %cst_37, %cst_36 : tensor<1x256x16x16xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>) outs(%50 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x256x16x16xf16>
    %52 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%49, %51 : tensor<1x256x16x16xf16>, tensor<1x256x16x16xf16>) outs(%43 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x256x16x16xf16>
    %53 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%52 : tensor<1x256x16x16xf16>) outs(%43 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x256x16x16xf16>
    %padded_113 = tensor.pad %53 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x256x16x16xf16> to tensor<1x256x18x18xf16>
    %54 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_113, %cst_34 : tensor<1x256x18x18xf16>, tensor<256x256x3x3xf16>) outs(%44 : tensor<1x256x16x16xf16>) -> tensor<1x256x16x16xf16>
    cf.assert %3, "training is not supported for now"
    %55 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%54, %cst_31, %cst_30, %cst_33, %cst_32 : tensor<1x256x16x16xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>) outs(%54 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x256x16x16xf16>
    %56 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%55 : tensor<1x256x16x16xf16>) outs(%43 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x256x16x16xf16>
    %padded_114 = tensor.pad %56 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x256x16x16xf16> to tensor<1x256x18x18xf16>
    %57 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_114, %cst_29 : tensor<1x256x18x18xf16>, tensor<256x256x3x3xf16>) outs(%44 : tensor<1x256x16x16xf16>) -> tensor<1x256x16x16xf16>
    cf.assert %3, "training is not supported for now"
    %58 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%57, %cst_26, %cst_25, %cst_28, %cst_27 : tensor<1x256x16x16xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>, tensor<256xf16>) outs(%57 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x256x16x16xf16>
    %59 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%58, %53 : tensor<1x256x16x16xf16>, tensor<1x256x16x16xf16>) outs(%43 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x256x16x16xf16>
    %60 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%59 : tensor<1x256x16x16xf16>) outs(%43 : tensor<1x256x16x16xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x256x16x16xf16>
    %padded_115 = tensor.pad %60 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x256x16x16xf16> to tensor<1x256x18x18xf16>
    %61 = tensor.empty() : tensor<1x512x8x8xf16>
    %62 = linalg.fill ins(%cst_98 : f16) outs(%61 : tensor<1x512x8x8xf16>) -> tensor<1x512x8x8xf16>
    %63 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_115, %cst_24 : tensor<1x256x18x18xf16>, tensor<512x256x3x3xf16>) outs(%62 : tensor<1x512x8x8xf16>) -> tensor<1x512x8x8xf16>
    cf.assert %3, "training is not supported for now"
    %64 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%63, %cst_21, %cst_20, %cst_23, %cst_22 : tensor<1x512x8x8xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>) outs(%63 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x512x8x8xf16>
    %65 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%64 : tensor<1x512x8x8xf16>) outs(%61 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x512x8x8xf16>
    %padded_116 = tensor.pad %65 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x512x8x8xf16> to tensor<1x512x10x10xf16>
    %66 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_116, %cst_19 : tensor<1x512x10x10xf16>, tensor<512x512x3x3xf16>) outs(%62 : tensor<1x512x8x8xf16>) -> tensor<1x512x8x8xf16>
    cf.assert %3, "training is not supported for now"
    %67 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%66, %cst_16, %cst_15, %cst_18, %cst_17 : tensor<1x512x8x8xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>) outs(%66 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x512x8x8xf16>
    %68 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%60, %cst_14 : tensor<1x256x16x16xf16>, tensor<512x256x1x1xf16>) outs(%62 : tensor<1x512x8x8xf16>) -> tensor<1x512x8x8xf16>
    cf.assert %3, "training is not supported for now"
    %69 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%68, %cst_11, %cst_15, %cst_13, %cst_12 : tensor<1x512x8x8xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>) outs(%68 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x512x8x8xf16>
    %70 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%67, %69 : tensor<1x512x8x8xf16>, tensor<1x512x8x8xf16>) outs(%61 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x512x8x8xf16>
    %71 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%70 : tensor<1x512x8x8xf16>) outs(%61 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x512x8x8xf16>
    %padded_117 = tensor.pad %71 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x512x8x8xf16> to tensor<1x512x10x10xf16>
    %72 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_117, %cst_10 : tensor<1x512x10x10xf16>, tensor<512x512x3x3xf16>) outs(%62 : tensor<1x512x8x8xf16>) -> tensor<1x512x8x8xf16>
    cf.assert %3, "training is not supported for now"
    %73 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%72, %cst_7, %cst_6, %cst_9, %cst_8 : tensor<1x512x8x8xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>) outs(%72 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x512x8x8xf16>
    %74 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%73 : tensor<1x512x8x8xf16>) outs(%61 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x512x8x8xf16>
    %padded_118 = tensor.pad %74 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_98 : f16
    } : tensor<1x512x8x8xf16> to tensor<1x512x10x10xf16>
    %75 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_118, %cst_5 : tensor<1x512x10x10xf16>, tensor<512x512x3x3xf16>) outs(%62 : tensor<1x512x8x8xf16>) -> tensor<1x512x8x8xf16>
    cf.assert %3, "training is not supported for now"
    %76 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%75, %cst_2, %cst_1, %cst_4, %cst_3 : tensor<1x512x8x8xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>, tensor<512xf16>) outs(%75 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %in_119: f16, %in_120: f16, %in_121: f16, %in_122: f16, %out: f16):
      %90 = arith.truncf %cst_100 : f64 to f16
      %91 = arith.addf %in_122, %90 : f16
      %92 = math.rsqrt %91 : f16
      %93 = arith.subf %in, %in_121 : f16
      %94 = arith.mulf %93, %92 : f16
      %95 = arith.mulf %94, %in_119 : f16
      %96 = arith.addf %95, %in_120 : f16
      linalg.yield %96 : f16
    } -> tensor<1x512x8x8xf16>
    %77 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%76, %71 : tensor<1x512x8x8xf16>, tensor<1x512x8x8xf16>) outs(%61 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x512x8x8xf16>
    %78 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%77 : tensor<1x512x8x8xf16>) outs(%61 : tensor<1x512x8x8xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.cmpf ugt, %in, %cst_98 : f16
      %91 = arith.select %90, %in, %cst_98 : f16
      linalg.yield %91 : f16
    } -> tensor<1x512x8x8xf16>
    %79 = tensor.empty() : tensor<1x512x1x1xf16>
    %80 = linalg.fill ins(%cst_98 : f16) outs(%79 : tensor<1x512x1x1xf16>) -> tensor<1x512x1x1xf16>
    %81 = tensor.empty() : tensor<8x8xf16>
    %82 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%78, %81 : tensor<1x512x8x8xf16>, tensor<8x8xf16>) outs(%80 : tensor<1x512x1x1xf16>) -> tensor<1x512x1x1xf16>
    %83 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%82 : tensor<1x512x1x1xf16>) outs(%79 : tensor<1x512x1x1xf16>) {
    ^bb0(%in: f16, %out: f16):
      %90 = arith.divf %in, %cst_101 : f16
      linalg.yield %90 : f16
    } -> tensor<1x512x1x1xf16>
    %collapsed = tensor.collapse_shape %83 [[0], [1, 2, 3]] : tensor<1x512x1x1xf16> into tensor<1x512xf16>
    %84 = tensor.empty() : tensor<512x1000xf16>
    %85 = linalg.generic {indexing_maps = [#map3, #map4], iterator_types = ["parallel", "parallel"]} ins(%cst_0 : tensor<1000x512xf16>) outs(%84 : tensor<512x1000xf16>) {
    ^bb0(%in: f16, %out: f16):
      linalg.yield %in : f16
    } -> tensor<512x1000xf16>
    %86 = tensor.empty() : tensor<1x1000xf16>
    %87 = linalg.fill ins(%cst_98 : f16) outs(%86 : tensor<1x1000xf16>) -> tensor<1x1000xf16>
    %88 = linalg.matmul ins(%collapsed, %85 : tensor<1x512xf16>, tensor<512x1000xf16>) outs(%87 : tensor<1x1000xf16>) -> tensor<1x1000xf16>
    %89 = linalg.generic {indexing_maps = [#map5, #map6, #map3], iterator_types = ["parallel", "parallel"]} ins(%88, %cst : tensor<1x1000xf16>, tensor<1000xf16>) outs(%86 : tensor<1x1000xf16>) {
    ^bb0(%in: f16, %in_119: f16, %out: f16):
      %90 = arith.addf %in, %in_119 : f16
      linalg.yield %90 : f16
    } -> tensor<1x1000xf16>
    return %89 : tensor<1x1000xf16>
  }
}
