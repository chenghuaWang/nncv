import torch
import torchvision.models as models
import torch_mlir


net = models.vgg11(
    weights=models.VGG11_Weights.DEFAULT
)
net.train(False)
module = torch_mlir.compile(net, torch.ones(
    1, 3, 256, 256, dtype=torch.float32), output_type="linalg-on-tensors")
with open("m.mlir", "w") as f:
    # large_elements_limit=0
    f.write(module.operation.get_asm())
