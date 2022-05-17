# Copyright (c) 2020, Soohwan Kim. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#-*- coding: utf-8 -*-

import argparse
import torch
import torch.nn as nn
import numpy as np
import torchaudio
from torch import Tensor


from kospeech.vocabs.ksponspeech import KsponSpeechVocabulary
from kospeech.data.audio.core import load_audio
from kospeech.models import (
    SpeechTransformer,
    Jasper,
    DeepSpeech2,
    ListenAttendSpell,
    Conformer,
)

import time

import shutil, os

def revise(sentence):
    words = sentence[0].split()
    result = []
    for word in words:
        tmp = ''
        for t in word:
            if not tmp:
                tmp += t
            elif tmp[-1] != t:
                tmp += t
        if tmp == '스로':
            tmp = '스스로'
        # 평평은 어떻게 할꺼에요??;; 000943.pcm
        if tmp == '평한':
            tmp = '평평한'
        if tmp == '평해':
            tmp = '평평해'
        # 성인인데 는 어떻게.....
        if tmp == '성인데':
            tmp ='성인인데'
        result.append(tmp)
    return ' '.join(result)



def parse_audio(audio_path: str, del_silence: bool = False, audio_extension: str = 'pcm') -> Tensor:
#def parse_audio(audio_path: str, del_silence: bool = False, audio_extension: str = 'wav') -> Tensor:
    signal = load_audio(audio_path, del_silence, extension=audio_extension)
    feature = torchaudio.compliance.kaldi.fbank(
        waveform=Tensor(signal).unsqueeze(0),
        num_mel_bins=80,
        frame_length=20,
        frame_shift=10,
        window_type='hamming'
    ).transpose(0, 1).numpy()

    feature -= feature.mean()
    feature /= np.std(feature)

    return torch.FloatTensor(feature).transpose(0, 1)

import json
import requests
from starlette.responses import FileResponse
from fastapi import FastAPI, Form, File, UploadFile
from pydantic import BaseModel 
from fastapi.middleware.cors import CORSMiddleware
import aiofiles
import uvicorn
import tempfile
import time

app = FastAPI()
app.router.redirect_slashes = False

origins=["*"]

origins=[
    "http://127.0.0.1",
    "http://localhost"
]
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


#class fd_name(BaseModel):
    # text: str
#    pass

# class fd_name(BaseModel):
#     name: str
    # text2: str



@app.post("/STT")
async def STT(fd_name: str=Form(...), fd_audio: UploadFile = File(...)):
    start = time.time()
    dirname = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__))))
    audioFilePath = dirname+"/audio/"+fd_audio.filename
#    print(fd_audio.filename)

    with open(audioFilePath, "wb+") as file_object:
        file_object.write(fd_audio.file.read())

    audioFile = audioFilePath
    audioFileName = "./audio/"+fd_audio.filename[:-4]

    ### 🤐Model
    model_path = '/home/aiserver/ai/STT/600k_augmentation_trdn_epoch_50_end/model.pt'
 
    ### 🤐AudioFile
    cmd = "ffmpeg -y -i "+audioFile+" -f s16le -acodec pcm_s16le -ar 16k -ac 1 "+audioFileName+".pcm 2>> "+audioFileName+".log"
    os.system(cmd) # wav -> pcm, Transform Format
    cmd = "ffmpeg -y -f s16le -ar 16k -ac 1 -i "+audioFileName+".pcm "+audioFileName+"_fromPCM.wav 2>> "+audioFileName+".log" ;
    os.system(cmd) # pcm -> wav

#    cmd = "ffmpeg -y -i "+audioFileName+"_fromPCM.wav -af loudnorm=I=-5:TP=-2:LRA=11:measured_I=-20.26:measured_TP=-9.22:measured_LRA=14.1:measured_TP=-9.22:measured_thresh=-31.20:offset=1.28:linear=true:print_format=json -ar 16k "+audioFileName+"_fromPCM_loud-5.wav 2>> "+audioFileName+".log"
#   os.system(cmd) # wav -> wav, loudnorm
#   audio_path = audioFileName+"_fromPCM_loud-5.wav"
    audio_path = audioFileName+"_fromPCM.wav"

    ### 🤐Device
    device = 'cpu'

    feature = parse_audio(audio_path, del_silence=True)
    input_length = torch.LongTensor([len(feature)])

    vocab = KsponSpeechVocabulary('/home/aiserver/ai/STT/600k_augmentation_trdn_epoch_50_end/aihub_character_vocabs.csv')

    model = torch.load(model_path, map_location=lambda storage, loc: storage).to(device)
    if isinstance(model, nn.DataParallel):
        model = model.module
    model.eval()

    if isinstance(model, ListenAttendSpell):
        model.encoder.device = device
        model.decoder.device = device

        y_hats = model.recognize(feature.unsqueeze(0), input_length, device)
    elif isinstance(model, DeepSpeech2):
        model.device = device
        # y_hats = model.recognize(feature.unsqueeze(0), input_length, device)
        y_hats = model.recognize(feature.unsqueeze(0), input_length)
    elif isinstance(model, SpeechTransformer) or isinstance(model, Jasper) or isinstance(model, Conformer):
        y_hats = model.recognize(feature.unsqueeze(0), input_length, device)

    sentence = vocab.label_to_string(y_hats.cpu().detach().numpy())

    print(audio_path)
    print(revise(sentence))
    print("time : {:.2f}".format(time.time()-start))

        # print(revise(sentence))
    
    return revise(sentence)
