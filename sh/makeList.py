import os

path='./wavs'
os.chdir(path)

fileName = os.listdir()
print(fileName)

# os.chdir('../makeList')

for i,f in enumerate(fileName):
	os.chdir('../makeList')
	with open('list_%d.txt'%i,'w',encoding='utf-8') as L:
		L.write('file /home/kseek/aiDisk/newTTS/under1sec_wavs_rnn_22050_2/wavs/%s\n'%f)
		L.write('file /home/kseek/aiDisk/newTTS/under1sec_wavs_rnn_22050_2/out2.wav\n')


	os.chdir('/home/kseek/aiDisk/newTTS/under1sec_wavs_rnn_22050_2/wavs2')
	cmd = "ffmpeg -f concat -safe 0 -i /home/kseek/aiDisk/newTTS/under1sec_wavs_rnn_22050_2/makeList/list_"+str(i)+".txt -c copy endPointAdd_"+f
	# print(cmd)
	os.system(cmd)

