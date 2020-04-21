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
  ax1 = fig.add_subplot(231)
  ax1.set_ylabel('UAV x')
  ax1.set_xlabel('Seq#')
  ax1.set_xlim(0,1000)
  ax1.set_ylim(0,800)
  ax2 = fig.add_subplot(232)
  ax2.set_ylabel('UAV y')
  ax2.set_xlabel('Seq#')
  ax2.set_xlim(0,1000)
  ax2.set_ylim(0,800)
  ax3 = fig.add_subplot(233)
  ax3.set_ylabel('UAV z')
  ax3.set_xlabel('Seq#')
  ax3.set_xlim(0,1000)
  ax3.set_ylim(0,800)
  ax4 = fig.add_subplot(234)
  ax4.set_ylabel('TGT x')
  ax4.set_xlabel('Seq#')
  ax4.set_xlim(0,1000)
  ax4.set_ylim(0,16000)
  ax5 = fig.add_subplot(235)
  ax5.set_ylabel('TGT y')
  ax5.set_xlabel('Seq#')
  ax5.set_xlim(0,1000)
  ax5.set_ylim(0,16000)
  ax6 = fig.add_subplot(236)
  ax6.set_ylabel('TGT z')
  ax6.set_xlabel('Seq#')
  ax6.set_xlim(0,1000)
  ax6.set_ylim(0,16000)
  fig.subplots_adjust(wspace=1.0,hspace=1.0)

  uavclk = 0
  tgtclk = 0
  for line in sys.stdin:
    plt.pause(0.001)
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
          ax1.plot(uavt,uavx)
          ax2.plot(uavt,uavy)
          ax3.plot(uavt,uavz)
          ax4.plot(tgtt,tgtx)
          ax5.plot(tgtt,tgty)
          ax6.plot(tgtt,tgtz)
          plt.draw()
        elif typ == 2:
          tgtclk += 1
          tgtx.append(x)
          tgty.append(y)
          tgtz.append(z)
          tgtt.append(tgtclk)
          ax1.plot(uavt,uavx)
          ax2.plot(uavt,uavy)
          ax3.plot(uavt,uavz)
          ax4.plot(tgtt,tgtx)
          ax5.plot(tgtt,tgty)
          ax6.plot(tgtt,tgtz)
          plt.draw()
    typ = 0
    sta = 0 

  plt.show(block=True) 

