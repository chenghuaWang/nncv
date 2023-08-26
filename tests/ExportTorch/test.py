import torch
import torchvision.models as models
from torchvision import transforms
import torch_mlir

efficientnet_b0 = models.efficientnet_b0(pretrained=True)
efficientnet_b0.train(False)
module = torch_mlir.compile(efficientnet_b0, torch.ones(
    1, 3, 224, 224), output_type="linalg-on-tensors")
with open("/content/data.txt", "w") as f:
    f.write(module.operation.get_asm())
