add_executable(EOIR
   RunEOIR.cpp
   EOIR.cpp
   Blob.cpp
   GAPS_opencv_Manager.cpp
)
target_include_directories(EOIR PRIVATE 
  ../include 
  ../install/include/opencv4/
) 
target_link_libraries(EOIR PRIVATE 
  activemq-cpp
  opencv_core opencv_dnn opencv_highgui opencv_imgproc opencv_videoio
  pthread
)
