PCM_PATH="/home/kseek/STT/soundData/KsponSpeech_01"
PCM_PATH2="/STT/soundData/KsponSpeech_01/KsponSpeech_0001"
k=000001
op=1


for i in $PCM_PATH/*
do
	# echo "$i"
	for j in $i/*.pcm
	do
		# echo $j
		format=`printf "%.6d" $k`
		ffmpeg -f s16le -ar 16k -ac 1 -i $j ./wav/$format.wav
		echo $format
		k=$(($k+$op))
	done
done