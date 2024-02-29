##Set up server environment:
##pip install requests flask
##pip install git+https://github.com/openai/whisper.git

## To run server: python3 whisper_server.py
## To run client: python3 post_audio.py

import base64
import time
from flask import Flask, request, jsonify
import whisper
model = whisper.load_model("base")

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
        return jsonify(result["text"])
    

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000, debug=True)