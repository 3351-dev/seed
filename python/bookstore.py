class Book:
	def setData(self, title, price, author):
		self.title = title
		self.price = price
		self.author = author

	def printData(self):
		print ('Title : ', self.title)
		print ('Price : ', self.price)
		print ('Author : ',self.author)

	def __init__(self):
		print ('create Book obj !!!')