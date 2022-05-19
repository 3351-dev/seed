import os

for i in range(5):
	file_path='/home/kseek/aimc/filelistSET/balloon/wavs%d'%i
	file_names = os.listdir(file_path)
	# print(file_names)

	for name in file_names:
		src = os.path.join(file_path, name)
		dst = 'balloon_%d_'%i
		dst = dst + name
		dst = os.path.join(file_path, dst)
		# i+=1
		# print(dst)
		# print(src)

		os.rename(src, dst)