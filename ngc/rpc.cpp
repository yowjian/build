#include <iostream>
#include "rpc/server.h"
#include "rpc.h"

#include "ownship.h"
#include "target.h"

OwnShip* uav = NULL;
Target* tgt = NULL;

void foo() { std::cout << "foo was called!" << std::endl; }

void bad(int x) {
    if (x == 5) {
        throw std::runtime_error("x == 5. I really don't like 5.");
    }
}

void *rpc_server(void *args) {
    int port = orange_enclave ? UAV_PORT : TARGET_PORT;
    std::cout << "port = " << port << std::endl;
    // Create a server that listens on port 8080, or whatever the user selected
    rpc::server srv("0.0.0.0", port);

    // Binding the name "foo" to free function foo.
    // note: the signature is automatically captured
    srv.bind("foo", &foo);

    // Binding a lambda function to the name "add".
    srv.bind("position", [](double x, double y, double z) {
        Position pos(x, y, z);
        Velocity v(0, 0, 0);  // don't care
        GpsSensor* gps = new GpsSensor(pos, v);
        uav->update(gps);
        return "OK";
    });
    srv.bind("uav", [](double x, double y, double z) {
        Position pos(x, y, z);
        OwnShip* ownship = new OwnShip(100);
        ownship->setPosition(pos);
        tgt->update(ownship);
        return "OK";
    });
    srv.bind("distance", [](double x, double y, double z) {
        Distance distance(x, y, z);
        Velocity vtgt(0, 0, 0);  // don't care
        RfSensor* rfs = new RfSensor(distance, vtgt);
        tgt->update(rfs);
        return "OK";
    });

    // Throwing an exception will cause the server to write
    // an error response. This call will make it also
    // suppress the exception (note that this is not default
    // because this behavior might hide errors in the
    // code).
    srv.suppress_exceptions(true);
    srv.bind("bad", &bad);

    // Run the server loop.
    srv.run();

    return 0;
}

void rpc_init(OwnShip* u, Target* t)
{
   uav = u;
   tgt = t;

   pthread_t rpcThread;

   int rpcThreadID = pthread_create(&rpcThread, NULL, &rpc_server, NULL);
   if (rpcThreadID != 0) {
        throw std::runtime_error("RPC thrad create failed.");
   }
}
