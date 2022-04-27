f = open('scenario_pp_end.txt', 'r')
f2 = open('english_corpus.csv','w')

line = f.readline()
while line:
	line = line.strip('- ')
	# line = line.replace("\t", "@")
	cnt = len(line) -1
	if(cnt != 0):
		linez = line.strip()
		f2.write("%s\t %d"%(linez, cnt))
		# f2.write("%s\t"%(linez))
		f2.write("\n")
	line= f.readline()
	# print('count : ',cnt)
f.close()
