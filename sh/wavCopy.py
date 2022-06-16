# wavMixer.py
import os
import wave

metadata_path =  "/home/kseek/aimc/filelistSET/filelistMIX_endPointNoiseCut2/metadata_noiseCut_nonGbk.csv"
metadata_path2 =  "/home/kseek/aimc/filelistSET/filelistMIX_endPointNoiseCut2/metadata_noiseCut_nonGbk.csv"
# folder1 = "/home/kseek/aimc/filelistSET/filelists0428/wavs/"
# folder2 = "/home/kseek/aimc/filelistSET/filelists0504/wavs/"
folder2 = "/home/kseek/aimc/filelistSET/filelistMIX_endPointNoiseCut/wavs/"
mvFolder = "/home/kseek/aimc/filelistSET/filelistMIX_endPointNoiseCut2/wavs/"

with open(metadata_path2) as f:
	read_metadata = f.readlines()

# print(read_metadata)

# for i in read_metadata:
# 	fileName = i.split('|')
# 	fileName = fileName[0]
# 	# print(fileName)
# 	if os.path.exists(folder2+fileName+'.wav'):
# 		cmd = "cp "+folder2+fileName+'.wav '+ mvFolder+fileName+'_0x02.wav'
# 		os.system(cmd)
# 		# print(cmd)


# for i in read_metadata:
# 	string = i.split('|')
# 	string[0] += '_0x02|'
# 	print(string)
# 	with open(metadata_path2,'a') as f:
# 		f.writelines(string)

def get_duration(audio_path):
	audio = wave.open(audio_path)
	frames = audio.getnframes()
	rate = audio.getframerate()
	duration = frames/float(rate)
	return duration

for i in read_metadata:
	fileName = i.split('|')
	fileName = fileName[0]
	# print(fileName)
	time = get_duration(mvFolder+fileName+'.wav')
	if time <1.5:
		print(round(time,1), ', ',fileName )