# CLOSURE Simple App
The simple app is a small utility to test the connectivity and data transfer via CLOSURE HAL.

A prerequisite of building CLOSURE from its components is git slave. Download and install [git slave](http://gitslave.sourceforge.net/) as follows, if it is not already installed on your system.
```
```

## Contents
- [Building the App](#building-the-app)
- [Running the App](#running-the-app)
- [Sample Output](#sample-output)

## Building the App
Do the following to build the app.

```
make
```
An executable named simple is created if the build is successful.


## Running the App
The usage of the app is as follows.

```
Usage: <this-program> 
	 -h     	 help
	 -v     	 verbose mode
	 -f <flow file>	 Use the flow file (default flows.txt)
	 -e <enc>	 name of my enclave
	 -l <period>	 Interval in seconds to display statistics (default 10s)
```

A flow specification file is needed in order to run the app. By default, the file, flows.txt, which defines the 6-month demo flows and listed below, is used.

```
# enclave <enclave name> <port> <pub-endpoint> <sub-endpoint>
enclave orange 9001 ipc:///tmp/halpubbworange ipc:///tmp/halsubbworange
enclave green 9002 ipc:///tmp/halpubbwgreen ipc:///tmp/halsubbwgreen

# flows <from-enclave> to <to-enclave>
flows orange green

# <transmission rate in Hz> <mux> <sec> <type> [<#packets>]
100 2 2 1 
10 2 2 2 

flows green orange
100 1 1 1 
```

In a flow specification, at least two enclaves should be declared, one on each line started with the keyword 'enclave', followed by the name of the enclave, a UDP port for out-of-band communication, the publication endpoint and finally the subscription endpoint.

Flows from <from-enclave> to <to-enclave> are declared using the 'flows' keyword, followed by the names of the two enclaves. Individual flows in this group are listed after the 'flows' declaration. Each of such flows contains the transmission rate in number of packets per second (Hz), followed by HAL mux, sec and type. Finally, an optional field <#packets> gives the number of GAPS packets are to be transmitted in this flow. If the number of packets in all flows of the run are specified, the execution of the app will be terminated after all packets have been transmitted.

Once the flows are specified, the app can be started, one instance per enclave, by giving the enclave name is the spec. For example, two enclaves, orange and green, are specified in the default spec in flows.txt. Therefore, they can be started as follows.
```
$ ./simple -e orange
$ ./simple -e green
```

## Sample Output
After started, the app prints the flow specfications and waits for the receivers of the flows to be ready before sending packets originated from this enclave. The following output are from running the default flows. A table of statistics are displayed by the app periodically (default 10 seconds, configurable with the -l command line argument). Each line in the table is a flow where the second column gives its direction, -> for outgoing and <- for incoming.

Output of the green enclave
```
$ ./simple -e green
using default flow definition: flows.txt
IPC: ipc:///tmp/halpubbwgreen ipc:///tmp/halsubbwgreen
flow 1: 100 2 2 1
flow 2: 10 2 2 2
flow 3: 100 1 1 1
enclave: green	 current time: 08:36:44	 elapsed time: 00:00:10
    |  | this period |      accumulated      |      jitter (ms)      |       delay (ms)      |loss (%)|
flow|  | count   rate| count      rate      %|average     max     min|average     max     min|        |
   1|<-|  280   28.00|    280    28.00 100.00|   0.42    2.00    0.00|   1.07    3.00    0.00|    0.00|
   2|<-|   29    2.90|     29     2.90 100.00|   1.10    3.00    0.00|   0.62    3.00    0.00|    0.00|
   3|->|  348   34.80|    348    38.67     NA|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|

enclave: green	 current time: 08:36:54	 elapsed time: 00:00:20
    |  | this period |      accumulated      |      jitter (ms)      |       delay (ms)      |loss (%)|
flow|  | count   rate| count      rate      %|average     max     min|average     max     min|        |
   1|<-|  928   92.80|   1208    60.40 100.00|   0.45    7.00    0.00|   1.24    9.00    0.00|    0.00|
   2|<-|  100   10.00|    129     6.45 100.00|   1.33   13.00    0.00|   0.80   13.00    0.00|    0.00|
   3|->|  934   93.40|   1282    67.47     NA|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|
```

Output of the orange enclave
```
chen@u19:~/build/apps/simple$ ./simple -e orange
using default flow definition: flows.txt
IPC: ipc:///tmp/halpubbworange ipc:///tmp/halsubbworange
flow 1: 100 2 2 1
flow 2: 10 2 2 2
flow 3: 100 1 1 1
enclave: orange	 current time: 08:36:50	 elapsed time: 00:00:10
    |  | this period |      accumulated      |      jitter (ms)      |       delay (ms)      |loss (%)|
flow|  | count   rate| count      rate      %|average     max     min|average     max     min|        |
   1|->|  865   86.50|    865    86.50     NA|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|
   2|->|   92    9.20|     92     9.20     NA|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|
   3|<-|    0    0.00|      0     0.00   0.00|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|

enclave: orange	 current time: 08:37:00	 elapsed time: 00:00:20
    |  | this period |      accumulated      |      jitter (ms)      |       delay (ms)      |loss (%)|
flow|  | count   rate| count      rate      %|average     max     min|average     max     min|        |
   1|->|  932   93.20|   1797    89.85     NA|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|
   2|->|   99    9.90|    191     9.55     NA|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|
   3|<-|    0    0.00|      0     0.00   0.00|   0.00    0.00    0.00|   0.00    0.00    0.00|    0.00|
```