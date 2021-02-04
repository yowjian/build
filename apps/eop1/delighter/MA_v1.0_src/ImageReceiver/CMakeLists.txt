add_executable(ImageReceiver
   RunImageReceiver.cpp
   ImageReceiver.cpp
)
target_include_directories(ImageReceiver PRIVATE ../include)
target_link_libraries(ImageReceiver PRIVATE 
  activemq-cpp
  pthread
)
