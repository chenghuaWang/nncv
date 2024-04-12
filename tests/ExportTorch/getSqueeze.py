import torch
import torchvision.models as models
import torch_mlir
import time

net = models.squeezenet1_0(
    weights=models.SqueezeNet1_0_Weights.DEFAULT)
net.train(False)
module = torch_mlir.compile(net, torch.ones(
    1, 3, 256, 256, dtype=torch.float32), output_type="linalg-on-tensors")
with open("/media/wch/D/Project/mlir-test-place/Compare/SqueezeNet/m.mlir", "w") as f:
    f.write(module.operation.get_asm())
