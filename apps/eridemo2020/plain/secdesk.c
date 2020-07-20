#include "secdesk.h"

int main(int argc, char const **argv) {
  /* Initialize web application */
  initialize_http_service(argc, argv);

  /* XXX: Initialize database */
  /* XXX: Initialize image processing */

  /* XXX: Close image processing */
  /* XXX: Close database */

  /* Cleanup web application */
  housekeep_http_service();
  return 0;
}
