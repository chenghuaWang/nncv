import torch
import torchvision.models as models
import torch_mlir


net = models.mobilenet_v3_small(
    weights=models.MobileNet_V3_Small_Weights.DEFAULT
)
net.train(False)
module = torch_mlir.compile(net, torch.ones(
    1, 3, 256, 256, dtype=torch.float32), output_type="linalg-on-tensors")
with open("m.mlir", "w") as f:
    # large_elements_limit=0
    f.write(module.operation.get_asm())
