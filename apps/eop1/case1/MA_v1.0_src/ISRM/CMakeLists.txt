add_executable(ISRM
   RunISRM.cpp
   ISRM.cpp
)
target_include_directories(ISRM PRIVATE ../include)
target_link_libraries(ISRM PRIVATE 
  activemq-cpp
  pthread
)
