# Mission Application v1.0
### Clone (CRITICAL)
* For SSH, use
`git clone --recurse-submodules ssh://git@bigmac.northgrum.com:8010/darpa/gaps.mission.application.git`

* For HTTPS, use `git clone --recurse-submodules https://bigmac.northgrum.com/bitbucket/scm/darpa/gaps.mission.application.git`

### Documentation
* View Documentiton:
```
Open docs/html/index.html in a web browser 
```
* (Re-)Generate Documentiton:

```
$DOXY_INSTALL_PATH/doxygen $PATH_TO_DOXYFILE
```

## Windows (VS 2017)

### Build

#### Build apr
1. Open *gaps.ma.dependencies/apr-1.5.2/apr.sln* in Visual Studio 2017.

2. In Project Hierarchy, right click on *apr* project, hover on *Project Only*, and click on *Build only apr*

#### Build libapr
1. Open *gaps.ma.dependencies/apr-1.5.2/libapr.sln* in Visual Studio 2017.

2. In Project Hierarchy, right click on *libapr* project, hover on *Project Only*, and click on *Build only libapr*

#### Build ActiveMQ

1. Open *gaps.ma.dependencies/activemq-cpp-library-3.9.5/vs2017-build/activemq-cpp.sln* in Visual Studio 2017.

2. In Project Hierarchy, right click on *activemq-cpp* project hover on *Project Only*, and click on *Build only activemq-cpp*


#### Build cppunit

1. Open *gaps.ma.dependencies/cppunit-1.15.1/src/CppUnitLibraries2010.sln in Visual Studio 2017.
2. In Project Hierarchy, right click on *cppunit* project hover on *Project Only*, and click on *Build only cppunit*
3. In Project Hierarchy, right click on *cppunit_dll* project hover on *Project Only*, and click on *Build only cppunit_dll*

### Run

#### ActiveMQ Broker

1. Open a CMD terminal.
2. Run ```gaps.ma.dependencies/apache-activemq-5.15.13/bin/activemq start``` from CMD.

#### Configure Systems


1. In MA Solution, right click on **Solution 'build'**, select *properties*, and on the *Action* dropdown for EOIR, RDR, ISRM, MPU, MPX, set to *Start*. 

2. (OPTIONAL) From the same menu mentioned above, you can select to start "TestMA". This will output an XML file named *maTestResults.xml* in TestMA's project directory.

#### Build and Run Mission Application
1. Open *build/build.sln* in Visual Studio 2017.
2. Click "Start" to build and run MPU, MPX, EOIR, RDR, and ISRM.

## Linux

### Requirements
* NOTE: Oracle Java JDK is required to run the UI. Otherwise, OpenJDK 1.8 (8.1) will only work with the C++ mission application.

#### Non-Provided Requirements
1. Java 8
2. Python 3.6+
3. Apache Portable Runtime (libapr-1 on Ubuntu/apr-devel on RHEL/Cetnos)
4. nasm
5. tar
6. unzip
7. gtk2 or gtk3 (libdev/devel)
8. g++ 8+
9. openssl-devel / libopenssl-dev
10. autoreconf


#### Provided Requirements
1. ActiveMQ-CPP (v3.9.5) library
2. ActiveMQ Broker (5.16.0)
3. OpenCV (v4.3.0)
4. FFMPEG

### Install Provided Requirements

* Run `chmod +x scripts/*`

#### ActiveMQ-cpp (v3.9.5)
1. Navigate to the scripts directory
2. Run `./install-activemq-cpp.sh`

#### ActiveMQ Broker (v.5.16.0)
1. Navigate to the scripts directory
2. Run `./install-activemq.sh`

#### OpenCV (4.3.0) & FFMPEG (4.3.1)

1. Navigate to the scripts directory
2. Run `./install-opencv.sh`


### Build Mission Application
1. Ensure g++ is version 8 or higher. Run `g++ --version` to check. If it is not, install and enable the devtoolset-8.
2. Navigate to the scripts directory
3. Run `./install-ma.sh`


### How to Run
1. Navigate to the scripts directory
2. Run `./activemq start`
3. Run `./mission-application start`
4. Terminal output is cluttered. If not needed, it may be closed as all the processes are running in the background.

### How to Stop Running
1. Navigate to the scripts directory
2. Run `./activemq stop`
3. Run `./mission-application stop`
