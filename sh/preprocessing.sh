#DATA_PATH="/home/kseek/aiPrj/soundData"
DATA_PATH="/home/kseek/aiPrj/soundData/trdn"

for folder_1 in $DATA_PATH/K*
do
    echo $folder_1
    for folder_2 in $folder_1/*
    do
        for folder_3 in $folder_2/*.pcm
        do

#            echo $folder_3
            fileName=${folder_3##*/}
            fileName=${fileName%%.pcm}
            fileName=${fileName##*_}
            echo $fileName
            if [ `expr "$fileName"` -le 81595 ]; then
                continue
            else
                ./rnnoise_demo $folder_3 $folder_3+1
                mv $folder_3+1 $folder_3
            fi

        done
    done
done
