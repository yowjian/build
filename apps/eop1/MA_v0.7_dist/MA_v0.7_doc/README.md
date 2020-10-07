# Mission Application Solution


## Windows (VS 2017)

### Clone (CRITICAL)
* For SSH, use
```git clone --recurse-submodules ssh://git@bigmac.northgrum.com:8010/darpa/gaps.mission.application.git```

* For HTTPS, use ```git clone --recurse-submodules https://bigmac.northgrum.com/bitbucket/scm/darpa/gaps.mission.application.git```


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

### Run

#### ActiveMQ Broker

1. Open a CMD terminal.
2. Run ```gaps.ma.dependencies/apache-activemq-5.15.13/bin/activemq start``` from CMD.

#### Build and Run Mission Application

1. Open *build/build.sln* in Visual Studio 2017.
2. Click "Start" to build and run MPU, MPX, EOIR, RDR, and ISRM.

## Linux

* TBD