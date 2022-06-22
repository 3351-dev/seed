# scenario_converter.py

import re

with open('0622_scenario','r',encoding='utf-8') as f:
	lines = f.readlines()

with open('0622_scenario_2','w',encoding='utf-8') as ff:
	for line in lines:
		line = line.replace('(1만원권)','')
		line = re.sub(r'\([^)]*\)', '',line)	# () 제거
		
		convertChar = str.maketrans('<>‘’“”','\'\'\'\'\'\'')
		line = line.translate(convertChar)
		
		line = line.replace('\n',' ')

		line = line.replace('강성규    ','')
		line = line.replace('황광희    ','')
		line = line.replace('전효성    ','')
		line = line.replace('시죠','시죠.')
		line = line.replace('니다','니다.')
		line = line.replace('KAIST','카이스트')
		line = line.replace('QAIST','카이스트')

		line = line.strip()
		
		line = line.replace('.','.\n')
		line = line.replace('!','!\n')
		line = line.replace('?','?\n')

		ff.write(line)

with open('0622_scenario_2','r',encoding='utf-8') as f:
	with open('0622_scenario_3.csv','w',encoding='utf-8') as ff:
		lines = f.readlines()
		for line in lines:
			line = line.strip('-) ')
			if len(line) < 15:
				line = ''

			cnt=len(line)-1
			if cnt > 0:
				line = line.replace('\n','\t')
				line += str(cnt)+'\n'
				ff.write(line)

