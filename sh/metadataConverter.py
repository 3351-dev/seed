import os

print(os.getcwd())

with open('metadata5.csv','r',encoding='utf-8') as metadata:
	lines = metadata.readlines()

for line in lines:
	line = line.split('|')
	line[0]='endPointAdd_'+line[0]
	# print(line)
	line = "|".join(line)
	# print(line)
	with open('metadata.csv','a',encoding='utf-8') as f:
		f.write(line)

