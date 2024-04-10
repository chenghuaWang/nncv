import torch
import torch.nn as nn
import torchvision.models as models
import torch_mlir


class MHA(nn.Module):
    def __init__(self, *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)
        self.mha = nn.MultiheadAttention(2048, 8, 0, False)

    def forward(self, x):
        return self.mha(x, x, x)


net = MHA()
net.train(False)
out = net(torch.ones(
    1, 1, 2048, dtype=torch.float32))
exit(0)
module = torch_mlir.compile(net, torch.ones(
    1, 1, 1, 2048, dtype=torch.float32), output_type="linalg-on-tensors")
with open("m.mlir", "w") as f:
    f.write(module.operation.get_asm())
