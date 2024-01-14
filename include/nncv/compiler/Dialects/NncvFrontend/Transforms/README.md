# NNCV Frontend Transfroms Pipeline

The pipeline here is static. Will not use transform dialect. And no external hyper parameters requires.

1. MLProgram Bufferize Pass
    Eliminate unused ml_program.global Op

2. Convert Conv2D1x1 To Matmul Pass
3. Convert Conv2D to Image2Col algorithm Pass(optional, default enable=false)
4. Pad LinalgOps To Integer Multiple Pass(default padding size=4)
    - Convert `linalg.depthwise_conv_2d_nhwc_hwcm with depth_multiplier=1` To `linalg.depthwise_conv_2d_nhwc_hwc`

    - Convert `linalg.depthwise_conv_2d_nhwc_hwcm_q with depth_multiplier=1` To `linalg.depthwise_conv_2d_nhwc_hwc_q`
5. 