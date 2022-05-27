import os
import wave

def get_duration(audio_path):
	audio = wave.open(audio_path)
	frames = audio.getnframes()
	rate = audio.getframerate()
	duration = frames/float(rate)
	return duration

# print(get_duration("/home/kseek/aimc/filelistSET/filelists/wavs/ffef9ab19081a314d2967997b1bce1df.wav"))
# with open('path_new'+'metadata.csv') as file_data:
path = "/home/kseek/aimc/filelistSET/filelists/wavs/"
path_new = "/home/kseek/aiDisk/newTTS/"

dir_list = os.listdir(path)

with open(path_new+'under3sec.csv','w+') as file:
	for i in dir_list:
		time = get_duration(path+i)
		if time < 3:
			file.write(i+'\n')
		# cmd = "rm /home/kseek/aiDisk/newTTS/wavs/"+i
		# print(cmd)
		# os.system(cmd)

with open(path_new+'metadata.csv','r') as file:
	lines = file.readlines()

with open(path_new+'under3sec.csv','r') as csv_file:
	csv_lines = csv_file.readlines()

csv_linesz=[]
for i in csv_lines:
	csv_linesz.append(i.strip('\n'))

with open(path_new+'metadata2.csv','w+') as file:
	for line in lines:
		line_wav = line.split('|')
		line_wav = line_wav[0]+'.wav'
	# 	# print(line)

		if line_wav not in csv_linesz:
			file.write(line)
	# 		# print("no")

	# print(csv_linesz)

		# if(line_wav not in csv_lines):
		# 	file.write(line_wav+"\n")

		# for csv_line in csv_lines:
		# 	# print(csv_line.strip('\n'))
		# 	if(line_wav != csv_line.strip("\n")):
		# 		file.write(line_wav+"\n")
		# 		break
