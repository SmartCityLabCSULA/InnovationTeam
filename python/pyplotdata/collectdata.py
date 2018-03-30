import argparse
import signal
import time

import serial
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


description = 'Utility to save data from serial to a CSV file'
parser = argparse.ArgumentParser(description=description)
parser.add_argument('-f', '--file', help='name for the CSV file')
parser.add_argument('-p', '--plot', help='plot the data', action='store_true')
parser.add_argument('--saveplot', 
        help='saves plotted data, must give filename (used with --plot)')

args = parser.parse_args()

def signal_handler(signal, frame):
    """Handles the SIGINT event. 
    From:  https://stackoverflow.com/a/32923097/3562890
    """
    global interrupted
    interrupted = True

signal.signal(signal.SIGINT, signal_handler)
interrupted = False


print("Connecting to serial port...")
ser = serial.Serial('/dev/ttyACM0', 115200)
print("Connected to serial port")

if args.plot:
    print("matplotlib setup stuff happening")
    plt.ion()
    fig = plt.figure()
    plt.grid(linestyle='--')
    plt.xlabel('Time [sec]')
    plt.ylabel('Voltage [V]')
    print("matplotlib done setting up")
    print("Let's plot")

start = time.time()
pause = 0.0001

data_list = []

print('Collecting data...')
while not interrupted:
    try:
        data = ser.readline()
        data = data.decode("utf-8")
        data_split = data.split(",")
        distance1 = data_split[0]
        distance2 = data_split[1]
        distance1 = float(data_split[0])
        distance2 = float(data_split[1])
        now = time.time()
        time_elapsed = now - start
        temp_data = [time_elapsed, distance1, distance2]
        data_list.append(temp_data)
        if args.plot:
            plt.show()
            plt.scatter(time_elapsed, distance1, c='red')
            plt.scatter(time_elapsed, distance2, c='blue')
            plt.pause(pause)
    except:
        print("Couldn't get data")

print('Data collection complete.')
columns = ['Time', 'Distance 1', 'Distance 2'] 
data_frame = pd.DataFrame(data_list, columns=columns)
if args.file:
    filename = '{}.csv'.format(args.file)
else:
    filename = 'test.csv'

data_frame.to_csv(filename, index=False)
print('Data written to {}'.format(filename))

if args.saveplot and args.plot:
    plt.savefig(args.saveplot)
