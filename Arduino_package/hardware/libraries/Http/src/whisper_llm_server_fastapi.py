## To run server: python whisper_llm_server.py
## To run client: python post_audio.py (to post hello_howareyou.mp4)

# pip install git+https://github.com/openai/whisper.git
# pip install fastapi uvicorn
# pip install nest-asyncio
# pip install accelerate

from fastapi import FastAPI, HTTPException
from fastapi.responses import Response
from pydantic import BaseModel
import uvicorn
import base64

import whisper
ASR = whisper.load_model("base")

import torch
import transformers
from transformers import AutoModelForCausalLM , AutoTokenizer

### https://huggingface.co/spaces/HuggingFaceH4/open_llm_leaderboard
#model_name = "Q-bert/Mamba-130M"
#model_name = "Q-bert/Mamba-370M"
#model_name = "Q-bert/Mamba-790M"
#model_name = "Q-bert/Mamba-1B"
#model_name = "Q-bert/Mamba-3B"
#model_name = "Q-bert/Mamba-3B-slimpj"
#model_name = "ckip-joint/bloom-3b-zh" # zh
#model_name = "google/gemma-1.1-7b-it"
#model_name = "microsoft/phi-2"
#model_name = "microsoft/Orca-2-7b"
#model_name = "mistralai/Mistral-7B-Instruct-v0.2"
#model_name = "openlm-research/open_llama_3b_v2"
#model_name = "openlm-research/open_llama_7b_v2"
#model_name = "meta-llama/Llama-2-7b-hf"
#model_name = "meta-llama/Llama-2-7b-chat-hf"
#model_name = "lmsys/vicuna-7b-v1.5"
#model_name = "lmsys/vicuna-7b-v1.5-16k"
#model_name = "Nexusflow/Starling-LM-7B-beta"

#model_name = "Qwen/Qwen1.5-7B-Chat" # 通义千问
#model_name = "01-ai/Yi-6B-Chat" # 零一万物
#model_name = "yentinglin/Taiwan-LLM-7B-v2.0.1-chat" # 台大
model_name = "MediaTek-Research/Breeze-7B-Instruct-v0.1" # 達哥
#model_name = "INX-TEXT/Bailong-instruct-7B" # zh 白龍

print(model_name)

#LLM = AutoModelForCausalLM.from_pretrained(model_name, trust_remote_code=True, torch_dtype="auto", device_map="cuda")
LLM = AutoModelForCausalLM.from_pretrained(model_name, trust_remote_code=True, torch_dtype=torch.bfloat16, device_map="cuda")
tokenizer = AutoTokenizer.from_pretrained(model_name)

import nest_asyncio
nest_asyncio.apply()

app = FastAPI()

class Base64Data(BaseModel):
    base64_string: str

@app.get("/")
def home():
    return Response("hello")

@app.post("/audio")
async def post_audio(data: Base64Data):
    try:
        #Decode the base64 string
        decoded_data = base64.b64decode(data.base64_string)
        
        # print(decoded_data)
        #Save the decoded data to an MP4 file
        with open("output.mp4", "wb") as f:
            f.write(decoded_data)
      
        # Whisper transcribe
        result = ASR.transcribe("output.mp4")
        print("ASR: "+result["text"])

        # LLM generate
        prompt = result["text"]
        input_ids = tokenizer.encode(prompt, return_tensors="pt").to("cuda")
        output = LLM.generate(input_ids, max_length=128, num_beams=5, no_repeat_ngram_size=2)
        generated_text = tokenizer.decode(output[0], skip_special_tokens=True)
        print("LLM: "+generated_text) 
        return Response(generated_text)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


if __name__ == "__main__":
    uvicorn.run(app, host="192.168.3.4", port=8000, log_level="info")