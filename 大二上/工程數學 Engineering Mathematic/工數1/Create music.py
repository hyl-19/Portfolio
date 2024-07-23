import numpy as np
import wave 
import struct

file = "11027222.wav"

amplitude = 30000
frequency = 100
duration = 1
fs = 44100
num_samples = (int)(duration * fs)

num_channels = 1
sampwidth = 2
num_frames = num_samples
comptype = "NONE"
compname = "not compressed"

t = np.linspace(0, duration, num_samples, endpoint = False)
t2 = np.linspace(0, 1, num_samples, endpoint = False)
x = amplitude * np.cos(2 * np.pi * frequency * t)

wav_file = wave.open(file, 'w')
wav_file.setparams((num_channels, sampwidth, fs, num_frames, comptype, compname))

x = amplitude * np.cos(2 * np.pi * 440.0 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 493.9 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 523.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 493.9 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 622.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 349.2 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 439.9 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 659.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 493.9 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 440 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 554.4 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 587.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 659.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 523.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))

x = amplitude * np.cos(2 * np.pi * 440 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 493.9 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 554.4 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 587.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 466.2 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 493.9 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 440.0 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 523.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 440 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 392.0 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 587.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 698.5 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 523.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 440 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 587.3 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 440 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 392 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 493.9 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
x = amplitude * np.cos(2 * np.pi * 329.6 * t)
for s in x:
    wav_file.writeframes(struct.pack('h', int(s)))
wav_file.close()