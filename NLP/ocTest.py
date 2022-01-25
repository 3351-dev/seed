f = open('new.text','w')
for i in range(1,11):
	data = "%d's Line\n"%i
	f.write(data)
f.close();