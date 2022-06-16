import tkinter as tk
import wave
import pyaudio
import threading


class SamplePlayer:

    def __init__(self, master):

        frame = tk.Frame(master=master)
        frame.pack(expand=True, fill="both")


        self.current_lbl = tk.Label(master=frame, text="0/0")
        self.current_lbl.pack()

        self.pause_btn = tk.Button(master=frame, text="Pause", command=self.pause)
        self.pause_btn.pack()

        self.play_btn = tk.Button(master=frame, text="Play", command=self.play)
        self.play_btn.pack()

        self.file = r"/home/kseek/STT/spectrogramCheck/sampleData/0615/2022_6_15_1655274558384.wav"

        self.paused = True
        self.playing = False

        self.audio_length = 0
        self.current_sec = 0
        self.after_id = None

    def start_playing(self):  
        
        p = pyaudio.PyAudio()
        chunk = 1024
        with wave.open(self.file, "rb") as wf:
            
            self.audio_length = wf.getnframes() / float(wf.getframerate())

            stream = p.open(format =
                    p.get_format_from_width(wf.getsampwidth()),
                    channels = wf.getnchannels(),
                    rate = wf.getframerate(),
                    output = True)

            data = wf.readframes(chunk)

            chunk_total = 0
            while data != b"" and self.playing:

                if not self.paused:
                    chunk_total += chunk
                    stream.write(data)
                    data = wf.readframes(chunk)
                    self.current_sec = chunk_total/wf.getframerate()

        self.playing=False
        stream.close()   
        p.terminate()

    def pause(self):
        self.paused = True
        
        if self.after_id:
            self.current_lbl.after_cancel(self.after_id)
            self.after_id = None
    
    def play(self):
        if not self.playing:
            self.playing = True
            threading.Thread(target=self.start_playing, daemon=True).start()
        
        if self.after_id is None:
            self.update_lbl()

        self.paused = False

    def stop(self):
        self.playing = False
        if self.after_id:
            self.current_lbl.after_cancel(self.after_id)
        self.after_id = None

    def update_lbl(self):
        
        self.current_lbl.config(text=f"{self.current_sec}/{self.audio_length}")
        self.after_id = self.current_lbl.after(5, self.update_lbl)


def handle_close():
    player.stop()
    root.destroy()

## SETUP AND RUN
root = tk.Tk()
player = SamplePlayer(root)

root.bind("<space>",SamplePlayer.play)
root.protocol("WM_DELETE_WINDOW", handle_close)
root.mainloop()