#include "secdesk.h"

int main(int argc, char const *argv[]) {
  /* Initialize web application */
  initialize_cli(argc, argv);
  initialize_http_service();
  fio_start(.threads = fio_cli_get_i("-t"), .workers = fio_cli_get_i("-w"));

  /* XXX: Initialize database */
  /* XXX: Initialize image processing */

  /* XXX: Close image processing */
  /* XXX: Close database */

  /* Close web application */
  free_cli();
  return 0;
}
