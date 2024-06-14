#Credits to Prof Richard for testing the LLM models.
##Disclaimer: Large language models require a strong GPU, such as NVIDIA GPUs and selected AMD GPUs. 
##If you are running purely on CPU, please make sure that you are not running the mediatek one. Run the Mamba-130M.

##Set up server environment:
##pip install requests flask
##pip install git+https://github.com/openai/whisper.git
##pip install einops
##pip install transformers


## To run server: python3 whisper_llm_server.py
## To run client: python3 post_audio.py


import base64
import time
from flask import Flask, request, jsonify
import whisper
model = whisper.load_model("base")

import transformers
from transformers import AutoModelForCausalLM , AutoTokenizer

llm_name = "Q-bert/Mamba-130M"
#llm_name = "MediaTek-Research/Breeze-7B-Base-v0.1"
LLM = AutoModelForCausalLM.from_pretrained(llm_name, trust_remote_code=True)
tokenizer = AutoTokenizer.from_pretrained(llm_name)

app = Flask(__name__)

@app.route("/hello", methods=['GET'])
def hello():
    return "hello"

@app.route("/audio", methods=['POST'])
def audio():
    if request.method == 'POST':
        # Access the raw input stream of the request
        stream = request.stream
        
        # Read the stream in chunks
        CHUNK_SIZE = 1024  # Adjust chunk size as needed
        data = b''
        while True:
            chunk = stream.read(CHUNK_SIZE)
            if not chunk:
                break
            data += chunk
        
        # Print the binary stream
        # print("Received POST request data:", data)
        
        decoded_data = base64.b64decode(data)
        
        timestamp = int(time.time())
        filename = "audio_file_" + str(timestamp) + ".mp4";
        
        with open(filename, "wb") as audio_file:
            audio_file.write(decoded_data)
            
        # transcribe
        result = model.transcribe(filename) 
        print(result["text"])
        
        prompt = result["text"]
        input_ids = tokenizer.encode(prompt, return_tensors="pt")
        output = LLM.generate(input_ids, max_length=64, num_beams=5, no_repeat_ngram_size=2)
        generated_text = tokenizer.decode(output[0], skip_special_tokens=True)
        print("LLM: "+generated_text) 

        return jsonify(generated_text)    

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000, debug=True)
