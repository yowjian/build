#ifndef _WEBAPP_H_
#define _WEBAPP_H_

#include <stdlib.h>
#include <string.h>

#include "fio.h"
#include "fio_cli.h"
#include "http.h"

void initialize_cli(int argc, char const *argv[]);
void free_cli(void);
void initialize_http_service(void);

#endif /* _WEBAPP_H_ */
