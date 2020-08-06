# CLOSURE Example: ERI Demonstration

This directory contains sources for the application used for demonstrating
cross-domain systems development including use of open-source libraries 
using the CLOSURE toolchain. THe application integrates a C-based web
application framework (facil.io), calls the Sqlite3 database API, and also
does face recognition by calling Python from C (invoking opencv, dlib,
face-recognition, scikit-learn, numpy, and other modules).

## Licenses and Acknowledgements
Build top-level license applies to CLOSURE code. Third-party code includes SQLite3 (public domain), facil.io (MIT license), dlib (Boost software license), opencv (BSD 3-clause), and Face Recognition (MIT license). We have adopted ideas from [pyimagesearch](https://www.pyimagesearch.com/2018/06/18/face-recognition-with-opencv-python-and-deep-learning/).

## Directory Structure

* plain:       contains original unannotated application
* annotated:   contains annotations applied to plain to reflect security intent below
* refactored:  contains annotated code refactored for making security-compliant partitioning feasible
* divvied:     contains code divvied up into separate directories for each level/enclave as input for GEDL generation, followed by code autogeneration
* partitioned: contains fully paritioned sources with cross-domain RPCs, marshalling, serialization, tags, HAL API, etc.

## Cross Domain Topology

* Enclaves: 2 (Orange, Purple)

## Security Intent

* The web application must run on the orange side, and obtain input person 
name and photographic image 
* The face recognition functionality must run on the purple side, but feature extraction must run on the orange side
  * the photo cannot be shared, computed features can
  * variable `embeddings` in secdesk.c is on orange side but shared with purple 
  * functions recognize(), start_recognizer(), and stop_recognizer() will need to be wrapped in cross-domain RPC

## Dependencies

* CLE Version:
* Refactoring Methodology:
* HAL API:
* DFDL/DAGR:
### Additional packages needed 

```
sudo apt install sqlite3 libsqlite3-dev
sudo -H pip3 install numpy dlib face_recognition opencv-python scikit-learn
sudo -H pip3 install imutils
# A number of additional ubuntu pacakges are needed, see dlib documentation
# XXX: update from emulator VM build process which has all deps
```

## Other Tools

None

