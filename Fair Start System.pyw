import serial
import sys
import os
from os import startfile
import time
import random
import tkinter as tk
from tkinter import *
from tkinter import messagebox
from threading import Thread
from playsound import playsound

root= tk.Tk()
root.title("Fair Start System")
root.iconbitmap(os.path.dirname(__file__) + '/assets/images/short_logo.ico')

top = Frame(root)
top.pack(side=TOP, fill=BOTH, expand=True)

bottom = Frame(root)
bottom.pack(side=BOTTOM, fill=BOTH, expand=True)

header = tk.Canvas(root, width = 600, height = 80, relief="raised", background="#C80000")
header.pack(in_=top)

body = tk.Canvas(root, width = 400, height = 200, relief="raised")
body.pack()

main_logo = PhotoImage(file = os.path.dirname(__file__) + '/assets/images/full_logo_small.png')
header.create_image(300, 40, image = main_logo)

input_label = tk.Label(root, text='Enter Bluetooth Port:')
input_label.config(font=('helvetica', 14))
body.create_window(200, 100, window=input_label)

input = tk.Entry(root, width=30, justify=CENTER) 
body.create_window(200, 145, window=input)

notification = tk.Label(root)
notification.pack(pady=50)

wait_sound = os.path.dirname(__file__) + '/assets/sound/wait.mp3'
start_sound = os.path.dirname(__file__) + '/assets/sound/start.mp3'

def startRace():
	try:
		button1['state'] = "disable" # Disable start button
		button1['bg'] = "grey"
		port=input.get() # Read the port entered in the command line. The format will vary between Windows/Mac/Linux
		notification.config(text = "Searching for Fair Start System on {}...".format(port))
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
		button1['bg'] = "green" # Restore start button
		button1['state'] = 'normal'
		return
	except serial.SerialException:
		notification.config(text="")
		if not port:
			messagebox.showerror('Input Error', 'Please enter a port in the input.')
		else:
			messagebox.showerror('Bluetooth Error', 'Could not find device on port {}'.format(port))
		button1['bg'] = "green"
		button1['state'] = 'normal'
	except Exception as ex:
		ex_value = sys.exc_info()
		notification.config(text="")
		messagebox.showerror('Error', ex_value)
		button1['bg'] = "green"
		button1['state'] = 'normal'

def startRaceThreaded(): # Real-time notification updates requires threading
	global t
	t = Thread(target=startRace)
	t.start()

def openHelp(): # Show help page
    startfile(os.path.dirname(__file__) + '/webpages/help.html')

def openAbout(): # Show about page
    startfile(os.path.dirname(__file__) + '/webpages/about.html')

help_link = tk.Button(text='Help', command=openHelp, fg='blue', font=('helvetica', 9),  highlightthickness = 0, bd = 0, padx=100, pady=30)
help_link.pack(in_ = bottom, side = LEFT)

about_link = tk.Button(text='About', command=openAbout, fg='blue', font=('helvetica', 9),  highlightthickness = 0, bd = 0, padx=100, pady=30)
about_link.pack(in_ = bottom, side = RIGHT)

button1 = tk.Button(text='Start Race', command=startRaceThreaded, bg='green', fg='white', font=('helvetica', 12, 'bold'), padx=10, pady=5)
body.create_window(200, 200, window=button1)

root.mainloop()