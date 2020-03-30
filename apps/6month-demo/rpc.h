#pragma once

#define UAV_PORT 9001
#define TARGET_PORT 9002

extern bool orange_enclave;

void *hal_init();

extern void *ctx;
