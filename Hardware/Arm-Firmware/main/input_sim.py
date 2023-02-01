###############################################
# input a joint end position and a trajectory #
#   will be generated using 1 degree steps    #
###############################################

import numpy as np
import pandas as pd 
x = np.asarray(input("enter end position as a set of 6 joint angles as an array"))
# x = np.asarray([90, -30, 40, -170, 110, -15])
x_0 = np.asarray([0,0,0,0,0,0]) #initial
max_diff = max(abs(x)) # will determine n
trajectory = np.asarray(x_0)
trajectories = [x_0]
for j in range(0, max_diff):
  for i in range(0, len(x)):
    if abs(trajectory[i]) < abs(x[i]):
      if trajectory[i] != x[i]:
        if x[i] < 0:
            trajectory[i] -= 1
        if x[i] > 0:
            trajectory[i] += 1
      trajectories = np.vstack([trajectories, trajectory])
###############################################
# input a joint end position and a trajectory #
#   will be generated using 1 degree steps    #
###############################################

import numpy as np
import pandas as pd
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))
# x = np.asarray(input("enter end position as a set of 6 joint angles as an array"))
x = np.asarray([90, -30, 40, -170, 110, -15])
x_0 = np.asarray([0,0,0,0,0,0]) #initial
max_diff = max(abs(x)) # will determine n
trajectory = np.asarray(x_0)
trajectories = [x_0]
for j in range(0, max_diff):
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