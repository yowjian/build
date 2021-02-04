add_executable(ImageDetector
   RunImageDetector.cpp
   ImageDetector.cpp
)
target_include_directories(ImageDetector PRIVATE ../include)
target_link_libraries(ImageDetector PRIVATE 
  activemq-cpp
  pthread
  boost_system
  boost_filesystem
)
