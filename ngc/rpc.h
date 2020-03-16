#pragma once

#define UAV_PORT 9001
#define TARGET_PORT 9002

extern bool orange_enclave;
class OwnShip;
class Target;
void rpc_init(OwnShip* uav, Target* tgt);

