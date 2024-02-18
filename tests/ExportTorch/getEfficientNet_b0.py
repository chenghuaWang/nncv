import torch
import torchvision.models as models
import torch_mlir

efficientnet_b0 = models.efficientnet_b0(
    weights=models.EfficientNet_B0_Weights.DEFAULT)
efficientnet_b0.train(False)
module = torch_mlir.compile(efficientnet_b0, torch.ones(
    1, 1, 224, 224, dtype=torch.float32), output_type="linalg-on-tensors")
with open("data.txt", "w") as f:
    f.write(module.operation.get_asm())
