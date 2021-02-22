add_executable(Echoer
   RunEchoer.cpp
   Echoer.cpp
)

target_include_directories(Echoer PRIVATE ../include ../install/include/opencv4/)
target_link_libraries(Echoer PRIVATE 
  activemq-cpp
  pthread
  boost_system
  boost_filesystem
  
  opencv_core opencv_dnn opencv_highgui opencv_imgproc opencv_videoio opencv_imgcodecs      
)
