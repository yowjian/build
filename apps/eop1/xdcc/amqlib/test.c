#include "amqlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle(const char *js) {
    puts(js);
}

int main() {
    amqlib_t *amq = amqlib_create();
    amqlib_listen (amq, "testest",  handle, 1);
    amqlib_publish(amq, "testest",  "{\"hello\": \"world\"}", 1);
    sleep(3);
    amqlib_destroy(amq);
    return 0;
}

