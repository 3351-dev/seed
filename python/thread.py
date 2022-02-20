# 1
import threading

class CounterThread(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self, name='Timer Thread')

	def run(self):
		global totalCount

		for _ in range(2500000):
			totalCount += 1
		print('2,500,000 End')

if __name__=='__main__':
	global totalCount
	totalCount = 0

	for _ in range(4):
		timerThread = CounterThread()
		timerThread.start()

	print('Waiting thread End')
	mainThread = threading.currentThread()
	for thread in threading.enumerate():
		if thread is not mainThread:
			thread.join()
	print('totalCount = ' + str(totalCount))


# 결과는 10,000,000 이 아닌 현저히 낮은 수치가 나오게된다.
# 왜냐하면 같은 변수를 동시에 접근했기때문.

# 해결방안 : lock, release로 동기화를 한다.


