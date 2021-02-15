add_executable(External
   RunExternal.cpp
   Ground_Movers.cpp
)
target_include_directories(External PRIVATE 
  ../include 
) 
target_link_libraries(External PRIVATE 
  activemq-cpp
  pthread
)
