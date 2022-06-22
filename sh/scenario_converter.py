# scenario_converter.py

import re

with open('0622_scenario.txt','r',encoding='utf-8') as f:
	lines = f.readlines()

with open('0622_scenario_2.txt','w',encoding='utf-8') as ff:
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
	with open('korean_corpus.csv','w',encoding='utf-8') as ff:
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

# 산출된 파일의 이름을 korean_corpus.csv 혹은 english_corpus.csv로 변경하여 mimic-recording-studio의 backend폴더에 넣으십시오.
# 0622_scenario 파일을 읽어 0622_scenario_2로 만듭니다. 이를가지고 korea_corpus.csv 파일을 만듭니다.
# 대본 형식은 일관되지 않으므로 상황에 맞게 편집해주세요.
# 제 경우 string으로 만든 후 알맞게 잘라주는 방식을 택했습니다.