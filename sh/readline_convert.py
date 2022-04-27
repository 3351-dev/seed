import re
f = open('scenario.txt', 'r')
f2 = open('scenario_pp.txt','w')

stringArr=list()

line = f.readline()
while line:
	line = line.strip('- ')
	line = line.replace("\t", 'T')
	line = line.replace("\n", 'N')
	line = re.sub(r'\([^)]*\)', '',line)
	line = re.sub(r'\<[^)]*\>', '',line)

	stringArr.append(line)
	line= f.readline()
f.close()

i = 0
# for i in range(len(stringArr)):
while(1):
	if(stringArr[i-1][0:4] == 'TTTT'):
		i=0;
	elif(stringArr[i] == 'NN'):
		break;
	if(stringArr[i+1][0:4] == 'TTTT'):
		stringArr[i] += stringArr[i+1]
		del stringArr[i+1]
		stringArr.append('NN')
	i+=1

i = 0
while(1):
	if(stringArr[i] == 'NN'):
		break
	if(stringArr[i][0:3] == 'TTT'):
		stringArr[i] = stringArr[i][6:]
		stringArr[i].strip('NT')
	i+=1

i=0
# stringArr = stringArr.strip('NT')
while(1):
	if(stringArr[i] == 'NN'):
		break
	stringArr[i] = stringArr[i].strip('NT')
	sentence = "".join(stringArr[i])
	sentence = re.sub(r'\([^)]*\)', '',sentence)
	print(sentence)
	f2.write(sentence)
	f2.write("\n")
	i+=1

f2.close
# sentence2 = stringArr[0]
# print(sentence2)
# sentence2 = sentence2.replace('N',' ')
# sentence2 = sentence2.replace('T','')
# print(sentence2)