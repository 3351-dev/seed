PCM_PATH="/home/kseek/STT/kospeech/bin/audio/test"

k=000001
op=1


for i in $PCM_PATH/*/
do
	# echo $i
	for j in $i*.m4a
	do
		echo $j
		# fileName=${j##*/}
		fileName=${j%%.m4a}
		
		echo fileName is $fileName

		ffmpeg -i $fileName.m4a -f s16le -acodec pcm_s16le -ar 16k -ac 1 $fileName.pcm
		ffmpeg -f s16le -ar 16k -ac 1 -i $fileName.pcm $fileName.wav

		echo RNNoise start
		~/denoisePrj/rnnoise/examples/rnnoise_demo $fileName.pcm ${fileName}_trdn.pcm
		echo RNNoise end

		ffmpeg -f s16le -ar 16k -ac 1 -i ${fileName}_trdn.pcm ${fileName}_trdn.wav
		ffmpeg -i ${fileName}_trdn.wav -af loudnorm=I=-5:TP=-2:LRA=11:measured_I=-20.26:measured_TP=-9.22:measured_LRA=14.1:measured_TP=-9.22:measured_thresh=-31.20:offset=1.28:linear=true:print_format=json -ar 16k ${fileName}_trdn_loud-5.wav
	# 	format=`printf "%.6d" $k`
	# 	ffmpeg -f s16le -ar 16k -ac 1 -i $j ./wav/$format.wav
	# 	echo $format
	# 	k=$(($k+$op))
	done
done