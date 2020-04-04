#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <ctype.h>
#include <semaphore.h>

int main()
{
  char *sent = "sent";
  char *msg = "sent 2 18";

  int id, expected;
  sscanf("%d %d", msg + strlen(sent) + 1, &id, &expected);

printf(".......... '%s' %d %d \n", msg + strlen(sent) + 1, id, expected);
}
