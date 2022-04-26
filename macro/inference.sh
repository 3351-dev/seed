MODEL_PATH="/home/kseek/trainingOutput/a4000/"

AUDIO_PATH="/home/kseek/STT/soundData/wavwav/dnFile/loudnormTest/Recording_short"

model="model.pt"
version="
14.5_epoch_augmentation_trdn_600k_
15_end_epoch_augmentation_trdn_600k_
"

for a in `ls Recording_short/*.pcm`
	do
	echo " "
#	FINAL_AUDIO_PATH="$AUDIO_PATH/$a"
	FINAL_AUDIO_PATH="./$a"
	echo $FINAL_AUDIO_PATH
	for i in $version
		do
		FINAL_MODEL_PATH="$MODEL_PATH$i$model"
		echo $FINAL_MODEL_PATH
 	python3 ~/STT/kospeech/bin/inference.py \
		--model_path $FINAL_MODEL_PATH \
		--audio_path $FINAL_AUDIO_PATH
	done
done
