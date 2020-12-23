add_executable(RDR
   RunRDR.cpp
   RDR.cpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_include_directories(RDR PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(RDR PRIVATE 
  activemq-cpp
  pthread
)
