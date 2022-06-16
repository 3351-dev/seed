# wavMixer.py

import os

metadata_path =  "/home/kseek/aimc/filelistSET/metadata_noiseCut_nonGbk.csv"
folder1 = "/home/kseek/aimc/filelistSET/filelists0428/wavs/"
folder2 = "/home/kseek/aimc/filelistSET/filelists0504/wavs/"
mvFolder = "/home/kseek/aimc/filelistSET/wavs"

with open(metadata_path) as f:
	read_metadata = f.readlines()

# print(read_metadata)

for i in read_metadata:
	fileName = i.split('|')
	fileName = fileName[0]
	# print(fileName[0])
	if os.path.exists(folder1+fileName+'.wav'):
		cmd = "cp "+folder1+fileName+'.wav '+ mvFolder
		os.system(cmd)
		# print(cmd)
	elif os.path.exists(folder2+fileName+'.wav'):
		cmd = "cp "+folder2+fileName+'.wav '+ mvFolder
		os.system(cmd)


