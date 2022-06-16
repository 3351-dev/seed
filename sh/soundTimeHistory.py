# soundTimeHistory.py

import librosa
import numpy as np
import scipy.io as sio
import scipy.io.wavfile
import matplotlib.pyplot as plt

import sounddevice as sd

audio_path = "/home/kseek/aimc/filelistSET/filelists0504/wavs/eb791e4ffa65768abfa44d8c07db0d0b.wav"
# y, sr = librosa.load(audio_path)


samplerate, data = scipy.io.wavfile.read(audio_path)
times = np.arange(len(data))/float(samplerate)
# sd.play(data, samplerate)

plt.fill_between(times, data)
plt.xlim(times[0], times[-1])
plt.xlabel('time (s)')
plt.ylabel('amplitude')
plt.show()

print('sampling rate : ',samplerate)
print('time : ',times[-1])

import time
import wave

start_time = time.time()
audio = wave.open(audio_path)
audioFrames = audio.getnframes()
audioFramerate = audio.getframerate()
# duration_s = audio.getnframes() / audio.getframerate()
duration_s = audioFrames / audioFramerate
print('audio Frames : ',audioFrames)
print('audio Framerate : ',audioFramerate)


while 1:
	elapsed_time = time.time() - start_time
	current_location = elapsed_time / float(duration_s)
	if current_location>=1:
		break
	time.sleep(.01)