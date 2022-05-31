import serial
import sys
import os
from os import startfile
import time
import random
import tkinter as tk
from tkinter import *
from threading import Thread
from playsound import playsound

root= tk.Tk()
root.title("Fair Start System")

bottom = Frame(root)
bottom.pack(side=BOTTOM, fill=BOTH)

canvas1 = tk.Canvas(root, width = 400, height = 200, relief="raised")
canvas1.pack()

label1 = tk.Label(root, text='Fair Start System')
label1.config(font=('helvetica', 14))
canvas1.create_window(200, 25, window=label1)

label2 = tk.Label(root, text='Enter Bluetooth Port:')
label2.config(font=('helvetica', 10))
canvas1.create_window(200, 100, window=label2)

entry1 = tk.Entry (root) 
canvas1.create_window(200, 140, window=entry1)

notification = tk.Label(root)
notification.pack(pady=50)

wait_sound = os.path.dirname(__file__) + '/wait.mp3'
start_sound = os.path.dirname(__file__) + '/start.mp3'

def startRace():
	try:
		button1['state'] = "disable"
		button1['bg'] = "grey"
		port=entry1.get() # Read the port entered in the command line. The format will vary between Windows/Mac/Linux
		notification.config(text = "Searching for FairStartSystem on {}...".format(port))
		bluetooth=serial.Serial(port, 15200) # Initiate bluetooth connection with 15200 baud rate
		notification.config(text = "Connected")

		random_num = random.random() * 3.5
		notification.config(text = "This countdown delay: {} seconds".format(round(random_num, 2))) # Show the current randomized countdown
		bluetooth.flushInput() # Pulse check bluetooth

		bluetooth.write(bytes("2",'utf-8')) # Send the arduino a command to show countdown LEDs
		playsound(wait_sound) # Play the initial three start tones
		time.sleep(random_num) # Wait a short random amount of time (keep 'em guessing)

		bluetooth.write(bytes("1",'utf-8')) # Send the arduino a command to open the gate
		notification.config(text = "RACE START")
		time.sleep(0.2) # Wait a brief moment (to compensate for servo movement)
		playsound(start_sound) # Play the start sound

		time.sleep(10)   # Delay for 10 seconds
		notification.config(text = "Resetting...")
		bluetooth.write(bytes("0",'utf-8')) # Send the arduino a command to close the gate
		notification.config(text = "Done.")
		time.sleep(5)
		button1['bg'] = "green"
		button1['state'] = 'normal'
		return
	except serial.SerialException:
		notification.config(text="")
		if not port:
			tk.messagebox.showerror('Input Error', 'Please enter a port in the input.')
		else:
			tk.messagebox.showerror('Bluetooth Error', 'Could not find device on port {}'.format(port))
		button1['bg'] = "green"
		button1['state'] = 'normal'
	except Exception:
		notification.config(text="")
		tk.messagebox.showerror('Error', Exception)
		button1['bg'] = "green"
		button1['state'] = 'normal'

def startRaceThreaded():
	global t
	t = Thread(target=startRace)
	t.start()

	
def openHelp():
    startfile(os.path.dirname(__file__) + '/help.txt')

def openAbout():
    startfile(os.path.dirname(__file__) + '/about.txt')

help_link = tk.Button(text='Help', command=openHelp, fg='blue', font=('helvetica', 9),  highlightthickness = 0, bd = 0, padx=100, pady=30)
help_link.pack(in_ = bottom, side = LEFT)

about_link = tk.Button(text='About', command=openAbout, fg='blue', font=('helvetica', 9),  highlightthickness = 0, bd = 0, padx=100, pady=30)
about_link.pack(in_ = bottom, side = RIGHT)

button1 = tk.Button(text='Start Race', command=startRaceThreaded, bg='green', fg='white', font=('helvetica', 9, 'bold'))
canvas1.create_window(200, 180, window=button1)

root.mainloop()