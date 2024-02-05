module {
func.func @conv(%input: tensor<1x225x225x3xf32>, %filter: tensor<3x3x3x32xf32>, %init: tensor<1x112x112x32xf32>) -> tensor<1x112x112x32xf32> {
  %0 = linalg.conv_2d_nhwc_hwcf
    {dilations = dense<1> : tensor<2xi64>, strides = dense<2> : tensor<2xi64>}
    ins(%input, %filter : tensor<1x225x225x3xf32>, tensor<3x3x3x32xf32>)
    outs(%init : tensor<1x112x112x32xf32>)
  -> tensor<1x112x112x32xf32>
  return %0: tensor<1x112x112x32xf32>
}
}

// #map = affine_map<(d0, d1) -> (d0 * 2 + d1)>
// module {
//   func.func @conv(%arg0: tensor<1x225x225x3xf32>, %arg1: tensor<3x3x3x32xf32>, %arg2: tensor<1x112x112x32xf32>) -> tensor<1x112x112x32xf32> {
//     %0 = bufferization.to_memref %arg1 : memref<3x3x3x32xf32, strided<[?, ?, ?, ?], offset: ?>>
//     %1 = bufferization.to_memref %arg0 : memref<1x225x225x3xf32, strided<[?, ?, ?, ?], offset: ?>>
//     %2 = bufferization.to_memref %arg2 : memref<1x112x112x32xf32, strided<[?, ?, ?, ?], offset: ?>>
//     %alloc = memref.alloc() {alignment = 64 : i64} : memref<1x112x112x32xf32>
//     memref.copy %2, %alloc : memref<1x112x112x32xf32, strided<[?, ?, ?, ?], offset: ?>> to memref<1x112x112x32xf32>
//     affine.for %arg3 = 0 to 1 {
//       affine.for %arg4 = 0 to 112 {
//         affine.for %arg5 = 0 to 112 {
//           affine.for %arg6 = 0 to 32 {
//             affine.for %arg7 = 0 to 3 {
//               affine.for %arg8 = 0 to 3 {
//                 affine.for %arg9 = 0 to 3 {
//                   %4 = affine.apply #map(%arg4, %arg7)
//                   %5 = affine.apply #map(%arg5, %arg8)
//                   %6 = affine.load %1[%arg3, %4, %5, %arg9] : memref<1x225x225x3xf32, strided<[?, ?, ?, ?], offset: ?>>
//                   %7 = affine.load %0[%arg7, %arg8, %arg9, %arg6] : memref<3x3x3x32xf32, strided<[?, ?, ?, ?], offset: ?>>
//                   %8 = affine.load %alloc[%arg3, %arg4, %arg5, %arg6] : memref<1x112x112x32xf32>
//                   %9 = arith.mulf %6, %7 : f32
//                   %10 = arith.addf %8, %9 : f32
//                   affine.store %10, %alloc[%arg3, %arg4, %arg5, %arg6] : memref<1x112x112x32xf32>
//                 }
//               }
//             }
//           }
//         }
//       }
//     }
//     %3 = bufferization.to_tensor %alloc : memref<1x112x112x32xf32>
//     return %3 : tensor<1x112x112x32xf32>
//   }
// }

// #map = affine_map<(d0, d1) -> (d0 * 2 + d1)>
// #map1 = affine_map<(d0) -> (d0 * 2)>
// #map2 = affine_map<(d0) -> (d0 * -2 + 225, 17)>
// module {
//   func.func @conv(%arg0: tensor<1x225x225x3xf32>, %arg1: tensor<3x3x3x32xf32>, %arg2: tensor<1x112x112x32xf32>) -> tensor<1x112x112x32xf32> {
//     %c0 = arith.constant 0 : index
//     %c1 = arith.constant 1 : index
//     %c8 = arith.constant 8 : index
//     %c112 = arith.constant 112 : index
//     %c32 = arith.constant 32 : index
//     %c3 = arith.constant 3 : index
//     %0 = scf.for %arg3 = %c0 to %c112 step %c1 iter_args(%arg4 = %arg2) -> (tensor<1x112x112x32xf32>) {
//       %1 = scf.for %arg5 = %c0 to %c112 step %c8 iter_args(%arg6 = %arg4) -> (tensor<1x112x112x32xf32>) {
//         %2 = scf.for %arg7 = %c0 to %c32 step %c8 iter_args(%arg8 = %arg6) -> (tensor<1x112x112x32xf32>) {
//           %3 = scf.for %arg9 = %c0 to %c3 step %c1 iter_args(%arg10 = %arg8) -> (tensor<1x112x112x32xf32>) {
//             %4 = affine.apply #map(%arg3, %arg9)
//             %5 = affine.apply #map1(%arg5)
//             %6 = affine.min #map2(%arg5)
//             %extracted_slice = tensor.extract_slice %arg0[0, %4, %5, 0] [1, 1, %6, 3] [1, 1, 1, 1] : tensor<1x225x225x3xf32> to tensor<1x1x?x3xf32>
//             %extracted_slice_0 = tensor.extract_slice %arg1[%arg9, 0, 0, %arg7] [1, 3, 3, 8] [1, 1, 1, 1] : tensor<3x3x3x32xf32> to tensor<1x3x3x8xf32>
//             %extracted_slice_1 = tensor.extract_slice %arg10[0, %arg3, %arg5, %arg7] [1, 1, 8, 8] [1, 1, 1, 1] : tensor<1x112x112x32xf32> to tensor<1x1x8x8xf32>
//             %extracted_slice_2 = tensor.extract_slice %extracted_slice[0, 0, 0, 0] [1, 1, %6, 3] [1, 1, 1, 1] : tensor<1x1x?x3xf32> to tensor<1x?x3xf32>
//             %extracted_slice_3 = tensor.extract_slice %extracted_slice_0[0, 0, 0, 0] [1, 3, 3, 8] [1, 1, 1, 1] : tensor<1x3x3x8xf32> to tensor<3x3x8xf32>
//             %extracted_slice_4 = tensor.extract_slice %extracted_slice_1[0, 0, 0, 0] [1, 1, 8, 8] [1, 1, 1, 1] : tensor<1x1x8x8xf32> to tensor<1x8x8xf32>
//             %7 = linalg.conv_1d_nwc_wcf {dilations = dense<1> : vector<1xi64>, strides = dense<2> : vector<1xi64>} ins(%extracted_slice_2, %extracted_slice_3 : tensor<1x?x3xf32>, tensor<3x3x8xf32>) outs(%extracted_slice_4 : tensor<1x8x8xf32>) -> tensor<1x8x8xf32>
//             %inserted_slice = tensor.insert_slice %7 into %extracted_slice_1[0, 0, 0, 0] [1, 1, 8, 8] [1, 1, 1, 1] : tensor<1x8x8xf32> into tensor<1x1x8x8xf32>
//             %inserted_slice_5 = tensor.insert_slice %inserted_slice into %arg10[0, %arg3, %arg5, %arg7] [1, 1, 8, 8] [1, 1, 1, 1] : tensor<1x1x8x8xf32> into tensor<1x112x112x32xf32>
//             scf.yield %inserted_slice_5 : tensor<1x112x112x32xf32>
//           }
//           scf.yield %3 : tensor<1x112x112x32xf32>
//         }
//         scf.yield %2 : tensor<1x112x112x32xf32>
//       }
//       scf.yield %1 : tensor<1x112x112x32xf32>
//     }
//     return %0 : tensor<1x112x112x32xf32>
//   }
// }