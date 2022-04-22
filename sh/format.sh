FILE_PATH="/home/kseek/STT/spectrogramCheck/record/new"
DEMO_PATH="/home/kseek/rnnoise_original/rnnoise/examples"
TRAINING_PATH="/home/kseek/denoisePrj/rnnoise/examples"

for i in $FILE_PATH/*.m4a
do
#    echo $i
    fileName=${i##*/}
    fileName=${fileName%%.m4a}
#   echo $fileName
    ffmpeg -i $fileName.m4a -acodec pcm_s16le -f s16le -ar 16k -ac 1 $fileName.pcm
#    echo .$DEMO_PATH/rnnoise_demo $FILE_PATH/$fileName.pcm $FILE_PATH/${fileName}_dn.pcm
    $DEMO_PATH/rnnoise_demo $FILE_PATH/$fileName.pcm $FILE_PATH/${fileName}_dn.pcm
    $TRAINING_PATH/rnnoise_demo $FILE_PATH/$fileName.pcm $FILE_PATH/${fileName}_trdn.pcm

    ffmpeg -f s16le -ar 16k -ac 1 -i $fileName.pcm $fileName.wav
    ffmpeg -f s16le -ar 16k -ac 1 -i ${fileName}_dn.pcm ${fileName}_dn.wav
    ffmpeg -f s16le -ar 16k -ac 1 -i ${fileName}_trdn.pcm ${fileName}_trdn.wav
done
