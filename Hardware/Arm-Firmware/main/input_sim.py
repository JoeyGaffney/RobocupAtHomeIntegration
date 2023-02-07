###############################################
# input a joint end position and a trajectory #
#   will be generated using 1 degree steps    #
###############################################

import numpy as np
import pandas as pd 
import serial as ps
import time
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
# j1 = int(input("enter joint angle 1: "))
# j2 = int(input("enter joint angle 2: "))
# j3 = int(input("enter joint angle 3: "))
# j4 = int(input("enter joint angle 4: "))
# j5 = int(input("enter joint angle 5: "))
# j6 = int(input("enter joint angle 6: "))
# x = np.asarray([j1, j2, j3, j4, j5, j6])
x = np.asarray([-100,80,-70,30,-20,10])
x_0 = np.asarray([0,0,0,0,0,0]) #initial
serial_flag = 1

max_diff = max(abs(x)) # will determine n
trajectory = np.asarray(x_0)
trajectories = [x_0]
for j in range(0, max_diff+1):
  for i in range(0, len(x)):
    if abs(trajectory[i]) < abs(x[i]):
      if trajectory[i] != x[i]:
        if x[i] < 0:
            trajectory[i] -= 1
        if x[i] > 0:
            trajectory[i] += 1
      trajectories = np.vstack([trajectories, trajectory])
print(trajectories)
pd.DataFrame(trajectories).to_csv(dir_path + "/trajectory.csv")
inc_position_index = 0
j = 0
while True:
  # pass 6 characters then wait for response
  while serial_flag == 0:
    print("waiting for arm to finish moving")
    time.sleep(2)
    serial_flag = 1
    inc_position_index += 1
  
  # arduino = ps.Serial(port='COM6', baudrate=9600, timeout=0.1)
  while serial_flag == 1:
    print("sending joint positions")
    # I think this will need to send 6 chars then change their type to int on arduino side.
    time.sleep(1)

    print("sending joint position ", inc_position_index)
    for j in range(0,6):
      # arduino.write(trajectories[i][j])
      print("sending joint position ", inc_position_index, " ", j)
      # def write_read(x):
      #   arduino.write(bytes(x, 'utf-8'))
      #   time.sleep(0.05)
      #   data = arduino.readline()
      #   return data
      # while True:
      #   value =  write_read(trajectories[i])
    serial_flag = 0
    