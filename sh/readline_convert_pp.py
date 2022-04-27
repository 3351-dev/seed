# import re

f = open('scenario_pp.txt','r')
f2 = open('scenario_pp_end.txt','w')

line = f.readline()
while line:
	# line = line.strip('N')
	# strip은 작동하지않는 현상

	# line = re.sub(r'\([^)]*\)', '',line)
	# line = re.sub(r'\<[^>]*\)', '',line)
	# line = line.strip('\n')
	line = line.replace('\n','')
	line = line.replace('N','')
	line = line.replace('T','')
	
	cnt = len(line)
	if(cnt>2):
		# f2.write("%s\t %d"%(line, cnt))
		f2.write("%s"%line)
		f2.write('\n')
	line = f.readline()
f.close()