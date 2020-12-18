CXX = 		gcc
INCLUDES =	-I/usr/local/include/activemq-cpp-3.9.5 -I/usr/include/apr-1.0 
LDFLAGS += 	-lactivemq-cpp -lstdc++

OBJ = 		listener publisher
default: 	all
all: 		$(OBJ)

listener:	Listener.o
		$(CXX) -o $@ $< $(LDFLAGS)

publisher:	Publisher.o
		$(CXX) -o $@ $< $(LDFLAGS)

%.o:		%.cpp
		$(CXX) $< -o $@ -c $(INCLUDES)

clean:
	-rm -f  *.o *~ $(OBJ)

