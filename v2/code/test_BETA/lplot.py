#!/usr/bin/python2
import matplotlib.pyplot as plt
import time
import threading
import random
import socket
import sys
import struct

pltDataGyrX = [0]*50000
pltDataGyrY = [0]*50000
pltDataGyrZ = [0]*50000
pltDataAccX = [0]*50000
pltDataAccY = [0]*50000
pltDataAccZ = [0]*50000

def updatePltData(pltData, value):
    pltData.append(value)
    pltData.reverse()
    pltData.pop()
    pltData.reverse()

def data_listener():
    UDP_BIND="0.0.0.0"
    UDP_PORT=7000

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_BIND, UDP_PORT))

    while True:
        dataIn, addr = sock.recvfrom(165)
        for i in range(0,10):
            data = dataIn[16*i:16*i+16]
            uData = struct.unpack('Ihhhhhh', data)
            updatePltData(pltDataGyrX, uData[1])
            updatePltData(pltDataGyrY, uData[2])
            updatePltData(pltDataGyrZ, uData[3])
            updatePltData(pltDataAccX, uData[4])
            updatePltData(pltDataAccY, uData[5])
            updatePltData(pltDataAccZ, uData[6])

if __name__ == '__main__':
    thread = threading.Thread(target=data_listener)
    thread.daemon = True
    thread.start()
    #
    # initialize figure
    plt.figure(0)
    plt.ion()
    plt.show()
    plt.figure(1)
    plt.ion()
    plt.show()
    while True:
        plt.figure(0)
        plt.pause(0.05)
        plt.clf()
        plt.plot(pltDataGyrX)
        plt.plot(pltDataGyrY)
        plt.plot(pltDataGyrZ)
        plt.draw()
        plt.figure(1)
        plt.clf()
        plt.plot(pltDataAccX)
        plt.plot(pltDataAccY)
        plt.plot(pltDataAccZ)
        plt.draw()
