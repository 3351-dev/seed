# 0126

* docker build -t 3351dev/jupyter ./
* docker run -it --user kseek -v (`^`)/seedBox/NLP/jupyter /home/kseek/jupyter
* ./NLP/Docerfile은 sudo를 사용할 수 있게 만든 Dockerfile이다.

* 중지된 모든 컨테이너를 일괄 삭제
```
docker container prune
```

* 참고할만한 블로그
https://blog.naver.com/PostView.naver?blogId=shino1025&logNo=222463015437&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView&userTopListOpen=true&userTopListCount=30&userTopListManageOpen=false&userTopListCurrentPage=1

* 안드로이드 TTS, STT 예제
https://imleaf.tistory.com/13

* zip
```
zip -r test.zip ./*
```

* Add the package repositories
distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list

sudo apt-get update && sudo apt-get install -y nvidia-container-toolkit
sudo systemctl restart docker

```
torch.cuda.empty_cache()
```


# hello

CUDA out of memory. Tried to allocate 20.00 MiB (GPU 0; 1.95 GiB total capacity; 896.05 MiB already allocated; 17.62 MiB free; 956.00 MiB reserved in total by PyTorch) If reserved memory is >> allocated memory try setting max_split_size_mb to avoid fragmentation.  See documentation for Memory Management and PYTORCH_CUDA_ALLOC_CONF


???-

# 0127

> EPOCH: 392/10000

 > TRAINING (2022-01-26 12:44:06) 

   --> TRAIN PERFORMACE -- EPOCH TIME: 8.43 sec -- GLOBAL_STEP: 29144
     | > avg_loss: -0.59861
     | > avg_log_mle: -0.67887
     | > avg_loss_dur: 0.08026
     | > avg_align_error: 0.16646
     | > avg_loader_time: 0.01004
     | > avg_step_time: 1.00098

 > EVALUATION 

 | > Synthesizing test sentences
  --> EVAL PERFORMANCE
     | > avg_loss: 0.05932 (-0.00094)
     | > avg_log_mle: -0.13773 (-0.00232)
     | > avg_loss_dur: 0.19705 (+0.00139)
     | > avg_align_error: 0.18421 (+0.00000)


 > EPOCH: 393/10000

checkpoint_29000.pth.tar


* 코랩 연결 방지
```
function ClickConnect(){
    console.log("코랩 연결 끊김 방지"); 
    document.querySelector("colab-toolbar-button#connect").click() 
}
setInterval(ClickConnect, 60 * 1000)
```

* 훈련결과
약 3시간 30분 작동함...   
ColabNoteboos > data > glowtts-v2 > glowtts-v2-January-26 ... > test_audios >    
파일 번호가 커질수록 내 목소리가 학습됨을 확인 할 수 있었다.   


* docker -v 
```
docker run -it --user kseek -v (`^`)/seedBox/NLP/jupyter:/home/kseek/
: 로 구분해준다
```


python3 ./openspeech_cli/hydra_train.py dataset=ksponspeech dataset.dataset_path=$DATASET_PATH dataset.manifest_file_path=$MANIFEST_FILE_PATH dataset.test_dataset_path=$TEST_DATASET_PATH dataset.test_manifest_dir=$TEST_MANIFEST_DIR tokenizer=kspon_character model=listen_attend_spell audio=melspectrogram lr_scheduler=warmup_reduce_lr_on_plateau trainer=tpu criterion=cross_entropy


# 0127

 > EPOCH: 112/10000

 > TRAINING (2022-01-27 03:08:18) 

   --> STEP: 6/15 -- GLOBAL_STEP: 293375
     | > G_l1_spec_loss: 0.34856  (0.35474)
     | > G_mse_fake_loss: 0.67357  (0.66360)
     | > G_feat_match_loss: 0.11598  (0.11710)
     | > G_loss: 17.51840  (17.79780)
     | > G_gen_loss: 15.68507  (15.96322)
     | > G_adv_loss: 1.83333  (1.83458)
     | > D_mse_gan_loss: 0.22649  (0.21605)
     | > D_mse_gan_real_loss: 0.00078  (0.00149)
     | > D_mse_gan_fake_loss: 0.00071  (0.00108)
     | > D_loss: 0.22649  (0.21605)
     | > step_time: 4.23
     | > loader_time: 0.0038
     | > current_lr_G: 6.488910597268514e-05
     | > current_lr_D: 6.488910597268514e-05

   --> TRAIN PERFORMACE -- EPOCH TIME: 63.65 sec -- GLOBAL_STEP: 293383
     | > avg_G_l1_spec_loss: 0.35386
     | > avg_G_mse_fake_loss: 0.65490
     | > avg_G_feat_match_loss: 0.11597
     | > avg_G_loss: 17.73852
     | > avg_G_gen_loss: 15.92390
     | > avg_G_adv_loss: 1.81462
     | > avg_D_mse_gan_loss: 0.21697
     | > avg_D_mse_gan_real_loss: 0.00172
     | > avg_D_mse_gan_fake_loss: 0.00140
     | > avg_D_loss: 0.21697
     | > avg_loader_time: 0.00321
     | > avg_step_time: 4.23914

 > EVALUATION 

  --> EVAL PERFORMANCE
     | > avg_G_l1_spec_loss: 0.34895 (-0.00109)
     | > avg_G_mse_fake_loss: 0.63061 (+0.02380)
     | > avg_G_feat_match_loss: 0.10436 (+0.00277)
     | > avg_G_loss: 17.37688 (+0.00247)
     | > avg_G_gen_loss: 15.70267 (-0.04902)
     | > avg_G_adv_loss: 1.67421 (+0.05149)
     | > avg_D_mse_gan_loss: 0.26288 (-0.01331)
     | > avg_D_mse_gan_real_loss: 0.00397 (+0.00124)
     | > avg_D_mse_gan_fake_loss: 0.00016 (-0.00016)
     | > avg_D_loss: 0.26288 (-0.01331)
     | > avg_loader_time: 6.04624 (+0.01300)
     | > avg_step_time: 1.20975 (+0.00311)


 > EPOCH: 113/10000

 > TRAINING (2022-01-27 03:09:39) 
 > 
2시간 37분   


학습이 완료되어 glowtts, hifigan에서 각 각 best_model.pth.tar가 나와 연동해서 실행시켜보려한다.   

* requiremnet.txt
```
pip install -r requirement.txt
```

* TTS는 잘 돌아간다!

* 행동인식 블로그
https://blog.naver.com/PostView.naver?blogId=sogangori&logNo=222146039609&parentCategoryNo=&categoryNo=&viewDate=&isShowPopularPosts=false&from=postView


# 0128

* 전처리 방법
```
def rule(x):
    # 괄호
    a = re.compile(r'\([^)]*\)')
    # 문장 부호
    b = re.compile('[^가-힣 ]')
    x = re.sub(pattern=a, repl='', string= x)
    x = re.sub(pattern=b, repl='', string= x)
    return x
```
* Docker -v option
  - https://0902.tistory.com/6

* PCM Play for Linux
  - https://stackoverflow.com/questions/20314739/how-to-play-pcm-sound-file-in-ubuntu
```
ffplay -f s16le -ar 16k -ac 1 -autoexit
ffplay -f f32le -ar 48000 -ac 2 snake.raw
```

# 0203

* Colab으로 돌립니다... 컴퓨터 너무 느려요   
01.28 14:46 Start   
02.03 06:44 Epoch 2 End   
딱 일주일 학습만에 epoch 2 끝.   

Colab 단점, 데이터가 많은 것을 구글 드라이브에 올려야한다.. Local 마운트는 왜 안될까?   


* CycleGAN 개재밌어보임 ㅋㅋ   


* data scientist
https://theorydb.github.io/dev/2020/04/12/dev-competition-how-to-become-data-scientist/

* Deep Learning 
https://tensorflow.blog/page/6/?wref=bif

* 재밌는 프로젝트
https://diy-project.tistory.com/106

* 딥러닝 학습 (TTS)
  + 음성 신호에서 텍스트 전처리를 통해 언어적 특징벡터를 추출한 후 이 값을 입력으로 함
  + 음성 신호의 Vocoder parameter를 출력으로 학습
  + 기존 음성 합성 방식에서는 발성 기관 구조 및 원리의 이해와 문자에서 발음 표기로 변환하는 언어적 지시 및 음성 스펙트럼의 세부적인 특성 등 다양한 음성학, 음운론, 음성 신호처리 관련 지식이 필요 했음
  + 하지만 딥러닝 기술 기반에서는 입력과 출력 데이터만 있으면 됨.
  + 기계가 자동으로 중간 과정을 찾아서 모델링하고 모델값을 저장해 음성을 바로 합성 
  + 요즘은 End to End를 연구중.(수천 명 이상의 목소리를 하나의 TTS 모델에서 합성하는 모델)
* 참고사이트
https://blog.ncsoft.com/%EA%B2%8C%EC%9E%84%EA%B3%BC-ai-5-%EC%9D%8C%EC%84%B1-%ED%95%A9%EC%84%B1-%EA%B8%B0%EC%88%A0/

+ Morphing 기법을 활용한 대화구문기반 영상 콘텐츠 저작도구 시스템 내 3D 캐릭터 립싱크 애니메이션 제작 
https://www.earticle.net/Article/A181923