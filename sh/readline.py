f = open('test.txt', 'r')
f2 = open('test2.txt','w')

line = f.readline()
while line:
	cnt = len(line) -1
	linez = line.strip()
	f2.write("%s\t %d"%(linez, cnt))
	f2.write("\n")
	line= f.readline()
	print('count : ',cnt)
f.close()
