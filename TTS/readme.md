# TTS

## 0121
+ Ubuntu 재설치
+ gsetting set org.gnome.desktop.interface clock-show-setconds true   


### python-mecab-ko 관련하여...
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