## enumerate()
list_k = ['a','b','가']

for idx, name in enumerate(list_k):
	print(idx, name)
print(' ')
for idx, name in enumerate(list_k, 30):
	print(idx, name)