INCLUDE = -I ../../amqlib
INCLUDE += -I ../../amqlib/include
INCLUDE += -I/usr/local/include/activemq-cpp-3.9.5
INCLUDE += -I/usr/local/apr/include/apr-1

LDFLAGS += -lactivemq-cpp -lpthread
CXXFLAGS += -g $(INCLUDE) $(LDFLAGS) -fPIC -Wno-deprecated-declarations
CXX=g++

LIB_OBJ  = xdcc_echo.o
LIB_LIB  = libxdcc_echo.a
LIB_SLIB = libxdcc_echo.so

lib: $(LIB_LIB) $(LIB_SLIB)

$(LIB_LIB): $(LIB_OBJ)
	ar -cvq $@ $^

$(LIB_SLIB): $(LIB_OBJ)
	$(CXX) -shared -o $@ $^ $(CXXFLAGS) 

.PHONY : force-rebuild

.c.o:
	gcc $< -o $@ -c $(CXXFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(LIB_LIB) $(LIB_SLIB) 
