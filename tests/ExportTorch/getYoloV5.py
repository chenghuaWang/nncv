import torch
import torch_mlir
model = torch.hub.load("ultralytics/yolov5", "yolov5s", pretrained=True)
model.train(False)
module = torch_mlir.compile(model, torch.randn(
    1, 3, 640, 640), output_type="linalg-on-tensors", use_make_fx=True)
with open("yolov5s.mlir", "w") as f:
    # large_elements_limit=0
    f.write(module.operation.get_asm())
