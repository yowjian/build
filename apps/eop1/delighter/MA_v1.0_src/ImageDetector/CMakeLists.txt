add_executable(ImageDetector
   RunImageDetector.cpp
   ImageDetector.cpp
)
target_include_directories(ImageDetector PRIVATE ../include ../install/include/opencv4/)
target_link_libraries(ImageDetector PRIVATE 
  activemq-cpp
  pthread
  boost_system
  boost_filesystem
  
  opencv_core opencv_dnn opencv_highgui opencv_imgproc opencv_videoio opencv_imgcodecs      
)
  
