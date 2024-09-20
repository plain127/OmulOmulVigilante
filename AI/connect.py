import uvicorn
import requests
import base64
import os
from fastapi import FastAPI, Body, Request, UploadFile, HTTPException
from fastapi.responses import JSONResponse
from omul_llm import OmulLLM
from omul_call import voice2text
from pydantic import BaseModel
from starlette.middleware.base import BaseHTTPMiddleware

app = FastAPI()

MAX_JSON_SIZE = 10 * 1024 * 1024  # 10MB

class LimitJSONSizeMiddleware(BaseHTTPMiddleware):
    async def dispatch(self, request: Request, call_next):
        # 요청 본문 크기 확인
        body = await request.body()
        if len(body) > MAX_JSON_SIZE:
            raise HTTPException(status_code=413, detail="Request body too large")
        response = await call_next(request)
        return response

app.add_middleware(LimitJSONSizeMiddleware)
    
@app.post('/result/{username}')
async def server2ai(username:str, request: Request, result: dict = Body(...)):
    user_agent = request.headers.get('token') 

    binary = result['EncodingSoundFile']
       
    binary_data = base64.b64decode(binary)
    
    with open('./voice.wav', 'wb') as wav_file:
        wav_file.write(binary_data)
        
    calling = voice2text('./voice.wav')
    
    distance = result['AverDistance']
    warning = result['Alerted']
    action = str(distance) + str(calling) + str(warning)
    
    omul = OmulLLM(action, './omul_backup.txt')
    score, reason = omul.run_llm()
    
    post_data = {
        "username": username,
        "score": int(score),
        "reason": reason
    }
    
    headers = {
        "token": user_agent
    }
 
    try:
        response = requests.post(f'http://Input Your Host & Port/result/ai/{username}', json=post_data, headers=headers)
        response.raise_for_status()
    except requests.exceptions.RequestException as e:
        print(f'실패: {e}')
 
    return None

if __name__ == '__main__':
    uvicorn.run(app, host='Input Your Host', port='{Input Your Port Number}')