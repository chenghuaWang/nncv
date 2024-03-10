#map2 = affine_map<(d0, d1, d2) -> (d2, d1)>
#map5 = affine_map<(d0) -> (d0 * -128 + 1, 128)>
#map6 = affine_map<(d0) -> (d0 * -128 + 1000, 128)>
#map7 = affine_map<(d0) -> (d0 * 128)>
#map8 = affine_map<()[s0] -> (s0 ceildiv 16)>
#map9 = affine_map<(d0)[s0] -> (d0 * -16 + s0, 16)>
#map10 = affine_map<(d0) -> (d0 * 16)>
#map11 = affine_map<(d0, d1, d2) -> (d0, d2)>
#map12 = affine_map<(d0, d1, d2) -> (d0, d1)>
module {
    scf.parallel (%arg1, %arg2) = (%c0_268, %c0_269) to (%c1_270, %c8_271) step (%c1_272, %c1_273) {
      %68 = affine.min #map5(%arg1)
      %69 = affine.min #map6(%arg2)
      %70 = affine.apply #map7(%arg1)
      %71 = affine.apply #map7(%arg2)
      %subview_280 = memref.subview %expand_shape_259[%70, 0] [%68, 512] [1, 1] : memref<1x512xf32> to memref<?x512xf32, strided<[512, 1], offset: ?>>
      %subview_281 = memref.subview %alloc_260[0, %71] [512, %69] [1, 1] : memref<512x1000xf32> to memref<512x?xf32, strided<[1000, 1], offset: ?>>
      %subview_282 = memref.subview %alloc_267[%70, %71] [%68, %69] [1, 1] : memref<1x1000xf32> to memref<?x?xf32, strided<[1000, 1], offset: ?>>
      %72 = affine.apply #map8()[%68]
      %73 = affine.apply #map8()[%69]
      %c0_283 = arith.constant 0 : index
      %c0_284 = arith.constant 0 : index
      %c1_285 = arith.constant 1 : index
      %c1_286 = arith.constant 1 : index
      scf.parallel (%arg3, %arg4) = (%c0_283, %c0_284) to (%72, %73) step (%c1_285, %c1_286) {
        %74 = affine.min #map9(%arg3)[%68]
        %75 = affine.min #map9(%arg4)[%69]
        %76 = affine.apply #map10(%arg3)
        %77 = affine.apply #map10(%arg4)
        %subview_287 = memref.subview %subview_280[%76, 0] [%74, 512] [1, 1] : memref<?x512xf32, strided<[512, 1], offset: ?>> to memref<?x512xf32, strided<[512, 1], offset: ?>>
        %subview_288 = memref.subview %subview_281[0, %77] [512, %75] [1, 1] : memref<512x?xf32, strided<[1000, 1], offset: ?>> to memref<512x?xf32, strided<[1000, 1], offset: ?>>
        %subview_289 = memref.subview %subview_282[%76, %77] [%74, %75] [1, 1] : memref<?x?xf32, strided<[1000, 1], offset: ?>> to memref<?x?xf32, strided<[1000, 1], offset: ?>>
        scf.for %arg5 = %c0 to %c512 step %c16 {
          %subview_290 = memref.subview %subview_287[0, %arg5] [%74, 16] [1, 1] : memref<?x512xf32, strided<[512, 1], offset: ?>> to memref<?x16xf32, strided<[512, 1], offset: ?>>
          %subview_291 = memref.subview %subview_288[%arg5, 0] [16, %75] [1, 1] : memref<512x?xf32, strided<[1000, 1], offset: ?>> to memref<16x?xf32, strided<[1000, 1], offset: ?>>
          %78 = vector.create_mask %74, %c16 : vector<16x16xi1>
          %79 = vector.transfer_read %subview_290[%c0, %c0], %cst_3, %78 {in_bounds = [true, true]} : memref<?x16xf32, strided<[512, 1], offset: ?>>, vector<16x16xf32>
          %80 = vector.create_mask %c16, %75 : vector<16x16xi1>
          %81 = vector.transfer_read %subview_291[%c0, %c0], %cst_3, %80 {in_bounds = [true, true]} : memref<16x?xf32, strided<[1000, 1], offset: ?>>, vector<16x16xf32>
          %82 = vector.create_mask %74, %75 : vector<16x16xi1>
          %83 = vector.transfer_read %subview_289[%c0, %c0], %cst_3, %82 {in_bounds = [true, true]} : memref<?x?xf32, strided<[1000, 1], offset: ?>>, vector<16x16xf32>
          %84 = vector.create_mask %74, %75, %c16 : vector<16x16x16xi1>
          %85 = vector.mask %84 { vector.contract {indexing_maps = [#map11, #map2, #map12], iterator_types = ["parallel", "parallel", "reduction"], kind = #vector.kind<add>} %79, %81, %83 : vector<16x16xf32>, vector<16x16xf32> into vector<16x16xf32> } : vector<16x16x16xi1> -> vector<16x16xf32>
          vector.transfer_write %85, %subview_289[%c0, %c0], %82 {in_bounds = [true, true]} : vector<16x16xf32>, memref<?x?xf32, strided<[1000, 1], offset: ?>>
        }
        scf.reduce 
      } {mapping = [#gpu.loop_dim_map<processor = thread_x, map = (d0) -> (d0), bound = (d0) -> (d0)>, #gpu.loop_dim_map<processor = thread_y, map = (d0) -> (d0), bound = (d0) -> (d0)>]}
      scf.reduce 
    } {mapping = [#gpu.loop_dim_map<processor = block_x, map = (d0) -> (d0), bound = (d0) -> (d0)>, #gpu.loop_dim_map<processor = block_y, map = (d0) -> (d0), bound = (d0) -> (d0)>]}
}