import torch
import torch.nn as nn
import torch_mlir


class net_pool2d_max(nn.Module):
    def __init__(self, *args, **kwargs) -> None:
        super(net_pool2d_max, self).__init__(*args, **kwargs)
        self.pool = nn.MaxPool2d(kernel_size=3)

    def forward(self, x):
        return self.pool(x)


if __name__ == "__main__":
    model = net_pool2d_max()
    model.train(False)
    module = torch_mlir.compile(model, torch.ones(
        1, 3, 224, 224), output_type="linalg-on-tensors")
    with open("data.mlir", "w") as f:
        f.write(module.operation.get_asm())
