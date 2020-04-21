#!/usr/bin/python3
import sys
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt


if __name__ == '__main__':
  print("Reading from stdin, plotting using matplotlib")
  typ = 0 # No tracks yet
  sta = 0 
  uavx = []
  uavy = []
  uavz = []
  uavt = []
  tgtx = []
  tgty = []
  tgtz = []
  tgtt = []
  plt.ion()
  fig = plt.figure()
  ax1 = fig.add_subplot(121,projection='3d')
  ax1.set_xlabel('UAV x')
  ax1.set_ylabel('UAV y')
  ax1.set_zlabel('UAV z')
  ax1.set_xlim3d(0,120)
  ax1.set_ylim3d(0,60)
  ax1.set_zlim3d(0,30)
  ax2 = fig.add_subplot(122,projection='3d')
  ax2.set_xlabel('Target x')
  ax2.set_ylabel('Target y')
  ax2.set_zlabel('Target z')
  ax2.set_xlim3d(1000,1300)
  ax2.set_ylim3d(7800,9500)
  ax2.set_zlim3d(9000,9080)

  uavclk = 0
  tgtclk = 0
  for line in sys.stdin:
    plt.pause(0.05)
    line = line.strip()
    if sta == 0:
      if "UAV TRACK" in line:
        typ = 1 # UAV
        sta = 1 # Want x
        continue
      elif "Target TRACK" in line:
        typ = 2 # Target
        sta = 1 # Want x
        continue
    elif sta == 1:
      if "x=" in line:
        x = float(line.split('=')[1])
        sta = 2 # Want y
        continue
    elif sta == 2:
      if "y=" in line:
        y = float(line.split('=')[1])
        sta = 3 # Want z
        continue
    elif sta == 3:
      if "z=" in line:
        z = float(line.split('=')[1])
        print(typ,x,y,z)
        if typ == 1:
          uavclk += 1
          uavx.append(x)
          uavy.append(y)
          uavz.append(z)
          uavt.append(uavclk)
          ax1.plot3D(uavx,uavy,uavz)
          ax2.plot3D(tgtx,tgty,tgtz)
          plt.draw()
        elif typ == 2:
          tgtclk += 1
          tgtx.append(x)
          tgty.append(y)
          tgtz.append(z)
          tgtt.append(tgtclk)
          ax1.plot3D(uavx,uavy,uavz)
          ax2.plot3D(tgtx,tgty,tgtz)
          plt.draw()
    typ = 0
    sta = 0 

  plt.show(block=True) 

