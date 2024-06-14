## To run server: python whisper_server.py
## To run client: python post_audio.py

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
        filename = "audio_file_" + str(timestamp) + ".mp4"
        
        with open(filename, "wb") as audio_file:
            audio_file.write(decoded_data)
            
        # transcribe
        result = model.transcribe(filename) 
        print(result["text"])
        return jsonify(result["text"])
        
@app.route("/image", methods=['POST'])
def image():
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
        
        timestamp2 = int(time.time())
        imagename = "image_file_" + str(timestamp2) + ".jpg"
        
        with open(imagename, "wb") as image_file:
            image_file.write(decoded_data)
    
    return "Uploaded"
    

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000, debug=True)
