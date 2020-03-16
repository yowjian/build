CPPFLAGS=-std=c++11

pnt: pnt_example.o ownship.o target.o rpc.o
	$(CXX) -o $@ $^ -lrpc -lpthread
clean:
	rm -f pnt *.o
