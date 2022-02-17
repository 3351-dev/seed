import os
path = os.getcwd()
dir_list = os.listdir(path)
print("Files and directories in [", path ,"]")

for item in dir_list:
	print(item)