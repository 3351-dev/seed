# TTS Project

# 0121
+ Ubuntu 재설치
+ gsetting set org.gnome.desktop.interface clock-show-setconds true   


## python-mecab-ko 관련하여...
python-mecab-ko를 설치하기위해 다른것들을 설치하여 무엇때문에 정상설치되었는지 확인 불가   
이하 설치 목록   
* mecab
* mecab-ko
* mecab-ko-dic
* python3-dev
## mecab-ko는 한국어 형태소 분석기

1. glow-TTS
2. HiFi-GAN
3. infer

infer는 완료되었으니 이제 산출물을 wav파일로 저장되도록 설정 해 볼 것.   
glow-tts, HiFi-GAN 학습도 도전해볼것   

wav 파일로 저장하기 위해서 soudfile을 설치해주었다.   
```
pip install soundfile
```
data 폴더내에 음성데이터가 생성됨을 확인할 수 있다!   

## 음성 학습을 위한 Mimic Recording Studio
이 글은 이곳을 참고하여 만들었습니다.   
https://sce-tts.github.io/#/v2/recoding   
mimic recording Studio를 설치하기위해 docker와 docker-compose를 설치해준다   
(Window에선 Docker없이 설치만해주면 된다)   

* nodejs 설치가 의심되어 설치해줌
```
sudo apt install nodejs
nodejs -v
```
+ npm도 없어서 추가로 설치해줌
```
sudo apt install npm
npm -v
```
* react 설치
```
npm install -g create-react-app
create-react-app --version
```
Node버전 이슈가 있어서 Node 버전을 14 혹은 그 이상으로 업그레이드!   
* NVM을 이용한 설치로 진행
```
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.37.2/install.sh
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.37.2/install.sh | bash 
source ~/.bashrc
nvm list-remote
nvm install <Version>
```

헌데, 설치 문제가 아닌 것 같다....   
마이크를 연결하니 space bar를 눌렀을때 잘 넘어감을 확인하였다.   
   
   
현재는 음성데이터가 없으니 SCE-TTS에 미리 학습된 데이터를 받아 glow-tts와 HiFi-GAN을 구현해보려고한다.   

확인 결과 미리 학습된 데이터 또한 없어 tensorflow를 설치해보려고한다.

## Tensorflow 설치
환경 : Ubuntu 20.04 LTS, Nvidia Geforce GTX 750 Ti   
! 그래픽 드라이버를 설치할때 freeze 현상을 방지하기위해 다음과 같이 수정했다.   
```
sudo vi /etc/default/grub
GRUB_CMDLINE_LINUX_DEFAULT = "quiet splash nomodeset"
Software & Upgrade에서 tested 드라이버 설치
```

* 가상환경 활성화
? 이거 왜 하나용?
! 너의 환경을 박.살 나도 살릴 수 있도록
```
가상환경 Setting
python3 -m venv --system-site-packages ./venv

가상환경 On
source ./venv/bin/activate  # sh, bash, or zsh

가상환경 Off
deactivate  # don't exit until you're done using TensorFlow
```

## 기본 분류 : 의류 이미지 분류
https://www.tensorflow.org/tutorials/keras/classification?hl=ko

## ㅇㅅㅇ