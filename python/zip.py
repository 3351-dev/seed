num = [1,2,3]
name = ['a','b','가']

for pair in zip(num, name):
	print(pair)
	print(type(pair))

print('')
for num, alpha, kor in zip([1,2,3],['a','b','c'],['ㄱ','ㄴ','ㄷ']):
	print(num, alpha, kor)
	print(type(num))
print('')

key = ['a','b','c']
value = [1,2,3]
dictionary = dict(zip(key,value))
print(dictionary)
print(type(dictionary))
print('')

alpha = ['a','b','c']
num = [1,2,3]

for i,(a,n) in enumerate(zip(alpha,num)):
	print(i,a,n)
print('')
for i,(a,n) in enumerate(zip(alpha,num),5):
	print(i,a,n)