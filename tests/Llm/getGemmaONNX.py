from transformers import GemmaForCausalLM, GemmaTokenizer
import torch


class optModel(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.model = GemmaForCausalLM.from_pretrained(
            "google/gemma-2b-it")
        self.model.eval()

    def forward(self, tokens):
        attention_mask = torch.ones(tokens.shape, dtype=torch.long)
        return self.model.forward(input_ids=tokens, attention_mask=attention_mask)


tokenizer = GemmaTokenizer.from_pretrained(
    "google/gemma-2b-it", torch_dtype=torch.bfloat16)
test_input = tokenizer.encode(
    "Write me a poem about Machine Learning. Write me a poem about Machine Learning.", return_tensors="pt")

model = optModel()
onnx_program = torch.onnx.export(model, test_input, "gemma-2b.onnx")
