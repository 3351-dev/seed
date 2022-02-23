
MODEL_PATH="/STT/ModelWAV/"
AUDIO_PATH="/STT/soundData/KsponSpeech_01/KsponSpeech_0001/KsponSpeech_000"

audio="
515.pcm
"

model="0222_model_epoch_"
version="2.5.pt
3.pt
4.5.pt"

for a in $audio
	do
	echo " "
	FINAL_AUDIO_PATH="$AUDIO_PATH$a"
	echo $FINAL_AUDIO_PATH
	for i in $version
		do
		FINAL_MODEL_PATH="$MODEL_PATH$model$i"
		echo $FINAL_MODEL_PATH
		python3 ./bin/inference.py \
		--model_path $FINAL_MODEL_PATH \
		--audio_path $FINAL_AUDIO_PATH
		done
	done

:<<'END'

515 변화가 확실함
517 나쁘지않음
005 변화 나쁘지 않음
363 나쁘지않음


156 차이 x
158 차이 x
518 X



END