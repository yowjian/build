add_executable(ISRMshadow
   RunISRMshadow.cpp
   ISRMshadow.cpp
)
target_include_directories(ISRMshadow PRIVATE ../include)
target_link_libraries(ISRMshadow PRIVATE 
  activemq-cpp
  pthread
)
