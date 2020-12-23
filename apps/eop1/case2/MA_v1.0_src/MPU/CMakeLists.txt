add_executable(MPU
   RunMPU.cpp
   MPU.cpp
)
target_include_directories(MPU PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(MPU PRIVATE 
  activemq-cpp
  pthread
)
