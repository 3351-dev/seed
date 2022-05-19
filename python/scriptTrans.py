scriptFile = '/home/kseek/aimc/filelistSET/balloon/metadata.csv'

with open(scriptFile) as f:
	scriptEndpoint = len(f.readlines())

scriptFile2 = '/home/kseek/aimc/filelistSET/balloon/metadata_mix.csv'
openCSV = open(scriptFile2,'w', encoding='utf-8')

for i in range(5):
	openCSV = open(scriptFile2,'a', encoding='utf-8')
	f = open(scriptFile,'r', encoding='utf-8')

	# with open(scriptFile) as f:
	for z in range(scriptEndpoint):
		content = f.readline()
		openCSV.write('balloon_%d_'%i+content)

	openCSV.close()
	f.close()