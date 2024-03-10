import torch as t
import torch_mlir

import numpy


class twoParams(t.nn.Module):
    def __init__(self, *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)
        self.conv1 = t.nn.Conv2d(
            in_channels=3, out_channels=1, kernel_size=3, bias=False)
        self.conv2 = t.nn.Conv2d(
            in_channels=1, out_channels=1, kernel_size=5, bias=False)
        # init all params
        self.conv1.weight.data = t.Tensor([[[[1, 0, 0],
                                             [0, 0, 0],
                                             [0, 0, 0]],
                                            [[0, 0, 0],
                                             [0, 1, 0],
                                             [0, 0, 0]],
                                            [[0, 0, 0],
                                             [0, 0, 0],
                                             [0, 0, 1]]]])
        self.conv2.weight.data = t.Tensor([[[[1, 0, 0, 0, 0],
                                             [0, 1, 0, 0, 0],
                                             [0, 0, 1, 0, 0],
                                             [0, 0, 0, 1, 0],
                                             [0, 0, 0, 0, 1]]
                                            ]])

    def forward(self, x):
        return self.conv2(self.conv1(x))


if __name__ == "__main__":
    net = twoParams()
    net.train(False)
    module = torch_mlir.compile(net, t.ones(
        1, 3, 224, 224), output_type="linalg-on-tensors")
    with open("data.mlir", "w") as f:
        f.write(module.operation.get_asm())
