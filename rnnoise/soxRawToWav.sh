DATA_PATH="/home/kseek/STT/denoise/rnnoise_contributions"
SAVE_PATH="/home/kseek/STT/denoise/rnnoise/audio_file"
num=1
folder=1

for i in $DATA_PATH/*.raw
do
#    echo $i
#    ffmpeg -f s16le -ar 16k -ac 1 $i $num.raw
    sox -r 16k -e signed -b 16 -c 1 $i $SAVE_PATH/temp_$folder/$num.wav

    if [ $num -eq 1024 ];then
        folder=$((folder+1))
    elif [ $num -eq 2048 ];then
        folder=$((folder+1))
    fi

    echo $num

    num=$((num+1))
done

