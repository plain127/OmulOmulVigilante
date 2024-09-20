import torch
from transformers import AutoModelForSpeechSeq2Seq, AutoProcessor, pipeline

def voice2text(voice_path):
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    torch_dtype = torch.float16 if torch.cuda.is_available() else torch.float32
    model_id = "openai/whisper-large-v3"

    model = AutoModelForSpeechSeq2Seq.from_pretrained(
        model_id, torch_dtype=torch_dtype, low_cpu_mem_usage=True, use_safetensors=True
    )

    model.to(device)
    processor = AutoProcessor.from_pretrained(model_id)
    pipe = pipeline(
        "automatic-speech-recognition",
        model=model,
        tokenizer=processor.tokenizer,
        feature_extractor=processor.feature_extractor,
        max_new_tokens = 128,
        chunk_length_s = 30,
        batch_size = 16,
        return_timestamps = True,
        torch_dtype=torch_dtype,
        device=device
    )
    
    result_openai = pipe(voice_path, generate_kwargs={"language": "<|ko|>", "task": "transcribe"})
    
    with open('./client2voice/stt_file.txt', 'w', encoding='utf-8') as stt_file:
        stt_file.write(result_openai["text"])
    
    with open('./client2voice/stt_file.txt', 'r', encoding='utf-8') as file:
        file_content = file.read()
            
    return file_content
    
