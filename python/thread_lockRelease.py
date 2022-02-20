import threading

class ThereadVariable():
	def __init__(self):
		self.lock = threading.Lock()
		self.lockedValue = 0

	def plus(self, value):
		self.lock.acquire()
		try:
			self.lockedValue += value
		finally:
			self.lock.release()

class CountThread(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self, name='Timer Thread')
	def run(self):
		global totalCount

		for _ in range(2500000):
			totalCount.plus(1)
		print('2,500,000 End')

if __name__ == '__main__':
	global totalCount
	totalCount = ThereadVariable()

	for _ in range(4):
		timerThread = CountThread()
		timerThread.start()

	print('모든 Thread들이 종료될 때까지 기다린다.')
	mainThread = threading.currentThread()

	for thread in threading.enumerate():
		if thread is not mainThread:
			thread.join()
	print('totalCount = '+str(totalCount.lockedValue))

	## 이 방벅을 적용할경우 순차적으로 접근하게되어 느려진다