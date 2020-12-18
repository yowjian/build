add_executable(MPX
   RunMPX.cpp
   MPX.cpp
   TOI.cpp
)

target_include_directories(MPX PRIVATE ${CMAKE_SOURCE_DIR}/include )
target_link_libraries(MPX PRIVATE 
  activemq-cpp
  pthread
)
