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

# π¨
# sys.path.remove("")
# sys.path.remove("/home/kseek/TTS4note/TTS")
#sys.path.remove("/home/kseek/seedBox/NLP/jupyter/kospeech")
# sys.path.remove("/home/kseek/boxboxbox/g2pK")
# sys.path.remove("/home/kseek/.local/lib/python3.8/site-packages")
# sys.path.remove("/home/kseek/TTS")
#sys.path.remove("/home/aiserver/ai/STT/kospeech")
#print("π¨ module pathπ¨")
#for i in sys.path:
#  print(i)
#print("\n")
# π¨

start_synthesizer = time.time()
from TTS.utils.synthesizer import Synthesizer
# μ΄ μΉκ΅¬μ initμμ μκ°μ λ§μ΄ λ¨Ήλκ±°μλκ°.. -> μλ.
# synthesizer.pyμ torchκ° κ°μ₯ μ€λμκ°μ μ‘μ. μ½ 0.5μ΄, λλ¨Έμ§λ 0.45, 0.02 μ λ..
# print("π import synthesizer : ", time.time()-start_synthesizer);

# print("π g2p load end : ", time.time()-start);

def normalize_text(text):
    text = text.strip()

    for c in ",;:":
        text = text.replace(c, ".")
    # text = remove_duplicated_punctuations(text)

    text = jamo_text(text)
    
    # g2p μμ°λ©΄ μ΄λΆλΆμ μ£ΌμνμΈμ
    init_g2pk_time = time.time()
    
    text = g2p.idioms(text)
    # print("π£ g2p.idioms : ", time.time()-init_g2pk_time);
    text = g2pk.english.convert_eng(text, g2p.cmu)
    # print("π£ g2p convert eng : ", time.time()-init_g2pk_time);
    text = g2pk.utils.annotate(text, g2p.mecab)
    # print("π£ g2pk.utils.annotate : ", time.time()-init_g2pk_time);
    text = g2pk.numerals.convert_num(text)
    # print("π£ g2pk.numerals.convert_num : ", time.time()-init_g2pk_time);
    # g2p
    
    text = re.sub("/[PJEB]", "", text)

    text = alphabet_text(text)

    # remove unreadable characters
#    print("β before ",text);
    text = normalize("NFD", text)
    text = "".join(c for c in text if c in symbols)
    text = normalize("NFC", text)
#    print("β after ",text);

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

    # ?μ !λ‘ λλ μ§λκ²μ λ°©μ§νκΈ° μν΄
    # for subtext in re.findall(r'[^.!?\n]*[.!?\n]', text):
    for subtext in re.findall(r'[^.\n]*[.\n]', text):
        texts.append(subtext.strip())

    # print("π» split_text : ",texts)
    return texts


def alphabet_text(text):
    text = re.sub(r"(a|A)", "μμ΄", text)
    text = re.sub(r"(b|B)", "λΉ", text)
    text = re.sub(r"(c|C)", "μ¨", text)
    text = re.sub(r"(d|D)", "λ", text)
    text = re.sub(r"(e|E)", "μ΄", text)
    text = re.sub(r"(f|F)", "μν", text)
    text = re.sub(r"(g|G)", "μ₯", text)
    text = re.sub(r"(h|H)", "μμ΄μΉ", text)
    text = re.sub(r"(i|I)", "μμ΄", text)
    text = re.sub(r"(j|J)", "μ μ΄", text)
    text = re.sub(r"(k|K)", "μΌμ΄", text)
    text = re.sub(r"(l|L)", "μ", text)
    text = re.sub(r"(m|M)", "μ ", text)
    text = re.sub(r"(n|N)", "μ", text)
    text = re.sub(r"(o|O)", "μ€", text)
    text = re.sub(r"(p|P)", "νΌ", text)
    text = re.sub(r"(q|Q)", "ν", text)
    text = re.sub(r"(r|R)", "μ", text)
    text = re.sub(r"(s|S)", "μμ€", text)
    text = re.sub(r"(t|T)", "ν°", text)
    text = re.sub(r"(u|U)", "μ ", text)
    text = re.sub(r"(v|V)", "λΈμ΄", text)
    text = re.sub(r"(w|W)", "λλΈμ ", text)
    text = re.sub(r"(x|X)", "μμ€", text)
    text = re.sub(r"(y|Y)", "μμ΄", text)
    text = re.sub(r"(z|Z)", "μ§", text)

    return text


def punctuation_text(text):
    # λ¬Έμ₯λΆνΈ
    text = re.sub(r"!", "λλν", text)
    text = re.sub(r"\?", "λ¬Όμν", text)
    text = re.sub(r"\.", "λ§μΉ¨ν", text)

    return text


def jamo_text(text):
    # κΈ°λ³Έ μλͺ¨μ
    text = re.sub(r"γ±", "κΈ°μ­", text)
    text = re.sub(r"γ΄", "λμ", text)
    text = re.sub(r"γ·", "λκ·Ώ", text)
    text = re.sub(r"γΉ", "λ¦¬μ", text)
    text = re.sub(r"γ", "λ―Έμ", text)
    text = re.sub(r"γ", "λΉμ", text)
    text = re.sub(r"γ", "μμ·", text)
    text = re.sub(r"γ", "μ΄μ", text)
    text = re.sub(r"γ", "μ§μ", text)
    text = re.sub(r"γ", "μΉμ", text)
    text = re.sub(r"γ", "ν€μ", text)
    text = re.sub(r"γ", "ν°μ", text)
    text = re.sub(r"γ", "νΌμ", text)
    text = re.sub(r"γ", "νμ", text)
    text = re.sub(r"γ²", "μκΈ°μ­", text)
    text = re.sub(r"γΈ", "μλκ·Ώ", text)
    text = re.sub(r"γ", "μλΉμ", text)
    text = re.sub(r"γ", "μμμ·", text)
    text = re.sub(r"γ", "μμ§μ", text)
    text = re.sub(r"γ³", "κΈ°μ­μμ·", text)
    text = re.sub(r"γ΅", "λμμ§μ", text)
    text = re.sub(r"γΆ", "λμνμ", text)
    text = re.sub(r"γΊ", "λ¦¬μκΈ°μ­", text)
    text = re.sub(r"γ»", "λ¦¬μλ―Έμ", text)
    text = re.sub(r"γΌ", "λ¦¬μλΉμ", text)
    text = re.sub(r"γ½", "λ¦¬μμμ·", text)
    text = re.sub(r"γΎ", "λ¦¬μν°μ", text)
    text = re.sub(r"γΏ", "λ¦¬μνΌμ", text)
    text = re.sub(r"γ", "λ¦¬μνμ", text)
    text = re.sub(r"γ", "λΉμμμ·", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μΌ", text)
    text = re.sub(r"γ", "μ΄", text)
    text = re.sub(r"γ", "μ¬", text)
    text = re.sub(r"γ", "μ€", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μ°", text)
    text = re.sub(r"γ ", "μ ", text)
    text = re.sub(r"γ‘", "μΌ", text)
    text = re.sub(r"γ£", "μ΄", text)
    text = re.sub(r"γ", "μ ", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μΈ", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ", "μ¨", text)
    text = re.sub(r"γ", "μ", text)
    text = re.sub(r"γ’", "μ", text)

    return text


def normalize_multiline_text(long_text):
    texts = split_text(long_text)
    # print(texts)
    normalized_texts = [normalize_text(text).strip() for text in texts]
    # print(normalized_texts)
    return [text for text in normalized_texts if len(text) > 0]

# 3. νμ΅ν λͺ¨λΈ λΆλ¬μ€κΈ°
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

print("π only Synthesizer end : ",time.time()-syn_start) # μ¬κΈ°κΉμ§ 0.5μ΄
# symbols_start = time.time();
symbols = synthesizer.tts_config.characters.characters
# print(symbols)
# print("π symbol end : ",time.time()-symbols_start)

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
        print("πinitalize Time: ",time.time()-makeTTSTime)

        texts = "μνλ¬Έμ₯ μλλ€"
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
#       print("πoutput Time : ",time.time()-makeTTSTime) # 0.28 sec

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
        # print("Inference : ",time.time()-inference_start); # 0.2μ΄
        print("π total time : ",time.time()-makeTTSTime);
#        texts += "123";
        return texts

'''
# 4. μμ± ν©μ±
texts = """
μ΄μ  λ³Έκ²©μ μΌλ‘ μμν΄ λ³ΌκΉμ? μ²«λ²μ§Έ λ¬Έμ  λ³΄μ¬μ£ΌμΈμ! λ¬Έμ  λκ°λλ€.  μ λ΅μ μ²μ¬μμ΅λλ€! 1λ± κ·Έ μκ΄μ μ£ΌμΈκ³΅μ λ°λ‘ νκΈΈλλ! μΆνλλ¦½λλ€!  μ¬λ¬λΆλ€μ μ νμ΄ κΆκΈνλ°μ μ΄λ€κ±Έ λ§μ΄ μ ννμμμ§ κ·Έ κ²°κ³Όλ₯Ό κ³΅κ°ν©λλ€.
"""
# import librosa    // Synthesizerμ ν¬ν¨λμ΄ μ κ±°
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
print("Inference : ",time.time()-inference_start); # 0.2μ΄
print("π total time : ",time.time()-start);
'''

'''
import torch = 0.6
import g2pk = 0.1
synthesizer(glowtts + hifigan) = 0.6
inference = 0.2
0.3 ??

'''
