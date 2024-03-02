import torch
import torch_mlir
model = torch.hub.load("ultralytics/yolov5", "yolov5s", pretrained=True)
model.train(False)
module = torch_mlir.compile(model, torch.ones(
    1, 3, 224, 224), output_type="linalg-on-tensors")
