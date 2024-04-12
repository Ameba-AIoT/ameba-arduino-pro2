## To run server: python whisper_llm_server.py
## To run client: python post_audio.py (to post hello_howareyou.mp4)

# pip install git+https://github.com/openai/whisper.git
# pip install fastapi uvicorn
# pip install nest-asyncio
# pip install accelerate

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import uvicorn
import base64

import whisper
ASR = whisper.load_model("base")


app = FastAPI()

class Base64Data(BaseModel):
    image_base64_string: str
    audio_base64_string: str

@app.post("/audio")
async def save_mp4(data: Base64Data):
    try:
        # Decode the base64 string
        decoded_image_data = base64.b64decode(data.image_base64_string)
        decoded_audio_data = base64.b64decode(data.audio_base64_string)
        
        # print(decoded_data)
        #Save the decoded data to an MP4 file
        with open("output.jpg", "wb") as fileone:
            fileone.write(decoded_image_data)
        #Save the decoded data to an MP4 file
        with open("output.mp4", "wb") as filetwo:
            filetwo.write(decoded_audio_data)
            
        #Whisper transcribe
        #result = ASR.transcribe("output.mp4")
        #print("ASR: "+result["text"])
        
        return {"message": "MP4 file saved successfully"}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

if __name__ == "__main__":
    uvicorn.run(app, host="192.168.3.4", port=8000, log_level="info")
