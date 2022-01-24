From ubuntu
ARG DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y git pip wget libsndfile1
#RUN pip install mecab-ko  python-mecab-ko
RUN pip install IPython
WORKDIR /content
RUN git clone --depth 1 https://github.com/sce-tts/TTS.git -b sce-tts
RUN git clone --depth 1 https://github.com/sce-tts/g2pK.git
WORKDIR /content/TTS
RUN pip install -q --no-cache-dir -e .
RUN python3 setup.py develop
WORKDIR /content/g2pK
RUN pip install konlpy jamo nltk python-mecab-ko
RUN pip install -q --no-cache-dir -e .
