# Instructions

This file serves as a complete instruction manual on how to set up the Sync application, capture all of the artifacts, and run the demo from end to end on a distributed network. 


# Device Set Up

On each computer, install taky and redis:

```
sudo -H python3 -m pip install taky
sudo apt install redis-server
```

## Provisioning TAK Client
1. Download Android x86 Emulator VM from https://www.osboxes.org/android-x86/. Version 8.1-r6 32-bit. (64-bit should work as well).
2. Extract the downloaded VM (7z x)
3. Run `virtualbox` then create a new VM. Add the extracted disk from Step 2 when configuring.
4. Change Display Settings fo rthe VM to use VBoxVGA, 3D accel should be unchecked.
5. Install TAK App
  - Obtain ATAK-mil-3.9.0.apk from PL internal sources, place on respective computer
  - Start a simple web server in the directory to serve the apk `python3 -m http.server`
  - From the Android VM, browse to jaga:8000 and click the .apk. 
  - Follow prompts to allow permissions in teh process and install the app.


# Start TAKy
```
taky -c ~/gaps/taky/taky-jaga-green.conf
``` 
Starts TAK server listening on port :8087. A config file can be used for more complex configuration (see examples in the repo).
With the config file a redis instance begins on port :6379 which can be dirctly accessed with the command `redis-cli`

# Configuring the TAK Client
1. Open the TAK app (click the up arrow at bottom of home screen to see apps). Note that some buttons in the app are sensitive and you'll have to click in the lower left of the button.
2. Network Setup
  - ... > Settings > Network Preferences > Network Connection Preferences > Manage Networks
  - Add a network, advanced settings, point to jaga and appropriate port/protocol. Default will use TCP
  - Network icon turns from red to green if connected


# Generating HAL Configuration

From ~/gaps/build/hal/test/sync on both computers, run the following

```
cp ~/gaps/build/apps/sync/partitioned/multithreaded/xdconf.ini .
../../confgen/hal_autoconfig.py -d ../../confgen/device_defs/devices_jaga_liono.json -x ./xdconf.ini -p sync -o .
```

# Run Demo
1. On both computers, start a VM instance with TAK application installed and directed to corresponding taky servers.
2. Start 3 tabs on a terminal window, one for HAL, one for taky, and one for the sync app
On liono (orange), run these commands:
```
cd ~/gaps/build/hal/test/sync
../../daemon/hal -l 0 ./sync_orange.cfg

cd ~/gaps/taky
taky -c taky-liono-orange.conf

cd ~/gaps/build/apps/sync/partitioned/multithreaded/orange
LD_LIBRARY_PATH=/home/ijones/gaps/build/hal/api ./sync

```
On jaga (green), run these commands:
```
cd ~/gaps/build/hal/test/sync
../../daemon/hal -l 0 ./sync_green.cfg

cd ~/gaps/taky
taky -c taky-jaga-green.conf

cd ~/gaps/build/apps/sync/partitioned/multithreaded/green
LD_LIBRARY_PATH=/home/ijones/gaps/build/hal/api ./sync

```

# Test daffodil parser 
When testing daffodil parser, run the hal with an additional command `|& tee /tmp/sync_orange.log` to capture the output of the hal
With this, you can look for specific messages sent to xdd1. Save this as a single message.txt.

Then run the following commands to convert the message to binary and then parse the binary as an infoset.
```
cat 224.txt | xxd -r -p > 224.bin
daffodil parse --schema sync_bw.dfdl 224.bin > 224.infoset
``` 
