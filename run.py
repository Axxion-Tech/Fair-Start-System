import serial
import sys
import time
import random
from playsound import playsound


print("Searching for FairStartSystem...")
port=sys.argv[1:] # Read the port entered in the command line. The format will vary between Windows/Mac/Linux
bluetooth=serial.Serial(port, 15200) # Initiate bluetooth connection with 15200 baud rate
print("Connected!")

random_num = random.random() * 3.5
print("This countdown: ", random_num) # Show the current randomized countdown
bluetooth.flushInput() # Pulse check bluetooth

playsound('./wait.mp3') # Play the initial three start tones
time.sleep(random_num) # Wait a short random amount of time

bluetooth.write(bytes("1",'utf-8')) # Send the arduino a command to open the gate
time.sleep(0.1) # Wait a brief moment
playsound('./start.mp3') # Play the start sound
print("START")

time.sleep(10)   # Delay for 10 seconds
print("Resetting...")
bluetooth.write(bytes("0",'utf-8')) # Send the arduino a command to close the gate
print("Done.")