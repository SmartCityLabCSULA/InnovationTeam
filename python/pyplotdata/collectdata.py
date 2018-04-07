import argparse
import datetime
import signal
import time

import serial
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


description  = 'Utility to save data from serial to a CSV file. Default port: '
description += '/dev/ttyACMO, default baud rate: 115200'
f_arg_help  = 'name for the CSV file. If no file name is passed then the '
f_arg_help += 'default file name has the following format:'
f_arg_help += 'Year-month-day-Hour-Minute-Second.csv'
parser = argparse.ArgumentParser(description=description)
parser.add_argument('-f', '--file', help=f_arg_help, action='store', dest='filename')
parser.add_argument('-p', '--plot', help='plot the data', 
        action='store_true', dest='plot')
parser.add_argument('--saveplot', action='store', dest='saveplot',
        help='saves plotted data, must give filename (used with --plot)')
parser.add_argument('--port', help='serial port (default /dev/ttyACM0)',
        default='/dev/ttyACM0', action='store', dest='port')
parser.add_argument('-b', '--baud', help='baud rate (default 115200)', 
        default=115200, action='store', dest='baud')

args = parser.parse_args()

def signal_handler(signal, frame):
    """Handles the SIGINT event. 
    From:  https://stackoverflow.com/a/32923097/3562890
    """
    global interrupted
    interrupted = True

signal.signal(signal.SIGINT, signal_handler)
interrupted = False

print("Connecting to serial port {}".format(args.port))
ser = serial.Serial(args.port, args.baud)
print("Connected to serial port {} at baud rate {}".format(args.port, args.baud))

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
        distance1 = float(data_split[0])
        distance2 = float(data_split[1])
        voltage3 = float(data_split[2])
        voltage4 = float(data_split[3])
        voltage5 = float(data_split[4])
        # distance1 = float(data_split[0])
        # distance2 = float(data_split[1])
        now = time.time()
        time_elapsed = now - start
        temp_data = [time_elapsed, distance1, distance2, voltage3, voltage4, voltage5]
        data_list.append(temp_data)
        if args.plot:
            plt.show()
            plt.scatter(time_elapsed, distance1, c='red', s=5)
            plt.scatter(time_elapsed, distance2, c='blue', s=5)
            plt.scatter(time_elapsed, voltage3, c='green', s=5)
            plt.scatter(time_elapsed, voltage4, c='yellow', s=5)
            plt.scatter(time_elapsed, voltage5, c='black', s=5)
            plt.pause(pause)
    except:
        print("Couldn't get data")

print('Data collection complete.')
data_frame = pd.DataFrame(data_list)
if args.filename:
    filename = '{}.csv'.format(args.filename)
else:
    ts = time.time()
    timestamp = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d-%H-%M-%S')
    filename = '{}.csv'.format(timestamp)

data_frame.to_csv(filename, index=False)
print('Data written to {}'.format(filename))

if args.saveplot and args.plot:
    plt.savefig(args.saveplot)
