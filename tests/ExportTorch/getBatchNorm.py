import torch
import torch.nn as nn
import torch_mlir


class net_bached_bacthnorm2d(nn.Module):
    def __init__(self, *args, **kwargs) -> None:
        super(net_bached_bacthnorm2d, self).__init__(*args, **kwargs)
        self.batch_norm = nn.BatchNorm2d(num_features=3)

    def forward(self, x):
        return self.batch_norm(x)


if __name__ == "__main__":
    model = net_bached_bacthnorm2d()
    model = model.train(False)
    module = torch_mlir.compile(model, torch.ones(
        1, 3, 224, 224), output_type="linalg-on-tensors")
    with open("data.mlir", "w") as f:
        f.write(module.operation.get_asm())
