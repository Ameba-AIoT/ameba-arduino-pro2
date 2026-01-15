## To run server: python whisper_llm_server.py
## To run client: python post_audio.py (to post hello_howareyou.mp4)

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import Optional
import uvicorn
import base64
import uuid
import asyncio
import whisper
import os

# Load Whisper model once at startup
ASR = whisper.load_model("base")

app = FastAPI()

class Base64Data(BaseModel):
    image_base64_string: Optional[str] = None
    audio_base64_string: Optional[str] = None

def decode_base64(data: str) -> bytes:
    """
    Decode base64 strings safely.
    Handles strings with data:image/...;base64, or data:audio/...;base64, prefixes.
    """
    if "," in data:
        data = data.split(",", 1)[1]
    return base64.b64decode(data)

@app.post("/audio")
async def save_audio(data: Base64Data):
    try:
        uid = uuid.uuid4().hex
        transcription = None

        # Save image if provided
        if data.image_base64_string:
            image_path = f"{uid}.jpg"
            with open(image_path, "wb") as img_file:
                img_file.write(decode_base64(data.image_base64_string))

        # Save and transcribe audio if provided
        if data.audio_base64_string:
            audio_path = f"{uid}.mp4"
            audio_bytes = decode_base64(data.audio_base64_string)

            # Check if audio is not empty
            if len(audio_bytes) == 0:
                return {"message": "Audio data is empty", "id": uid, "text": None}

            # Save audio file
            with open(audio_path, "wb") as audio_file:
                audio_file.write(audio_bytes)

            # Transcribe audio using Whisper (non-blocking)
            result = await asyncio.to_thread(ASR.transcribe, audio_path)
            transcription = result.get("text", "")

        return {
            "message": "Files processed successfully",
            "id": uid,
            "text": transcription
        }

    except Exception as e:
        # Log the real error for debugging
        print("Error in /audio:", e)
        raise HTTPException(status_code=500, detail=str(e))

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000, log_level="info")

