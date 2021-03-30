add_executable(Sender
   RunSender.cpp
   Sender.cpp
)
target_include_directories(Sender PRIVATE ../include ../install/include/opencv4/)
target_link_libraries(Sender PRIVATE 
  activemq-cpp
  pthread
  boost_system
  boost_filesystem
  
  opencv_core opencv_dnn opencv_highgui opencv_imgproc opencv_videoio opencv_imgcodecs      
)
  
