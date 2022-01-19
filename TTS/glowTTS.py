# google colab
# SCE-TTS : Glow-TTS 학습
# python

# 1. 할당된 GPU 확인
import os
GPU_NAME = os.popen('nvidia-smi --query-gpu=name --format=csv,noheader').read().strip()
os.environ['GPU_NAME'] = GPU_NAME
print(f'GPU: {GPU_NAME}')

# 2. 구글 드라이브 마운트
from google.colab import drive
drive.mount('/content/drive')

# 3. 필수 라이브러리 및 함수 불러오기
import sys
from pathlib import Path
%cd /content
!git clone --depth 1 https://github.com/sce-tts/TTS.git -b sce-tts
%cd /content/TTS
!python setup.py develop
!pip install -q --no-cache-dir -e .

# 4. 학습할 데이터셋 불러오기
%cd /content/TTS
!cp "/content/drive/My Drive/Colab Notebooks/data/filelists.zip" ./filelists.zip
#!rm -rf ./filelists
!unzip -q filelists.zip -d ./filelists

# 5. 사전 학습 데이터 불러오기
%cd /content/TTS
!mkdir -p "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2"
if not Path("/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/config.json").exists():
    !gdown --id 1DMKLdfZ_gzc_z0qDod6_G8fEXj0zCHvC -O glowtts-v2.zip
    !unzip -q glowtts-v2.zip -d ./
    !cp -R ./glowtts-v2/* "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/"

%cd /content/TTS
if not Path("/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/scale_stats_new.npy").exists():
    !python TTS/bin/compute_statistics.py "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/config.json" "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/scale_stats_new.npy" --data_path "/content/TTS/filelists/wavs/"

with open("/content/TTS/test_sentences.txt", mode="w") as f:
    f.write("""아래 문장들은 모델 학습을 위해 사용하지 않은 문장들입니다.
서울특별시 특허허가과 허가과장 허과장.
경찰청 철창살은 외철창살이고 검찰청 철창살은 쌍철창살이다.
지향을 지양으로 오기하는 일을 지양하는 언어 습관을 지향해야 한다.
그러니까 외계인이 우리 생각을 읽고 우리 생각을 우리가 다시 생각토록 해서 그 생각이 마치 우리가 생각한 것인 것처럼 속였다는 거냐?""")

# 6.TensorBoard 실행
%load_ext tensorboard
%tensorboard --logdir="/content/drive/My Drive/Colab Notebooks/data/glowtts-v2"    

# 7. 학습 진행
'''
아래 셀에서 2 ~ 3번째 줄의 코드를 주석을 해제합니다.
3번째 줄의 경로를 이어서 학습을 진행할 모델의 경로로 변경합니다.
(예시: /content/drive/My Drive/Colab Notebooks/data/glowtts-v2/glowtts-v2-May-31-2021_08+17AM-d897f2e)
4번째 줄 아래의 코드를 제거합니다.
'''
%cd /content/TTS
# !(python TTS/bin/train_glow_tts.py \
#     --continue_path "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/CONTINUE_DIRECTORY")
!(python TTS/bin/train_glow_tts.py \
    --config_path "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/config.json" \
    --coqpit.datasets.0.path "/content/TTS/filelists"  \
    --coqpit.audio.stats_path "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/scale_stats_new.npy"  \
    --coqpit.test_sentences_file "/content/TTS/test_sentences.txt"  \
    --coqpit.output_path "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/"  \
    --coqpit.num_loader_workers 2  \
    --coqpit.num_val_loader_workers 2  \
    --restore_path "/content/drive/My Drive/Colab Notebooks/data/glowtts-v2/model_file.pth.tar")

