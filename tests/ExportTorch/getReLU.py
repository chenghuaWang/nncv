import torch
import torch.nn as nn
import torch_mlir


class net_bached_relu(nn.Module):
    def __init__(self, *args, **kwargs) -> None:
        super(net_bached_relu, self).__init__(*args, **kwargs)
        self.relu = nn.ReLU()

    def forward(self, x):
        return self.relu(x)


if __name__ == "__main__":
    model = net_bached_relu()
    model.train(False)
    module = torch_mlir.compile(model, torch.ones(
        1, 3, 224, 224), output_type="linalg-on-tensors")
    with open("data.mlir", "w") as f:
        f.write(module.operation.get_asm())
