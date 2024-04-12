#map = affine_map<(d0, d1, d2, d3) -> (d0, d1, d2, d3)>
#map1 = affine_map<(d0, d1, d2, d3) -> (d1)>
#map2 = affine_map<(d0, d1, d2, d3) -> (0, d1, d2, d3)>
#map3 = affine_map<() -> ()>
#map4 = affine_map<(d0, d1, d2, d3) -> ()>
#map5 = affine_map<(d0, d1, d2, d3) -> (0, d1, 0, 0)>
#map6 = affine_map<(d0, d1) -> (d0, d1)>
#map7 = affine_map<(d0, d1) -> (d1, d0)>
#map8 = affine_map<(d0, d1) -> (0, d1)>
#map9 = affine_map<(d0, d1) -> (d1)>
#map10 = affine_map<(d0, d1) -> ()>
module attributes {torch.debug_module_name = "MobileNetV3"} {
  ml_program.global private mutable @global_seed(dense<0> : tensor<i64>) : tensor<i64>
  func.func @forward(%arg0: tensor<1x3x256x256xf32>) -> tensor<1x1000xf32> {
    %false = arith.constant false
    %cst = arith.constant dense_resource<__elided__> : tensor<1000xf32>
    %cst_0 = arith.constant dense_resource<__elided__> : tensor<1000x1024xf32>
    %cst_1 = arith.constant dense_resource<__elided__> : tensor<1024xf32>
    %cst_2 = arith.constant dense_resource<__elided__> : tensor<1024x576xf32>
    %cst_3 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_4 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_5 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_6 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_7 = arith.constant dense_resource<__elided__> : tensor<576x96x1x1xf32>
    %cst_8 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_9 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_10 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_11 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_12 = arith.constant dense_resource<__elided__> : tensor<96x576x1x1xf32>
    %cst_13 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_14 = arith.constant dense_resource<__elided__> : tensor<576x144x1x1xf32>
    %cst_15 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_16 = arith.constant dense_resource<__elided__> : tensor<144x576x1x1xf32>
    %cst_17 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_18 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_19 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_20 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_21 = arith.constant dense_resource<__elided__> : tensor<576x1x5x5xf32>
    %cst_22 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_23 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_24 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_25 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_26 = arith.constant dense_resource<__elided__> : tensor<576x96x1x1xf32>
    %cst_27 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_28 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_29 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_30 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_31 = arith.constant dense_resource<__elided__> : tensor<96x576x1x1xf32>
    %cst_32 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_33 = arith.constant dense_resource<__elided__> : tensor<576x144x1x1xf32>
    %cst_34 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_35 = arith.constant dense_resource<__elided__> : tensor<144x576x1x1xf32>
    %cst_36 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_37 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_38 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_39 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_40 = arith.constant dense_resource<__elided__> : tensor<576x1x5x5xf32>
    %cst_41 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_42 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_43 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_44 = arith.constant dense_resource<__elided__> : tensor<576xf32>
    %cst_45 = arith.constant dense_resource<__elided__> : tensor<576x96x1x1xf32>
    %cst_46 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_47 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_48 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_49 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_50 = arith.constant dense_resource<__elided__> : tensor<96x288x1x1xf32>
    %cst_51 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_52 = arith.constant dense_resource<__elided__> : tensor<288x72x1x1xf32>
    %cst_53 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_54 = arith.constant dense_resource<__elided__> : tensor<72x288x1x1xf32>
    %cst_55 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_56 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_57 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_58 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_59 = arith.constant dense_resource<__elided__> : tensor<288x1x5x5xf32>
    %cst_60 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_61 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_62 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_63 = arith.constant dense_resource<__elided__> : tensor<288xf32>
    %cst_64 = arith.constant dense_resource<__elided__> : tensor<288x48x1x1xf32>
    %cst_65 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_66 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_67 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_68 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_69 = arith.constant dense_resource<__elided__> : tensor<48x144x1x1xf32>
    %cst_70 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_71 = arith.constant dense_resource<__elided__> : tensor<144x40x1x1xf32>
    %cst_72 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_73 = arith.constant dense_resource<__elided__> : tensor<40x144x1x1xf32>
    %cst_74 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_75 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_76 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_77 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_78 = arith.constant dense_resource<__elided__> : tensor<144x1x5x5xf32>
    %cst_79 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_80 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_81 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_82 = arith.constant dense_resource<__elided__> : tensor<144xf32>
    %cst_83 = arith.constant dense_resource<__elided__> : tensor<144x48x1x1xf32>
    %cst_84 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_85 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_86 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_87 = arith.constant dense_resource<__elided__> : tensor<48xf32>
    %cst_88 = arith.constant dense_resource<__elided__> : tensor<48x120x1x1xf32>
    %cst_89 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_90 = arith.constant dense_resource<__elided__> : tensor<120x32x1x1xf32>
    %cst_91 = arith.constant dense_resource<__elided__> : tensor<32xf32>
    %cst_92 = arith.constant dense_resource<__elided__> : tensor<32x120x1x1xf32>
    %cst_93 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_94 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_95 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_96 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_97 = arith.constant dense_resource<__elided__> : tensor<120x1x5x5xf32>
    %cst_98 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_99 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_100 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_101 = arith.constant dense_resource<__elided__> : tensor<120xf32>
    %cst_102 = arith.constant dense_resource<__elided__> : tensor<120x40x1x1xf32>
    %cst_103 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_104 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_105 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_106 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_107 = arith.constant dense_resource<__elided__> : tensor<40x240x1x1xf32>
    %cst_108 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_109 = arith.constant dense_resource<__elided__> : tensor<240x64x1x1xf32>
    %cst_110 = arith.constant dense_resource<__elided__> : tensor<64xf32>
    %cst_111 = arith.constant dense_resource<__elided__> : tensor<64x240x1x1xf32>
    %cst_112 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_113 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_114 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_115 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_116 = arith.constant dense_resource<__elided__> : tensor<240x1x5x5xf32>
    %cst_117 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_118 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_119 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_120 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_121 = arith.constant dense_resource<__elided__> : tensor<240x40x1x1xf32>
    %cst_122 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_123 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_124 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_125 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_126 = arith.constant dense_resource<__elided__> : tensor<40x240x1x1xf32>
    %cst_127 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_128 = arith.constant dense_resource<__elided__> : tensor<240x64x1x1xf32>
    %cst_129 = arith.constant dense_resource<__elided__> : tensor<64xf32>
    %cst_130 = arith.constant dense_resource<__elided__> : tensor<64x240x1x1xf32>
    %cst_131 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_132 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_133 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_134 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_135 = arith.constant dense_resource<__elided__> : tensor<240x1x5x5xf32>
    %cst_136 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_137 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_138 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_139 = arith.constant dense_resource<__elided__> : tensor<240xf32>
    %cst_140 = arith.constant dense_resource<__elided__> : tensor<240x40x1x1xf32>
    %cst_141 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_142 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_143 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_144 = arith.constant dense_resource<__elided__> : tensor<40xf32>
    %cst_145 = arith.constant dense_resource<__elided__> : tensor<40x96x1x1xf32>
    %cst_146 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_147 = arith.constant dense_resource<__elided__> : tensor<96x24x1x1xf32>
    %cst_148 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_149 = arith.constant dense_resource<__elided__> : tensor<24x96x1x1xf32>
    %cst_150 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_151 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_152 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_153 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_154 = arith.constant dense_resource<__elided__> : tensor<96x1x5x5xf32>
    %cst_155 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_156 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_157 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_158 = arith.constant dense_resource<__elided__> : tensor<96xf32>
    %cst_159 = arith.constant dense_resource<__elided__> : tensor<96x24x1x1xf32>
    %cst_160 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_161 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_162 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_163 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_164 = arith.constant dense_resource<__elided__> : tensor<24x88x1x1xf32>
    %cst_165 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_166 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_167 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_168 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_169 = arith.constant dense_resource<__elided__> : tensor<88x1x3x3xf32>
    %cst_170 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_171 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_172 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_173 = arith.constant dense_resource<__elided__> : tensor<88xf32>
    %cst_174 = arith.constant dense_resource<__elided__> : tensor<88x24x1x1xf32>
    %cst_175 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_176 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_177 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_178 = arith.constant dense_resource<__elided__> : tensor<24xf32>
    %cst_179 = arith.constant dense_resource<__elided__> : tensor<24x72x1x1xf32>
    %cst_180 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_181 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_182 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_183 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_184 = arith.constant dense_resource<__elided__> : tensor<72x1x3x3xf32>
    %cst_185 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_186 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_187 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_188 = arith.constant dense_resource<__elided__> : tensor<72xf32>
    %cst_189 = arith.constant dense_resource<__elided__> : tensor<72x16x1x1xf32>
    %cst_190 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_191 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_192 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_193 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_194 = arith.constant dense_resource<__elided__> : tensor<16x16x1x1xf32>
    %cst_195 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_196 = arith.constant dense_resource<__elided__> : tensor<16x8x1x1xf32>
    %cst_197 = arith.constant dense_resource<__elided__> : tensor<8xf32>
    %cst_198 = arith.constant dense_resource<__elided__> : tensor<8x16x1x1xf32>
    %cst_199 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_200 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_201 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_202 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_203 = arith.constant dense_resource<__elided__> : tensor<16x1x3x3xf32>
    %cst_204 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_205 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_206 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_207 = arith.constant dense_resource<__elided__> : tensor<16xf32>
    %cst_208 = arith.constant dense_resource<__elided__> : tensor<16x3x3x3xf32>
    %cst_209 = arith.constant 0.000000e+00 : f32
    %c6_i64 = arith.constant 6 : i64
    %cst_210 = arith.constant 1.000000e-03 : f64
    %cst_211 = arith.constant 3.000000e+00 : f32
    %cst_212 = arith.constant 6.000000e+00 : f32
    %cst_213 = arith.constant 4.096000e+03 : f32
    %cst_214 = arith.constant 2.560000e+02 : f32
    %c2 = arith.constant 2 : index
    %c0 = arith.constant 0 : index
    %c0_i64 = arith.constant 0 : i64
    %c1_i64 = arith.constant 1 : i64
    %c1 = arith.constant 1 : index
    %cst_215 = arith.constant 6.400000e+01 : f32
    %padded = tensor.pad %arg0 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x3x256x256xf32> to tensor<1x3x258x258xf32>
    %0 = tensor.empty() : tensor<1x16x128x128xf32>
    %1 = linalg.fill ins(%cst_209 : f32) outs(%0 : tensor<1x16x128x128xf32>) -> tensor<1x16x128x128xf32>
    %2 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded, %cst_208 : tensor<1x3x258x258xf32>, tensor<16x3x3x3xf32>) outs(%1 : tensor<1x16x128x128xf32>) -> tensor<1x16x128x128xf32>
    %3 = arith.cmpi eq, %false, %false : i1
    cf.assert %3, "training is not supported for now"
    %4 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%2, %cst_205, %cst_204, %cst_207, %cst_206 : tensor<1x16x128x128xf32>, tensor<16xf32>, tensor<16xf32>, tensor<16xf32>, tensor<16xf32>) outs(%2 : tensor<1x16x128x128xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x16x128x128xf32>
    %5 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%4 : tensor<1x16x128x128xf32>) outs(%0 : tensor<1x16x128x128xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x16x128x128xf32>
    %6 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%5 : tensor<1x16x128x128xf32>) outs(%0 : tensor<1x16x128x128xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x16x128x128xf32>
    %7 = tensor.empty() : tensor<i64>
    %8 = linalg.fill ins(%c6_i64 : i64) outs(%7 : tensor<i64>) -> tensor<i64>
    %9 = tensor.empty() : tensor<f32>
    %10 = linalg.generic {indexing_maps = [#map3, #map3], iterator_types = []} ins(%8 : tensor<i64>) outs(%9 : tensor<f32>) {
    ^bb0(%in: i64, %out: f32):
      %362 = arith.sitofp %in : i64 to f32
      linalg.yield %362 : f32
    } -> tensor<f32>
    %11 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%6, %10 : tensor<1x16x128x128xf32>, tensor<f32>) outs(%0 : tensor<1x16x128x128xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x16x128x128xf32>
    %12 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%11 : tensor<1x16x128x128xf32>) outs(%0 : tensor<1x16x128x128xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x16x128x128xf32>
    %13 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%12, %4 : tensor<1x16x128x128xf32>, tensor<1x16x128x128xf32>) outs(%0 : tensor<1x16x128x128xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x16x128x128xf32>
    %padded_216 = tensor.pad %13 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x16x128x128xf32> to tensor<1x16x130x130xf32>
    %14 = tensor.empty() : tensor<1x16x64x64xf32>
    %15 = linalg.fill ins(%cst_209 : f32) outs(%14 : tensor<1x16x64x64xf32>) -> tensor<1x16x64x64xf32>
    %collapsed = tensor.collapse_shape %cst_203 [[0, 1], [2], [3]] : tensor<16x1x3x3xf32> into tensor<16x3x3xf32>
    %16 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_216, %collapsed : tensor<1x16x130x130xf32>, tensor<16x3x3xf32>) outs(%15 : tensor<1x16x64x64xf32>) -> tensor<1x16x64x64xf32>
    cf.assert %3, "training is not supported for now"
    %17 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%16, %cst_200, %cst_199, %cst_202, %cst_201 : tensor<1x16x64x64xf32>, tensor<16xf32>, tensor<16xf32>, tensor<16xf32>, tensor<16xf32>) outs(%16 : tensor<1x16x64x64xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x16x64x64xf32>
    %18 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%17 : tensor<1x16x64x64xf32>) outs(%14 : tensor<1x16x64x64xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x16x64x64xf32>
    %19 = tensor.empty() : tensor<1x16x1x1xf32>
    %20 = linalg.fill ins(%cst_209 : f32) outs(%19 : tensor<1x16x1x1xf32>) -> tensor<1x16x1x1xf32>
    %21 = tensor.empty() : tensor<64x64xf32>
    %22 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%18, %21 : tensor<1x16x64x64xf32>, tensor<64x64xf32>) outs(%20 : tensor<1x16x1x1xf32>) -> tensor<1x16x1x1xf32>
    %23 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%22 : tensor<1x16x1x1xf32>) outs(%19 : tensor<1x16x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_213 : f32
      linalg.yield %362 : f32
    } -> tensor<1x16x1x1xf32>
    %24 = tensor.empty() : tensor<1x8x1x1xf32>
    %25 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_197 : tensor<8xf32>) outs(%24 : tensor<1x8x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x8x1x1xf32>
    %26 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%23, %cst_198 : tensor<1x16x1x1xf32>, tensor<8x16x1x1xf32>) outs(%25 : tensor<1x8x1x1xf32>) -> tensor<1x8x1x1xf32>
    %27 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%26 : tensor<1x8x1x1xf32>) outs(%24 : tensor<1x8x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x8x1x1xf32>
    %28 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_195 : tensor<16xf32>) outs(%19 : tensor<1x16x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x16x1x1xf32>
    %29 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%27, %cst_196 : tensor<1x8x1x1xf32>, tensor<16x8x1x1xf32>) outs(%28 : tensor<1x16x1x1xf32>) -> tensor<1x16x1x1xf32>
    %30 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%29 : tensor<1x16x1x1xf32>) outs(%19 : tensor<1x16x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x16x1x1xf32>
    %31 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%30 : tensor<1x16x1x1xf32>) outs(%19 : tensor<1x16x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x16x1x1xf32>
    %32 = linalg.fill ins(%c1_i64 : i64) outs(%7 : tensor<i64>) -> tensor<i64>
    %33 = linalg.generic {indexing_maps = [#map3, #map3], iterator_types = []} ins(%32 : tensor<i64>) outs(%9 : tensor<f32>) {
    ^bb0(%in: i64, %out: f32):
      %362 = arith.sitofp %in : i64 to f32
      linalg.yield %362 : f32
    } -> tensor<f32>
    %34 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %31 : tensor<f32>, tensor<1x16x1x1xf32>) outs(%19 : tensor<1x16x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x16x1x1xf32>
    %35 = linalg.fill ins(%c0_i64 : i64) outs(%7 : tensor<i64>) -> tensor<i64>
    %36 = linalg.generic {indexing_maps = [#map3, #map3], iterator_types = []} ins(%35 : tensor<i64>) outs(%9 : tensor<f32>) {
    ^bb0(%in: i64, %out: f32):
      %362 = arith.sitofp %in : i64 to f32
      linalg.yield %362 : f32
    } -> tensor<f32>
    %37 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %34 : tensor<f32>, tensor<1x16x1x1xf32>) outs(%19 : tensor<1x16x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x16x1x1xf32>
    %38 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%37, %18 : tensor<1x16x1x1xf32>, tensor<1x16x64x64xf32>) outs(%14 : tensor<1x16x64x64xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x16x64x64xf32>
    %39 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%38, %cst_194 : tensor<1x16x64x64xf32>, tensor<16x16x1x1xf32>) outs(%15 : tensor<1x16x64x64xf32>) -> tensor<1x16x64x64xf32>
    cf.assert %3, "training is not supported for now"
    %40 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%39, %cst_191, %cst_190, %cst_193, %cst_192 : tensor<1x16x64x64xf32>, tensor<16xf32>, tensor<16xf32>, tensor<16xf32>, tensor<16xf32>) outs(%39 : tensor<1x16x64x64xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x16x64x64xf32>
    %41 = tensor.empty() : tensor<1x72x64x64xf32>
    %42 = linalg.fill ins(%cst_209 : f32) outs(%41 : tensor<1x72x64x64xf32>) -> tensor<1x72x64x64xf32>
    %43 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%40, %cst_189 : tensor<1x16x64x64xf32>, tensor<72x16x1x1xf32>) outs(%42 : tensor<1x72x64x64xf32>) -> tensor<1x72x64x64xf32>
    cf.assert %3, "training is not supported for now"
    %44 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%43, %cst_186, %cst_185, %cst_188, %cst_187 : tensor<1x72x64x64xf32>, tensor<72xf32>, tensor<72xf32>, tensor<72xf32>, tensor<72xf32>) outs(%43 : tensor<1x72x64x64xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x72x64x64xf32>
    %45 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%44 : tensor<1x72x64x64xf32>) outs(%41 : tensor<1x72x64x64xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x72x64x64xf32>
    %padded_217 = tensor.pad %45 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x72x64x64xf32> to tensor<1x72x66x66xf32>
    %46 = tensor.empty() : tensor<1x72x32x32xf32>
    %47 = linalg.fill ins(%cst_209 : f32) outs(%46 : tensor<1x72x32x32xf32>) -> tensor<1x72x32x32xf32>
    %collapsed_218 = tensor.collapse_shape %cst_184 [[0, 1], [2], [3]] : tensor<72x1x3x3xf32> into tensor<72x3x3xf32>
    %48 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_217, %collapsed_218 : tensor<1x72x66x66xf32>, tensor<72x3x3xf32>) outs(%47 : tensor<1x72x32x32xf32>) -> tensor<1x72x32x32xf32>
    cf.assert %3, "training is not supported for now"
    %49 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%48, %cst_181, %cst_180, %cst_183, %cst_182 : tensor<1x72x32x32xf32>, tensor<72xf32>, tensor<72xf32>, tensor<72xf32>, tensor<72xf32>) outs(%48 : tensor<1x72x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x72x32x32xf32>
    %50 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%49 : tensor<1x72x32x32xf32>) outs(%46 : tensor<1x72x32x32xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x72x32x32xf32>
    %51 = tensor.empty() : tensor<1x24x32x32xf32>
    %52 = linalg.fill ins(%cst_209 : f32) outs(%51 : tensor<1x24x32x32xf32>) -> tensor<1x24x32x32xf32>
    %53 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%50, %cst_179 : tensor<1x72x32x32xf32>, tensor<24x72x1x1xf32>) outs(%52 : tensor<1x24x32x32xf32>) -> tensor<1x24x32x32xf32>
    cf.assert %3, "training is not supported for now"
    %54 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%53, %cst_176, %cst_175, %cst_178, %cst_177 : tensor<1x24x32x32xf32>, tensor<24xf32>, tensor<24xf32>, tensor<24xf32>, tensor<24xf32>) outs(%53 : tensor<1x24x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x24x32x32xf32>
    %55 = tensor.empty() : tensor<1x88x32x32xf32>
    %56 = linalg.fill ins(%cst_209 : f32) outs(%55 : tensor<1x88x32x32xf32>) -> tensor<1x88x32x32xf32>
    %57 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%54, %cst_174 : tensor<1x24x32x32xf32>, tensor<88x24x1x1xf32>) outs(%56 : tensor<1x88x32x32xf32>) -> tensor<1x88x32x32xf32>
    cf.assert %3, "training is not supported for now"
    %58 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%57, %cst_171, %cst_170, %cst_173, %cst_172 : tensor<1x88x32x32xf32>, tensor<88xf32>, tensor<88xf32>, tensor<88xf32>, tensor<88xf32>) outs(%57 : tensor<1x88x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x88x32x32xf32>
    %59 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%58 : tensor<1x88x32x32xf32>) outs(%55 : tensor<1x88x32x32xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x88x32x32xf32>
    %padded_219 = tensor.pad %59 low[0, 0, 1, 1] high[0, 0, 1, 1] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x88x32x32xf32> to tensor<1x88x34x34xf32>
    %collapsed_220 = tensor.collapse_shape %cst_169 [[0, 1], [2], [3]] : tensor<88x1x3x3xf32> into tensor<88x3x3xf32>
    %60 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_219, %collapsed_220 : tensor<1x88x34x34xf32>, tensor<88x3x3xf32>) outs(%56 : tensor<1x88x32x32xf32>) -> tensor<1x88x32x32xf32>
    cf.assert %3, "training is not supported for now"
    %61 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%60, %cst_166, %cst_165, %cst_168, %cst_167 : tensor<1x88x32x32xf32>, tensor<88xf32>, tensor<88xf32>, tensor<88xf32>, tensor<88xf32>) outs(%60 : tensor<1x88x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x88x32x32xf32>
    %62 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%61 : tensor<1x88x32x32xf32>) outs(%55 : tensor<1x88x32x32xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x88x32x32xf32>
    %63 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%62, %cst_164 : tensor<1x88x32x32xf32>, tensor<24x88x1x1xf32>) outs(%52 : tensor<1x24x32x32xf32>) -> tensor<1x24x32x32xf32>
    cf.assert %3, "training is not supported for now"
    %64 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%63, %cst_161, %cst_160, %cst_163, %cst_162 : tensor<1x24x32x32xf32>, tensor<24xf32>, tensor<24xf32>, tensor<24xf32>, tensor<24xf32>) outs(%63 : tensor<1x24x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x24x32x32xf32>
    %65 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%64, %54 : tensor<1x24x32x32xf32>, tensor<1x24x32x32xf32>) outs(%51 : tensor<1x24x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x24x32x32xf32>
    %66 = tensor.empty() : tensor<1x96x32x32xf32>
    %67 = linalg.fill ins(%cst_209 : f32) outs(%66 : tensor<1x96x32x32xf32>) -> tensor<1x96x32x32xf32>
    %68 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%65, %cst_159 : tensor<1x24x32x32xf32>, tensor<96x24x1x1xf32>) outs(%67 : tensor<1x96x32x32xf32>) -> tensor<1x96x32x32xf32>
    cf.assert %3, "training is not supported for now"
    %69 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%68, %cst_156, %cst_155, %cst_158, %cst_157 : tensor<1x96x32x32xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>) outs(%68 : tensor<1x96x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x96x32x32xf32>
    %70 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%69 : tensor<1x96x32x32xf32>) outs(%66 : tensor<1x96x32x32xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x32x32xf32>
    %71 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%70 : tensor<1x96x32x32xf32>) outs(%66 : tensor<1x96x32x32xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x96x32x32xf32>
    %72 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%71, %10 : tensor<1x96x32x32xf32>, tensor<f32>) outs(%66 : tensor<1x96x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x96x32x32xf32>
    %73 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%72 : tensor<1x96x32x32xf32>) outs(%66 : tensor<1x96x32x32xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x32x32xf32>
    %74 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%73, %69 : tensor<1x96x32x32xf32>, tensor<1x96x32x32xf32>) outs(%66 : tensor<1x96x32x32xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x32x32xf32>
    %padded_221 = tensor.pad %74 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x96x32x32xf32> to tensor<1x96x36x36xf32>
    %75 = tensor.empty() : tensor<1x96x16x16xf32>
    %76 = linalg.fill ins(%cst_209 : f32) outs(%75 : tensor<1x96x16x16xf32>) -> tensor<1x96x16x16xf32>
    %collapsed_222 = tensor.collapse_shape %cst_154 [[0, 1], [2], [3]] : tensor<96x1x5x5xf32> into tensor<96x5x5xf32>
    %77 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_221, %collapsed_222 : tensor<1x96x36x36xf32>, tensor<96x5x5xf32>) outs(%76 : tensor<1x96x16x16xf32>) -> tensor<1x96x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %78 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%77, %cst_151, %cst_150, %cst_153, %cst_152 : tensor<1x96x16x16xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>) outs(%77 : tensor<1x96x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x96x16x16xf32>
    %79 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%78 : tensor<1x96x16x16xf32>) outs(%75 : tensor<1x96x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x16x16xf32>
    %80 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%79 : tensor<1x96x16x16xf32>) outs(%75 : tensor<1x96x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x96x16x16xf32>
    %81 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%80, %10 : tensor<1x96x16x16xf32>, tensor<f32>) outs(%75 : tensor<1x96x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x96x16x16xf32>
    %82 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%81 : tensor<1x96x16x16xf32>) outs(%75 : tensor<1x96x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x16x16xf32>
    %83 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%82, %78 : tensor<1x96x16x16xf32>, tensor<1x96x16x16xf32>) outs(%75 : tensor<1x96x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x16x16xf32>
    %84 = tensor.empty() : tensor<1x96x1x1xf32>
    %85 = linalg.fill ins(%cst_209 : f32) outs(%84 : tensor<1x96x1x1xf32>) -> tensor<1x96x1x1xf32>
    %86 = tensor.empty() : tensor<16x16xf32>
    %87 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%83, %86 : tensor<1x96x16x16xf32>, tensor<16x16xf32>) outs(%85 : tensor<1x96x1x1xf32>) -> tensor<1x96x1x1xf32>
    %88 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%87 : tensor<1x96x1x1xf32>) outs(%84 : tensor<1x96x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_214 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x1x1xf32>
    %89 = tensor.empty() : tensor<1x24x1x1xf32>
    %90 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_148 : tensor<24xf32>) outs(%89 : tensor<1x24x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x24x1x1xf32>
    %91 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%88, %cst_149 : tensor<1x96x1x1xf32>, tensor<24x96x1x1xf32>) outs(%90 : tensor<1x24x1x1xf32>) -> tensor<1x24x1x1xf32>
    %92 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%91 : tensor<1x24x1x1xf32>) outs(%89 : tensor<1x24x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x24x1x1xf32>
    %93 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_146 : tensor<96xf32>) outs(%84 : tensor<1x96x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x96x1x1xf32>
    %94 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%92, %cst_147 : tensor<1x24x1x1xf32>, tensor<96x24x1x1xf32>) outs(%93 : tensor<1x96x1x1xf32>) -> tensor<1x96x1x1xf32>
    %95 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%94 : tensor<1x96x1x1xf32>) outs(%84 : tensor<1x96x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x1x1xf32>
    %96 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%95 : tensor<1x96x1x1xf32>) outs(%84 : tensor<1x96x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x1x1xf32>
    %97 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %96 : tensor<f32>, tensor<1x96x1x1xf32>) outs(%84 : tensor<1x96x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x96x1x1xf32>
    %98 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %97 : tensor<f32>, tensor<1x96x1x1xf32>) outs(%84 : tensor<1x96x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x96x1x1xf32>
    %99 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%98, %83 : tensor<1x96x1x1xf32>, tensor<1x96x16x16xf32>) outs(%75 : tensor<1x96x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x16x16xf32>
    %100 = tensor.empty() : tensor<1x40x16x16xf32>
    %101 = linalg.fill ins(%cst_209 : f32) outs(%100 : tensor<1x40x16x16xf32>) -> tensor<1x40x16x16xf32>
    %102 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%99, %cst_145 : tensor<1x96x16x16xf32>, tensor<40x96x1x1xf32>) outs(%101 : tensor<1x40x16x16xf32>) -> tensor<1x40x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %103 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%102, %cst_142, %cst_141, %cst_144, %cst_143 : tensor<1x40x16x16xf32>, tensor<40xf32>, tensor<40xf32>, tensor<40xf32>, tensor<40xf32>) outs(%102 : tensor<1x40x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x40x16x16xf32>
    %104 = tensor.empty() : tensor<1x240x16x16xf32>
    %105 = linalg.fill ins(%cst_209 : f32) outs(%104 : tensor<1x240x16x16xf32>) -> tensor<1x240x16x16xf32>
    %106 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%103, %cst_140 : tensor<1x40x16x16xf32>, tensor<240x40x1x1xf32>) outs(%105 : tensor<1x240x16x16xf32>) -> tensor<1x240x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %107 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%106, %cst_137, %cst_136, %cst_139, %cst_138 : tensor<1x240x16x16xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>) outs(%106 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x240x16x16xf32>
    %108 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%107 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %109 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%108 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %110 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%109, %10 : tensor<1x240x16x16xf32>, tensor<f32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %111 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%110 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %112 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%111, %107 : tensor<1x240x16x16xf32>, tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %padded_223 = tensor.pad %112 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x240x16x16xf32> to tensor<1x240x20x20xf32>
    %collapsed_224 = tensor.collapse_shape %cst_135 [[0, 1], [2], [3]] : tensor<240x1x5x5xf32> into tensor<240x5x5xf32>
    %113 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_223, %collapsed_224 : tensor<1x240x20x20xf32>, tensor<240x5x5xf32>) outs(%105 : tensor<1x240x16x16xf32>) -> tensor<1x240x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %114 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%113, %cst_132, %cst_131, %cst_134, %cst_133 : tensor<1x240x16x16xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>) outs(%113 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x240x16x16xf32>
    %115 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%114 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %116 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%115 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %117 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%116, %10 : tensor<1x240x16x16xf32>, tensor<f32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %118 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%117 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %119 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%118, %114 : tensor<1x240x16x16xf32>, tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %120 = tensor.empty() : tensor<1x240x1x1xf32>
    %121 = linalg.fill ins(%cst_209 : f32) outs(%120 : tensor<1x240x1x1xf32>) -> tensor<1x240x1x1xf32>
    %122 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%119, %86 : tensor<1x240x16x16xf32>, tensor<16x16xf32>) outs(%121 : tensor<1x240x1x1xf32>) -> tensor<1x240x1x1xf32>
    %123 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%122 : tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_214 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x1x1xf32>
    %124 = tensor.empty() : tensor<1x64x1x1xf32>
    %125 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_129 : tensor<64xf32>) outs(%124 : tensor<1x64x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x64x1x1xf32>
    %126 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%123, %cst_130 : tensor<1x240x1x1xf32>, tensor<64x240x1x1xf32>) outs(%125 : tensor<1x64x1x1xf32>) -> tensor<1x64x1x1xf32>
    %127 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%126 : tensor<1x64x1x1xf32>) outs(%124 : tensor<1x64x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x64x1x1xf32>
    %128 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_127 : tensor<240xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x240x1x1xf32>
    %129 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%127, %cst_128 : tensor<1x64x1x1xf32>, tensor<240x64x1x1xf32>) outs(%128 : tensor<1x240x1x1xf32>) -> tensor<1x240x1x1xf32>
    %130 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%129 : tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x1x1xf32>
    %131 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%130 : tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x1x1xf32>
    %132 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %131 : tensor<f32>, tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x1x1xf32>
    %133 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %132 : tensor<f32>, tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x1x1xf32>
    %134 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%133, %119 : tensor<1x240x1x1xf32>, tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %135 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%134, %cst_126 : tensor<1x240x16x16xf32>, tensor<40x240x1x1xf32>) outs(%101 : tensor<1x40x16x16xf32>) -> tensor<1x40x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %136 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%135, %cst_123, %cst_122, %cst_125, %cst_124 : tensor<1x40x16x16xf32>, tensor<40xf32>, tensor<40xf32>, tensor<40xf32>, tensor<40xf32>) outs(%135 : tensor<1x40x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x40x16x16xf32>
    %137 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%136, %103 : tensor<1x40x16x16xf32>, tensor<1x40x16x16xf32>) outs(%100 : tensor<1x40x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x40x16x16xf32>
    %138 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%137, %cst_121 : tensor<1x40x16x16xf32>, tensor<240x40x1x1xf32>) outs(%105 : tensor<1x240x16x16xf32>) -> tensor<1x240x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %139 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%138, %cst_118, %cst_117, %cst_120, %cst_119 : tensor<1x240x16x16xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>) outs(%138 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x240x16x16xf32>
    %140 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%139 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %141 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%140 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %142 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%141, %10 : tensor<1x240x16x16xf32>, tensor<f32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %143 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%142 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %144 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%143, %139 : tensor<1x240x16x16xf32>, tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %padded_225 = tensor.pad %144 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x240x16x16xf32> to tensor<1x240x20x20xf32>
    %collapsed_226 = tensor.collapse_shape %cst_116 [[0, 1], [2], [3]] : tensor<240x1x5x5xf32> into tensor<240x5x5xf32>
    %145 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_225, %collapsed_226 : tensor<1x240x20x20xf32>, tensor<240x5x5xf32>) outs(%105 : tensor<1x240x16x16xf32>) -> tensor<1x240x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %146 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%145, %cst_113, %cst_112, %cst_115, %cst_114 : tensor<1x240x16x16xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>, tensor<240xf32>) outs(%145 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x240x16x16xf32>
    %147 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%146 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %148 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%147 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %149 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%148, %10 : tensor<1x240x16x16xf32>, tensor<f32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x16x16xf32>
    %150 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%149 : tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %151 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%150, %146 : tensor<1x240x16x16xf32>, tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %152 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%151, %86 : tensor<1x240x16x16xf32>, tensor<16x16xf32>) outs(%121 : tensor<1x240x1x1xf32>) -> tensor<1x240x1x1xf32>
    %153 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%152 : tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_214 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x1x1xf32>
    %154 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_110 : tensor<64xf32>) outs(%124 : tensor<1x64x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x64x1x1xf32>
    %155 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%153, %cst_111 : tensor<1x240x1x1xf32>, tensor<64x240x1x1xf32>) outs(%154 : tensor<1x64x1x1xf32>) -> tensor<1x64x1x1xf32>
    %156 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%155 : tensor<1x64x1x1xf32>) outs(%124 : tensor<1x64x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x64x1x1xf32>
    %157 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_108 : tensor<240xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x240x1x1xf32>
    %158 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%156, %cst_109 : tensor<1x64x1x1xf32>, tensor<240x64x1x1xf32>) outs(%157 : tensor<1x240x1x1xf32>) -> tensor<1x240x1x1xf32>
    %159 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%158 : tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x1x1xf32>
    %160 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%159 : tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x1x1xf32>
    %161 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %160 : tensor<f32>, tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x1x1xf32>
    %162 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %161 : tensor<f32>, tensor<1x240x1x1xf32>) outs(%120 : tensor<1x240x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x240x1x1xf32>
    %163 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%162, %151 : tensor<1x240x1x1xf32>, tensor<1x240x16x16xf32>) outs(%104 : tensor<1x240x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x240x16x16xf32>
    %164 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%163, %cst_107 : tensor<1x240x16x16xf32>, tensor<40x240x1x1xf32>) outs(%101 : tensor<1x40x16x16xf32>) -> tensor<1x40x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %165 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%164, %cst_104, %cst_103, %cst_106, %cst_105 : tensor<1x40x16x16xf32>, tensor<40xf32>, tensor<40xf32>, tensor<40xf32>, tensor<40xf32>) outs(%164 : tensor<1x40x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x40x16x16xf32>
    %166 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%165, %137 : tensor<1x40x16x16xf32>, tensor<1x40x16x16xf32>) outs(%100 : tensor<1x40x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x40x16x16xf32>
    %167 = tensor.empty() : tensor<1x120x16x16xf32>
    %168 = linalg.fill ins(%cst_209 : f32) outs(%167 : tensor<1x120x16x16xf32>) -> tensor<1x120x16x16xf32>
    %169 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%166, %cst_102 : tensor<1x40x16x16xf32>, tensor<120x40x1x1xf32>) outs(%168 : tensor<1x120x16x16xf32>) -> tensor<1x120x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %170 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%169, %cst_99, %cst_98, %cst_101, %cst_100 : tensor<1x120x16x16xf32>, tensor<120xf32>, tensor<120xf32>, tensor<120xf32>, tensor<120xf32>) outs(%169 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x120x16x16xf32>
    %171 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%170 : tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x16x16xf32>
    %172 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%171 : tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x120x16x16xf32>
    %173 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%172, %10 : tensor<1x120x16x16xf32>, tensor<f32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x120x16x16xf32>
    %174 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%173 : tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x16x16xf32>
    %175 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%174, %170 : tensor<1x120x16x16xf32>, tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x16x16xf32>
    %padded_227 = tensor.pad %175 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x120x16x16xf32> to tensor<1x120x20x20xf32>
    %collapsed_228 = tensor.collapse_shape %cst_97 [[0, 1], [2], [3]] : tensor<120x1x5x5xf32> into tensor<120x5x5xf32>
    %176 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_227, %collapsed_228 : tensor<1x120x20x20xf32>, tensor<120x5x5xf32>) outs(%168 : tensor<1x120x16x16xf32>) -> tensor<1x120x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %177 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%176, %cst_94, %cst_93, %cst_96, %cst_95 : tensor<1x120x16x16xf32>, tensor<120xf32>, tensor<120xf32>, tensor<120xf32>, tensor<120xf32>) outs(%176 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x120x16x16xf32>
    %178 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%177 : tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x16x16xf32>
    %179 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%178 : tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x120x16x16xf32>
    %180 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%179, %10 : tensor<1x120x16x16xf32>, tensor<f32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x120x16x16xf32>
    %181 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%180 : tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x16x16xf32>
    %182 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%181, %177 : tensor<1x120x16x16xf32>, tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x16x16xf32>
    %183 = tensor.empty() : tensor<1x120x1x1xf32>
    %184 = linalg.fill ins(%cst_209 : f32) outs(%183 : tensor<1x120x1x1xf32>) -> tensor<1x120x1x1xf32>
    %185 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%182, %86 : tensor<1x120x16x16xf32>, tensor<16x16xf32>) outs(%184 : tensor<1x120x1x1xf32>) -> tensor<1x120x1x1xf32>
    %186 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%185 : tensor<1x120x1x1xf32>) outs(%183 : tensor<1x120x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_214 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x1x1xf32>
    %187 = tensor.empty() : tensor<1x32x1x1xf32>
    %188 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_91 : tensor<32xf32>) outs(%187 : tensor<1x32x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x32x1x1xf32>
    %189 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%186, %cst_92 : tensor<1x120x1x1xf32>, tensor<32x120x1x1xf32>) outs(%188 : tensor<1x32x1x1xf32>) -> tensor<1x32x1x1xf32>
    %190 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%189 : tensor<1x32x1x1xf32>) outs(%187 : tensor<1x32x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x32x1x1xf32>
    %191 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_89 : tensor<120xf32>) outs(%183 : tensor<1x120x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x120x1x1xf32>
    %192 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%190, %cst_90 : tensor<1x32x1x1xf32>, tensor<120x32x1x1xf32>) outs(%191 : tensor<1x120x1x1xf32>) -> tensor<1x120x1x1xf32>
    %193 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%192 : tensor<1x120x1x1xf32>) outs(%183 : tensor<1x120x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x1x1xf32>
    %194 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%193 : tensor<1x120x1x1xf32>) outs(%183 : tensor<1x120x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x1x1xf32>
    %195 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %194 : tensor<f32>, tensor<1x120x1x1xf32>) outs(%183 : tensor<1x120x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x120x1x1xf32>
    %196 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %195 : tensor<f32>, tensor<1x120x1x1xf32>) outs(%183 : tensor<1x120x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x120x1x1xf32>
    %197 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%196, %182 : tensor<1x120x1x1xf32>, tensor<1x120x16x16xf32>) outs(%167 : tensor<1x120x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x120x16x16xf32>
    %198 = tensor.empty() : tensor<1x48x16x16xf32>
    %199 = linalg.fill ins(%cst_209 : f32) outs(%198 : tensor<1x48x16x16xf32>) -> tensor<1x48x16x16xf32>
    %200 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%197, %cst_88 : tensor<1x120x16x16xf32>, tensor<48x120x1x1xf32>) outs(%199 : tensor<1x48x16x16xf32>) -> tensor<1x48x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %201 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%200, %cst_85, %cst_84, %cst_87, %cst_86 : tensor<1x48x16x16xf32>, tensor<48xf32>, tensor<48xf32>, tensor<48xf32>, tensor<48xf32>) outs(%200 : tensor<1x48x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x48x16x16xf32>
    %202 = tensor.empty() : tensor<1x144x16x16xf32>
    %203 = linalg.fill ins(%cst_209 : f32) outs(%202 : tensor<1x144x16x16xf32>) -> tensor<1x144x16x16xf32>
    %204 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%201, %cst_83 : tensor<1x48x16x16xf32>, tensor<144x48x1x1xf32>) outs(%203 : tensor<1x144x16x16xf32>) -> tensor<1x144x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %205 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%204, %cst_80, %cst_79, %cst_82, %cst_81 : tensor<1x144x16x16xf32>, tensor<144xf32>, tensor<144xf32>, tensor<144xf32>, tensor<144xf32>) outs(%204 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x144x16x16xf32>
    %206 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%205 : tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x16x16xf32>
    %207 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%206 : tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x16x16xf32>
    %208 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%207, %10 : tensor<1x144x16x16xf32>, tensor<f32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x16x16xf32>
    %209 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%208 : tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x16x16xf32>
    %210 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%209, %205 : tensor<1x144x16x16xf32>, tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x16x16xf32>
    %padded_229 = tensor.pad %210 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x144x16x16xf32> to tensor<1x144x20x20xf32>
    %collapsed_230 = tensor.collapse_shape %cst_78 [[0, 1], [2], [3]] : tensor<144x1x5x5xf32> into tensor<144x5x5xf32>
    %211 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_229, %collapsed_230 : tensor<1x144x20x20xf32>, tensor<144x5x5xf32>) outs(%203 : tensor<1x144x16x16xf32>) -> tensor<1x144x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %212 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%211, %cst_75, %cst_74, %cst_77, %cst_76 : tensor<1x144x16x16xf32>, tensor<144xf32>, tensor<144xf32>, tensor<144xf32>, tensor<144xf32>) outs(%211 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x144x16x16xf32>
    %213 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%212 : tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x16x16xf32>
    %214 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%213 : tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x16x16xf32>
    %215 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%214, %10 : tensor<1x144x16x16xf32>, tensor<f32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x16x16xf32>
    %216 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%215 : tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x16x16xf32>
    %217 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%216, %212 : tensor<1x144x16x16xf32>, tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x16x16xf32>
    %218 = tensor.empty() : tensor<1x144x1x1xf32>
    %219 = linalg.fill ins(%cst_209 : f32) outs(%218 : tensor<1x144x1x1xf32>) -> tensor<1x144x1x1xf32>
    %220 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%217, %86 : tensor<1x144x16x16xf32>, tensor<16x16xf32>) outs(%219 : tensor<1x144x1x1xf32>) -> tensor<1x144x1x1xf32>
    %221 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%220 : tensor<1x144x1x1xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_214 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x1x1xf32>
    %222 = tensor.empty() : tensor<1x40x1x1xf32>
    %223 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_72 : tensor<40xf32>) outs(%222 : tensor<1x40x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x40x1x1xf32>
    %224 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%221, %cst_73 : tensor<1x144x1x1xf32>, tensor<40x144x1x1xf32>) outs(%223 : tensor<1x40x1x1xf32>) -> tensor<1x40x1x1xf32>
    %225 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%224 : tensor<1x40x1x1xf32>) outs(%222 : tensor<1x40x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x40x1x1xf32>
    %226 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_70 : tensor<144xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x144x1x1xf32>
    %227 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%225, %cst_71 : tensor<1x40x1x1xf32>, tensor<144x40x1x1xf32>) outs(%226 : tensor<1x144x1x1xf32>) -> tensor<1x144x1x1xf32>
    %228 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%227 : tensor<1x144x1x1xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x1x1xf32>
    %229 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%228 : tensor<1x144x1x1xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x1x1xf32>
    %230 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %229 : tensor<f32>, tensor<1x144x1x1xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x1x1xf32>
    %231 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %230 : tensor<f32>, tensor<1x144x1x1xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x1x1xf32>
    %232 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%231, %217 : tensor<1x144x1x1xf32>, tensor<1x144x16x16xf32>) outs(%202 : tensor<1x144x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x144x16x16xf32>
    %233 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%232, %cst_69 : tensor<1x144x16x16xf32>, tensor<48x144x1x1xf32>) outs(%199 : tensor<1x48x16x16xf32>) -> tensor<1x48x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %234 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%233, %cst_66, %cst_65, %cst_68, %cst_67 : tensor<1x48x16x16xf32>, tensor<48xf32>, tensor<48xf32>, tensor<48xf32>, tensor<48xf32>) outs(%233 : tensor<1x48x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x48x16x16xf32>
    %235 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%234, %201 : tensor<1x48x16x16xf32>, tensor<1x48x16x16xf32>) outs(%198 : tensor<1x48x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x48x16x16xf32>
    %236 = tensor.empty() : tensor<1x288x16x16xf32>
    %237 = linalg.fill ins(%cst_209 : f32) outs(%236 : tensor<1x288x16x16xf32>) -> tensor<1x288x16x16xf32>
    %238 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%235, %cst_64 : tensor<1x48x16x16xf32>, tensor<288x48x1x1xf32>) outs(%237 : tensor<1x288x16x16xf32>) -> tensor<1x288x16x16xf32>
    cf.assert %3, "training is not supported for now"
    %239 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%238, %cst_61, %cst_60, %cst_63, %cst_62 : tensor<1x288x16x16xf32>, tensor<288xf32>, tensor<288xf32>, tensor<288xf32>, tensor<288xf32>) outs(%238 : tensor<1x288x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x288x16x16xf32>
    %240 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%239 : tensor<1x288x16x16xf32>) outs(%236 : tensor<1x288x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x16x16xf32>
    %241 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%240 : tensor<1x288x16x16xf32>) outs(%236 : tensor<1x288x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x288x16x16xf32>
    %242 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%241, %10 : tensor<1x288x16x16xf32>, tensor<f32>) outs(%236 : tensor<1x288x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x288x16x16xf32>
    %243 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%242 : tensor<1x288x16x16xf32>) outs(%236 : tensor<1x288x16x16xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x16x16xf32>
    %244 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%243, %239 : tensor<1x288x16x16xf32>, tensor<1x288x16x16xf32>) outs(%236 : tensor<1x288x16x16xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x16x16xf32>
    %padded_231 = tensor.pad %244 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x288x16x16xf32> to tensor<1x288x20x20xf32>
    %245 = tensor.empty() : tensor<1x288x8x8xf32>
    %246 = linalg.fill ins(%cst_209 : f32) outs(%245 : tensor<1x288x8x8xf32>) -> tensor<1x288x8x8xf32>
    %collapsed_232 = tensor.collapse_shape %cst_59 [[0, 1], [2], [3]] : tensor<288x1x5x5xf32> into tensor<288x5x5xf32>
    %247 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} ins(%padded_231, %collapsed_232 : tensor<1x288x20x20xf32>, tensor<288x5x5xf32>) outs(%246 : tensor<1x288x8x8xf32>) -> tensor<1x288x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %248 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%247, %cst_56, %cst_55, %cst_58, %cst_57 : tensor<1x288x8x8xf32>, tensor<288xf32>, tensor<288xf32>, tensor<288xf32>, tensor<288xf32>) outs(%247 : tensor<1x288x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x288x8x8xf32>
    %249 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%248 : tensor<1x288x8x8xf32>) outs(%245 : tensor<1x288x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x8x8xf32>
    %250 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%249 : tensor<1x288x8x8xf32>) outs(%245 : tensor<1x288x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x288x8x8xf32>
    %251 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%250, %10 : tensor<1x288x8x8xf32>, tensor<f32>) outs(%245 : tensor<1x288x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x288x8x8xf32>
    %252 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%251 : tensor<1x288x8x8xf32>) outs(%245 : tensor<1x288x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x8x8xf32>
    %253 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%252, %248 : tensor<1x288x8x8xf32>, tensor<1x288x8x8xf32>) outs(%245 : tensor<1x288x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x8x8xf32>
    %254 = tensor.empty() : tensor<1x288x1x1xf32>
    %255 = linalg.fill ins(%cst_209 : f32) outs(%254 : tensor<1x288x1x1xf32>) -> tensor<1x288x1x1xf32>
    %256 = tensor.empty() : tensor<8x8xf32>
    %257 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%253, %256 : tensor<1x288x8x8xf32>, tensor<8x8xf32>) outs(%255 : tensor<1x288x1x1xf32>) -> tensor<1x288x1x1xf32>
    %258 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%257 : tensor<1x288x1x1xf32>) outs(%254 : tensor<1x288x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_215 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x1x1xf32>
    %259 = tensor.empty() : tensor<1x72x1x1xf32>
    %260 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_53 : tensor<72xf32>) outs(%259 : tensor<1x72x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x72x1x1xf32>
    %261 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%258, %cst_54 : tensor<1x288x1x1xf32>, tensor<72x288x1x1xf32>) outs(%260 : tensor<1x72x1x1xf32>) -> tensor<1x72x1x1xf32>
    %262 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%261 : tensor<1x72x1x1xf32>) outs(%259 : tensor<1x72x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x72x1x1xf32>
    %263 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_51 : tensor<288xf32>) outs(%254 : tensor<1x288x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x288x1x1xf32>
    %264 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%262, %cst_52 : tensor<1x72x1x1xf32>, tensor<288x72x1x1xf32>) outs(%263 : tensor<1x288x1x1xf32>) -> tensor<1x288x1x1xf32>
    %265 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%264 : tensor<1x288x1x1xf32>) outs(%254 : tensor<1x288x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x1x1xf32>
    %266 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%265 : tensor<1x288x1x1xf32>) outs(%254 : tensor<1x288x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x1x1xf32>
    %267 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %266 : tensor<f32>, tensor<1x288x1x1xf32>) outs(%254 : tensor<1x288x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x288x1x1xf32>
    %268 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %267 : tensor<f32>, tensor<1x288x1x1xf32>) outs(%254 : tensor<1x288x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x288x1x1xf32>
    %269 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%268, %253 : tensor<1x288x1x1xf32>, tensor<1x288x8x8xf32>) outs(%245 : tensor<1x288x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x288x8x8xf32>
    %270 = tensor.empty() : tensor<1x96x8x8xf32>
    %271 = linalg.fill ins(%cst_209 : f32) outs(%270 : tensor<1x96x8x8xf32>) -> tensor<1x96x8x8xf32>
    %272 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%269, %cst_50 : tensor<1x288x8x8xf32>, tensor<96x288x1x1xf32>) outs(%271 : tensor<1x96x8x8xf32>) -> tensor<1x96x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %273 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%272, %cst_47, %cst_46, %cst_49, %cst_48 : tensor<1x96x8x8xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>) outs(%272 : tensor<1x96x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x96x8x8xf32>
    %274 = tensor.empty() : tensor<1x576x8x8xf32>
    %275 = linalg.fill ins(%cst_209 : f32) outs(%274 : tensor<1x576x8x8xf32>) -> tensor<1x576x8x8xf32>
    %276 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%273, %cst_45 : tensor<1x96x8x8xf32>, tensor<576x96x1x1xf32>) outs(%275 : tensor<1x576x8x8xf32>) -> tensor<1x576x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %277 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%276, %cst_42, %cst_41, %cst_44, %cst_43 : tensor<1x576x8x8xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>) outs(%276 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x576x8x8xf32>
    %278 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%277 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %279 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%278 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %280 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%279, %10 : tensor<1x576x8x8xf32>, tensor<f32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %281 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%280 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %282 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%281, %277 : tensor<1x576x8x8xf32>, tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %padded_233 = tensor.pad %282 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x576x8x8xf32> to tensor<1x576x12x12xf32>
    %collapsed_234 = tensor.collapse_shape %cst_40 [[0, 1], [2], [3]] : tensor<576x1x5x5xf32> into tensor<576x5x5xf32>
    %283 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_233, %collapsed_234 : tensor<1x576x12x12xf32>, tensor<576x5x5xf32>) outs(%275 : tensor<1x576x8x8xf32>) -> tensor<1x576x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %284 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%283, %cst_37, %cst_36, %cst_39, %cst_38 : tensor<1x576x8x8xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>) outs(%283 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x576x8x8xf32>
    %285 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%284 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %286 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%285 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %287 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%286, %10 : tensor<1x576x8x8xf32>, tensor<f32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %288 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%287 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %289 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%288, %284 : tensor<1x576x8x8xf32>, tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %290 = tensor.empty() : tensor<1x576x1x1xf32>
    %291 = linalg.fill ins(%cst_209 : f32) outs(%290 : tensor<1x576x1x1xf32>) -> tensor<1x576x1x1xf32>
    %292 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%289, %256 : tensor<1x576x8x8xf32>, tensor<8x8xf32>) outs(%291 : tensor<1x576x1x1xf32>) -> tensor<1x576x1x1xf32>
    %293 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%292 : tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_215 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x1x1xf32>
    %294 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_34 : tensor<144xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x144x1x1xf32>
    %295 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%293, %cst_35 : tensor<1x576x1x1xf32>, tensor<144x576x1x1xf32>) outs(%294 : tensor<1x144x1x1xf32>) -> tensor<1x144x1x1xf32>
    %296 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%295 : tensor<1x144x1x1xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x1x1xf32>
    %297 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_32 : tensor<576xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x576x1x1xf32>
    %298 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%296, %cst_33 : tensor<1x144x1x1xf32>, tensor<576x144x1x1xf32>) outs(%297 : tensor<1x576x1x1xf32>) -> tensor<1x576x1x1xf32>
    %299 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%298 : tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x1x1xf32>
    %300 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%299 : tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x1x1xf32>
    %301 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %300 : tensor<f32>, tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x1x1xf32>
    %302 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %301 : tensor<f32>, tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x1x1xf32>
    %303 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%302, %289 : tensor<1x576x1x1xf32>, tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %304 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%303, %cst_31 : tensor<1x576x8x8xf32>, tensor<96x576x1x1xf32>) outs(%271 : tensor<1x96x8x8xf32>) -> tensor<1x96x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %305 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%304, %cst_28, %cst_27, %cst_30, %cst_29 : tensor<1x96x8x8xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>) outs(%304 : tensor<1x96x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x96x8x8xf32>
    %306 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%305, %273 : tensor<1x96x8x8xf32>, tensor<1x96x8x8xf32>) outs(%270 : tensor<1x96x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x8x8xf32>
    %307 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%306, %cst_26 : tensor<1x96x8x8xf32>, tensor<576x96x1x1xf32>) outs(%275 : tensor<1x576x8x8xf32>) -> tensor<1x576x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %308 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%307, %cst_23, %cst_22, %cst_25, %cst_24 : tensor<1x576x8x8xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>) outs(%307 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x576x8x8xf32>
    %309 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%308 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %310 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%309 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %311 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%310, %10 : tensor<1x576x8x8xf32>, tensor<f32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %312 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%311 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %313 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%312, %308 : tensor<1x576x8x8xf32>, tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %padded_235 = tensor.pad %313 low[0, 0, 2, 2] high[0, 0, 2, 2] {
    ^bb0(%arg1: index, %arg2: index, %arg3: index, %arg4: index):
      tensor.yield %cst_209 : f32
    } : tensor<1x576x8x8xf32> to tensor<1x576x12x12xf32>
    %collapsed_236 = tensor.collapse_shape %cst_21 [[0, 1], [2], [3]] : tensor<576x1x5x5xf32> into tensor<576x5x5xf32>
    %314 = linalg.depthwise_conv_2d_nchw_chw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%padded_235, %collapsed_236 : tensor<1x576x12x12xf32>, tensor<576x5x5xf32>) outs(%275 : tensor<1x576x8x8xf32>) -> tensor<1x576x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %315 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%314, %cst_18, %cst_17, %cst_20, %cst_19 : tensor<1x576x8x8xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>) outs(%314 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x576x8x8xf32>
    %316 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%315 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %317 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%316 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %318 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%317, %10 : tensor<1x576x8x8xf32>, tensor<f32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %319 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%318 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %320 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%319, %315 : tensor<1x576x8x8xf32>, tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %321 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%320, %256 : tensor<1x576x8x8xf32>, tensor<8x8xf32>) outs(%291 : tensor<1x576x1x1xf32>) -> tensor<1x576x1x1xf32>
    %322 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%321 : tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_215 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x1x1xf32>
    %323 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_15 : tensor<144xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x144x1x1xf32>
    %324 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%322, %cst_16 : tensor<1x576x1x1xf32>, tensor<144x576x1x1xf32>) outs(%323 : tensor<1x144x1x1xf32>) -> tensor<1x144x1x1xf32>
    %325 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%324 : tensor<1x144x1x1xf32>) outs(%218 : tensor<1x144x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x144x1x1xf32>
    %326 = linalg.generic {indexing_maps = [#map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%cst_13 : tensor<576xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1x576x1x1xf32>
    %327 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%325, %cst_14 : tensor<1x144x1x1xf32>, tensor<576x144x1x1xf32>) outs(%326 : tensor<1x576x1x1xf32>) -> tensor<1x576x1x1xf32>
    %328 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%327 : tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x1x1xf32>
    %329 = linalg.generic {indexing_maps = [#map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%328 : tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x1x1xf32>
    %330 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%33, %329 : tensor<f32>, tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x1x1xf32>
    %331 = linalg.generic {indexing_maps = [#map4, #map5, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%36, %330 : tensor<f32>, tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf ogt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x1x1xf32>
    %332 = linalg.generic {indexing_maps = [#map5, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%331, %320 : tensor<1x576x1x1xf32>, tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %333 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%332, %cst_12 : tensor<1x576x8x8xf32>, tensor<96x576x1x1xf32>) outs(%271 : tensor<1x96x8x8xf32>) -> tensor<1x96x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %334 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%333, %cst_9, %cst_8, %cst_11, %cst_10 : tensor<1x96x8x8xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>, tensor<96xf32>) outs(%333 : tensor<1x96x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x96x8x8xf32>
    %335 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%334, %306 : tensor<1x96x8x8xf32>, tensor<1x96x8x8xf32>) outs(%270 : tensor<1x96x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x96x8x8xf32>
    %336 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%335, %cst_7 : tensor<1x96x8x8xf32>, tensor<576x96x1x1xf32>) outs(%275 : tensor<1x576x8x8xf32>) -> tensor<1x576x8x8xf32>
    cf.assert %3, "training is not supported for now"
    %337 = linalg.generic {indexing_maps = [#map, #map1, #map1, #map1, #map1, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%336, %cst_4, %cst_3, %cst_6, %cst_5 : tensor<1x576x8x8xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>, tensor<576xf32>) outs(%336 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %in_239: f32, %in_240: f32, %in_241: f32, %out: f32):
      %362 = arith.truncf %cst_210 : f64 to f32
      %363 = arith.addf %in_241, %362 : f32
      %364 = math.rsqrt %363 : f32
      %365 = arith.subf %in, %in_240 : f32
      %366 = arith.mulf %365, %364 : f32
      %367 = arith.mulf %366, %in_238 : f32
      %368 = arith.addf %367, %in_239 : f32
      linalg.yield %368 : f32
    } -> tensor<1x576x8x8xf32>
    %338 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%337 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %339 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%338 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %340 = linalg.generic {indexing_maps = [#map2, #map4, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%339, %10 : tensor<1x576x8x8xf32>, tensor<f32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x576x8x8xf32>
    %341 = linalg.generic {indexing_maps = [#map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%340 : tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %342 = linalg.generic {indexing_maps = [#map2, #map2, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%341, %337 : tensor<1x576x8x8xf32>, tensor<1x576x8x8xf32>) outs(%274 : tensor<1x576x8x8xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x8x8xf32>
    %343 = linalg.pooling_nchw_sum {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%342, %256 : tensor<1x576x8x8xf32>, tensor<8x8xf32>) outs(%291 : tensor<1x576x1x1xf32>) -> tensor<1x576x1x1xf32>
    %344 = linalg.generic {indexing_maps = [#map, #map], iterator_types = ["parallel", "parallel", "parallel", "parallel"]} ins(%343 : tensor<1x576x1x1xf32>) outs(%290 : tensor<1x576x1x1xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_215 : f32
      linalg.yield %362 : f32
    } -> tensor<1x576x1x1xf32>
    %collapsed_237 = tensor.collapse_shape %344 [[0], [1, 2, 3]] : tensor<1x576x1x1xf32> into tensor<1x576xf32>
    %345 = tensor.empty() : tensor<576x1024xf32>
    %346 = linalg.generic {indexing_maps = [#map6, #map7], iterator_types = ["parallel", "parallel"]} ins(%cst_2 : tensor<1024x576xf32>) outs(%345 : tensor<576x1024xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<576x1024xf32>
    %347 = tensor.empty() : tensor<1x1024xf32>
    %348 = linalg.fill ins(%cst_209 : f32) outs(%347 : tensor<1x1024xf32>) -> tensor<1x1024xf32>
    %349 = linalg.matmul ins(%collapsed_237, %346 : tensor<1x576xf32>, tensor<576x1024xf32>) outs(%348 : tensor<1x1024xf32>) -> tensor<1x1024xf32>
    %350 = linalg.generic {indexing_maps = [#map8, #map9, #map6], iterator_types = ["parallel", "parallel"]} ins(%349, %cst_1 : tensor<1x1024xf32>, tensor<1024xf32>) outs(%347 : tensor<1x1024xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x1024xf32>
    %351 = linalg.generic {indexing_maps = [#map8, #map6], iterator_types = ["parallel", "parallel"]} ins(%350 : tensor<1x1024xf32>) outs(%347 : tensor<1x1024xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.addf %in, %cst_211 : f32
      linalg.yield %362 : f32
    } -> tensor<1x1024xf32>
    %352 = linalg.generic {indexing_maps = [#map8, #map6], iterator_types = ["parallel", "parallel"]} ins(%351 : tensor<1x1024xf32>) outs(%347 : tensor<1x1024xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.cmpf ugt, %in, %cst_209 : f32
      %363 = arith.select %362, %in, %cst_209 : f32
      linalg.yield %363 : f32
    } -> tensor<1x1024xf32>
    %353 = linalg.generic {indexing_maps = [#map8, #map10, #map6], iterator_types = ["parallel", "parallel"]} ins(%352, %10 : tensor<1x1024xf32>, tensor<f32>) outs(%347 : tensor<1x1024xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.cmpf olt, %in, %in_238 : f32
      %363 = arith.select %362, %in, %in_238 : f32
      linalg.yield %363 : f32
    } -> tensor<1x1024xf32>
    %354 = linalg.generic {indexing_maps = [#map8, #map6], iterator_types = ["parallel", "parallel"]} ins(%353 : tensor<1x1024xf32>) outs(%347 : tensor<1x1024xf32>) {
    ^bb0(%in: f32, %out: f32):
      %362 = arith.divf %in, %cst_212 : f32
      linalg.yield %362 : f32
    } -> tensor<1x1024xf32>
    %355 = linalg.generic {indexing_maps = [#map8, #map8, #map6], iterator_types = ["parallel", "parallel"]} ins(%354, %350 : tensor<1x1024xf32>, tensor<1x1024xf32>) outs(%347 : tensor<1x1024xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.mulf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x1024xf32>
    %356 = tensor.empty() : tensor<1024x1000xf32>
    %357 = linalg.generic {indexing_maps = [#map6, #map7], iterator_types = ["parallel", "parallel"]} ins(%cst_0 : tensor<1000x1024xf32>) outs(%356 : tensor<1024x1000xf32>) {
    ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<1024x1000xf32>
    %358 = tensor.empty() : tensor<1x1000xf32>
    %359 = linalg.fill ins(%cst_209 : f32) outs(%358 : tensor<1x1000xf32>) -> tensor<1x1000xf32>
    %360 = linalg.matmul ins(%355, %357 : tensor<1x1024xf32>, tensor<1024x1000xf32>) outs(%359 : tensor<1x1000xf32>) -> tensor<1x1000xf32>
    %361 = linalg.generic {indexing_maps = [#map8, #map9, #map6], iterator_types = ["parallel", "parallel"]} ins(%360, %cst : tensor<1x1000xf32>, tensor<1000xf32>) outs(%358 : tensor<1x1000xf32>) {
    ^bb0(%in: f32, %in_238: f32, %out: f32):
      %362 = arith.addf %in, %in_238 : f32
      linalg.yield %362 : f32
    } -> tensor<1x1000xf32>
    return %361 : tensor<1x1000xf32>
  }
}
