import time
start = time.time()
import g2pk
g2p = g2pk.G2p()

import re, os
import sys
from unicodedata import normalize
# import IPython

from fastapi import FastAPI, Form
from pydantic import BaseModel 
from fastapi.middleware.cors import CORSMiddleware

# 🚨
# sys.path.remove("")
# sys.path.remove("/home/kseek/TTS4note/TTS")
#sys.path.remove("/home/kseek/seedBox/NLP/jupyter/kospeech")
# sys.path.remove("/home/kseek/boxboxbox/g2pK")
# sys.path.remove("/home/kseek/.local/lib/python3.8/site-packages")
# sys.path.remove("/home/kseek/TTS")
#sys.path.remove("/home/aiserver/ai/STT/kospeech")
#print("🚨 module path🚨")
#for i in sys.path:
#  print(i)
#print("\n")
# 🚨

start_synthesizer = time.time()
from TTS.utils.synthesizer import Synthesizer
# 이 친구의 init에서 시간을 많이 먹는거아닌가.. -> 아님.
# synthesizer.py의 torch가 가장 오랜시간을 잡음. 약 0.5초, 나머지는 0.45, 0.02 정도..
# print("👉 import synthesizer : ", time.time()-start_synthesizer);

# print("👉 g2p load end : ", time.time()-start);

def normalize_text(text):
    text = text.strip()

    for c in ",;:":
        text = text.replace(c, ".")
    # text = remove_duplicated_punctuations(text)

    text = jamo_text(text)
    
    # g2p 안쓰면 이부분을 주석하세요
    init_g2pk_time = time.time()
    
    text = g2p.idioms(text)
    # print("🗣 g2p.idioms : ", time.time()-init_g2pk_time);
    text = g2pk.english.convert_eng(text, g2p.cmu)
    # print("🗣 g2p convert eng : ", time.time()-init_g2pk_time);
    text = g2pk.utils.annotate(text, g2p.mecab)
    # print("🗣 g2pk.utils.annotate : ", time.time()-init_g2pk_time);
    text = g2pk.numerals.convert_num(text)
    # print("🗣 g2pk.numerals.convert_num : ", time.time()-init_g2pk_time);
    # g2p
    
    text = re.sub("/[PJEB]", "", text)

    text = alphabet_text(text)

    # remove unreadable characters
#    print("✍ before ",text);
    text = normalize("NFD", text)
    text = "".join(c for c in text if c in symbols)
    text = normalize("NFC", text)
#    print("✍ after ",text);

    text = text.strip()
    if len(text) == 0:
        return ""

    # only single punctuation
    if text in '.!?':
        return punctuation_text(text)

    # append punctuation if there is no punctuation at the end of the text
    if text[-1] not in '.!?':
        text += ' '

    return text


def remove_duplicated_punctuations(text):
    text = re.sub(r"[.?!]+\?", "?", text)
    text = re.sub(r"[.?!]+!", "!", text)
    text = re.sub(r"[.?!]+\.", ".", text)
    return text


def split_text(text):
    # text = remove_duplicated_punctuations(text)

    texts = []

    # ?와 !로 나눠지는것을 방지하기 위해
    # for subtext in re.findall(r'[^.!?\n]*[.!?\n]', text):
    for subtext in re.findall(r'[^.\n]*[.\n]', text):
        texts.append(subtext.strip())

    # print("💻 split_text : ",texts)
    return texts


def alphabet_text(text):
    text = re.sub(r"(a|A)", "에이", text)
    text = re.sub(r"(b|B)", "비", text)
    text = re.sub(r"(c|C)", "씨", text)
    text = re.sub(r"(d|D)", "디", text)
    text = re.sub(r"(e|E)", "이", text)
    text = re.sub(r"(f|F)", "에프", text)
    text = re.sub(r"(g|G)", "쥐", text)
    text = re.sub(r"(h|H)", "에이치", text)
    text = re.sub(r"(i|I)", "아이", text)
    text = re.sub(r"(j|J)", "제이", text)
    text = re.sub(r"(k|K)", "케이", text)
    text = re.sub(r"(l|L)", "엘", text)
    text = re.sub(r"(m|M)", "엠", text)
    text = re.sub(r"(n|N)", "엔", text)
    text = re.sub(r"(o|O)", "오", text)
    text = re.sub(r"(p|P)", "피", text)
    text = re.sub(r"(q|Q)", "큐", text)
    text = re.sub(r"(r|R)", "알", text)
    text = re.sub(r"(s|S)", "에스", text)
    text = re.sub(r"(t|T)", "티", text)
    text = re.sub(r"(u|U)", "유", text)
    text = re.sub(r"(v|V)", "브이", text)
    text = re.sub(r"(w|W)", "더블유", text)
    text = re.sub(r"(x|X)", "엑스", text)
    text = re.sub(r"(y|Y)", "와이", text)
    text = re.sub(r"(z|Z)", "지", text)

    return text


def punctuation_text(text):
    # 문장부호
    text = re.sub(r"!", "느낌표", text)
    text = re.sub(r"\?", "물음표", text)
    text = re.sub(r"\.", "마침표", text)

    return text


def jamo_text(text):
    # 기본 자모음
    text = re.sub(r"ㄱ", "기역", text)
    text = re.sub(r"ㄴ", "니은", text)
    text = re.sub(r"ㄷ", "디귿", text)
    text = re.sub(r"ㄹ", "리을", text)
    text = re.sub(r"ㅁ", "미음", text)
    text = re.sub(r"ㅂ", "비읍", text)
    text = re.sub(r"ㅅ", "시옷", text)
    text = re.sub(r"ㅇ", "이응", text)
    text = re.sub(r"ㅈ", "지읒", text)
    text = re.sub(r"ㅊ", "치읓", text)
    text = re.sub(r"ㅋ", "키읔", text)
    text = re.sub(r"ㅌ", "티읕", text)
    text = re.sub(r"ㅍ", "피읖", text)
    text = re.sub(r"ㅎ", "히읗", text)
    text = re.sub(r"ㄲ", "쌍기역", text)
    text = re.sub(r"ㄸ", "쌍디귿", text)
    text = re.sub(r"ㅃ", "쌍비읍", text)
    text = re.sub(r"ㅆ", "쌍시옷", text)
    text = re.sub(r"ㅉ", "쌍지읒", text)
    text = re.sub(r"ㄳ", "기역시옷", text)
    text = re.sub(r"ㄵ", "니은지읒", text)
    text = re.sub(r"ㄶ", "니은히읗", text)
    text = re.sub(r"ㄺ", "리을기역", text)
    text = re.sub(r"ㄻ", "리을미음", text)
    text = re.sub(r"ㄼ", "리을비읍", text)
    text = re.sub(r"ㄽ", "리을시옷", text)
    text = re.sub(r"ㄾ", "리을티읕", text)
    text = re.sub(r"ㄿ", "리을피읍", text)
    text = re.sub(r"ㅀ", "리을히읗", text)
    text = re.sub(r"ㅄ", "비읍시옷", text)
    text = re.sub(r"ㅏ", "아", text)
    text = re.sub(r"ㅑ", "야", text)
    text = re.sub(r"ㅓ", "어", text)
    text = re.sub(r"ㅕ", "여", text)
    text = re.sub(r"ㅗ", "오", text)
    text = re.sub(r"ㅛ", "요", text)
    text = re.sub(r"ㅜ", "우", text)
    text = re.sub(r"ㅠ", "유", text)
    text = re.sub(r"ㅡ", "으", text)
    text = re.sub(r"ㅣ", "이", text)
    text = re.sub(r"ㅐ", "애", text)
    text = re.sub(r"ㅒ", "얘", text)
    text = re.sub(r"ㅔ", "에", text)
    text = re.sub(r"ㅖ", "예", text)
    text = re.sub(r"ㅘ", "와", text)
    text = re.sub(r"ㅙ", "왜", text)
    text = re.sub(r"ㅚ", "외", text)
    text = re.sub(r"ㅝ", "워", text)
    text = re.sub(r"ㅞ", "웨", text)
    text = re.sub(r"ㅟ", "위", text)
    text = re.sub(r"ㅢ", "의", text)

    return text


def normalize_multiline_text(long_text):
    texts = split_text(long_text)
    # print(texts)
    normalized_texts = [normalize_text(text).strip() for text in texts]
    # print(normalized_texts)
    return [text for text in normalized_texts if len(text) > 0]

# 3. 학습한 모델 불러오기
syn_start = time.time();

synthesizer = Synthesizer(
# "/home/aiserver/ai/TTSmodel/glowtts_training_700_1/best_model.pth.tar",
# "/home/aiserver/ai/TTSmodel/glowtts_training_700_1/config.json",
   "/home/aiserver/ai/TTSmodel/0511_training/glowtts_checkpoint_30000.pth.tar",
   "/home/aiserver/ai/TTSmodel/0511_training/glowtts_config.json",
    None,
#   "/home/aiserver/ai/TTSmodel/hifigan_training_700_2/best_model_307123.pth.tar",
#   "/home/aiserver/ai/TTSmodel/hifigan_training_700_1/config.json",
  "/home/aiserver/ai/TTSmodel/0511_training/a4000_best_model_315313.pth.tar",
  "/home/aiserver/ai/TTSmodel/0511_training/a4000_config.json",
    # None,
    # None,
)

print("👉 only Synthesizer end : ",time.time()-syn_start) # 여기까지 0.5초
# symbols_start = time.time();
symbols = synthesizer.tts_config.characters.characters
# print(symbols)
# print("👉 symbol end : ",time.time()-symbols_start)

app = FastAPI()

origins = ["*"]
origins=[
    "http://127.0.0.1",
    "http://localhost",
]
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
#    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)



# class Item(BaseModel):
#     text: str

#class text(BaseModel):
    # text: str
#    pass

#class text(BaseModel):
#    text: str

@app.post("/TTS/")
#@app.get("/TTS/")
#def makeTTS(text: str, fileName: str):
async def makeTTS(text: str=Form(...), fileName: str=Form(...)):
    makeTTSTime = time.time()
    # print(type(text))
    # if(text_str):
    #     print(type(text_str))
    if(text):
        print("inpurt text : ",text)
        print("🙊initalize Time: ",time.time()-makeTTSTime)

        texts = "샘플문장 입니다"
        # texts = text+".\n"
        texts = text+"\n"
        # print(texts)
        print(fileName)

        import soundfile as sf
        inference_start = time.time();

        normalize_multiline_text(texts)
        # print("normalized end")
        # print("type normalize text : ",type(normalize_multiline_text(texts)))

        # list to str
        texts = "".join(map(str,normalize_multiline_text(texts)))

        wav = synthesizer.tts(texts, None, None)
        print("Inference : ",time.time()-inference_start); # 0.2 sec
        # print("tts end")
        output_name = '/home/aiserver/ai/TTS/soundData/'+fileName+".wav"
#        output_name = '/home/aiserver/ai/TTS/soundData/0.wav'
        # output_name = '/usr/share/nginx/demo/TTS/audio/0.wav'
        sf.write(output_name, wav, 22050)
        print("output time : ",time.time()-inference_start)
#       print("🙊output Time : ",time.time()-makeTTSTime) # 0.28 sec

        # os.system("whoami")
        cmd = "cp /home/aiserver/ai/TTS/soundData/"+fileName+".wav /home/aiserver/ai/demo/TTS/audio/"+fileName+".wav"
        os.system(cmd)
#        os.system("cp /home/aiserver/ai/TTS/soundData/0.wav /home/aiserver/ai/demo/TTS/audio/0.wav")
#       print("copy time : ",time.time()-inference_start)

        # for text in Synthesizer.normalize_multiline_text(texts):
        #     wav = synthesizer.tts(text, None, None)
        #     output_name = '/home/kseek/boxboxbox/TTS/soundData/sample.wav'
        #     sf.write(output_name, wav, 22050)
        #     i+=1
        # print("Inference : ",time.time()-inference_start); # 0.2초
        print("👉 total time : ",time.time()-makeTTSTime);
#        texts += "123";
        return texts

'''
# 4. 음성 합성
texts = """
이제 본격적으로 시작해 볼까요? 첫번째 문제 보여주세요! 문제 나갑니다.  정답은 천사였습니다! 1등 그 영광의 주인공은 바로 홍길동님! 축하드립니다!  여러분들의 선택이 궁금한데요 어떤걸 많이 선택하였을지 그 결과를 공개합니다.
"""
# import librosa    // Synthesizer에 포함되어 제거
import soundfile as sf
inference_start = time.time();

i=10
for text in normalize_multiline_text(texts):
    wav = synthesizer.tts(text, None, None)
    # IPython.display.display(IPython.display.Audio(wav, rate=22050))
    # output_name = '/home/kseek/boxboxbox/ChoTTS/output/%d.wav'%(i)
    # sf.write(output_name, wav, 22050)

    output_name = '/home/aiserver/ai/TTS/soundData/%d.wav'%(i)
    sf.write(output_name, wav, 22050)
    i+=1
print("Inference : ",time.time()-inference_start); # 0.2초
print("👉 total time : ",time.time()-start);
'''

'''
import torch = 0.6
import g2pk = 0.1
synthesizer(glowtts + hifigan) = 0.6
inference = 0.2
0.3 ??

'''
