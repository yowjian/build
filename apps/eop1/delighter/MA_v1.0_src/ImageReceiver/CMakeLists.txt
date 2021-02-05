add_executable(ImageReceiver
   RunImageReceiver.cpp
   ImageReceiver.cpp
)

target_include_directories(ImageReceiver PRIVATE ../include ../install/include/opencv4/)
target_link_libraries(ImageReceiver PRIVATE 
  activemq-cpp
  pthread
  boost_system
  boost_filesystem
  
  opencv_core opencv_dnn opencv_highgui opencv_imgproc opencv_videoio opencv_imgcodecs      
)
