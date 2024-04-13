from transformers import AutoModelForCausalLM, AutoTokenizer
import torch
import torch_mlir

tokenizer = AutoTokenizer.from_pretrained("Qwen/Qwen1.5-0.5B")


class optModel(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.model = AutoModelForCausalLM.from_pretrained(
            "Qwen/Qwen1.5-0.5B",
            torch_dtype="auto",
            device_map="auto"
        )
        self.model.eval()

    def forward(self, tokens):
        attention_mask = torch.ones(tokens.shape, dtype=torch.long)
        return self.model.forward(input_ids=tokens, attention_mask=attention_mask)


test_input = tokenizer.encode(
    "Write me a poem about Machine Learning. Write me a poem about Machine Learning.", return_tensors="pt")

model = optModel()
module = torch_mlir.compile(
    model, test_input, output_type="linalg-on-tensors", use_make_fx=True)
with open("QWen2.mlir", "w") as f:
    # large_elements_limit=0
    f.write(module.operation.get_asm())
