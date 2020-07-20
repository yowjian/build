#include "webapp.h"

void initialize_cli(int argc, char const *argv[]) {
  fio_cli_start(
      argc, argv, 0, 0, NULL, 
      FIO_CLI_PRINT_HEADER("Address binding:"),
      FIO_CLI_INT("-port -p port number to listen to. defaults port 3000"),
      FIO_CLI_STRING("-bind -b address to listen to. defaults any available."),
      FIO_CLI_PRINT_HEADER("Concurrency:"),
      FIO_CLI_INT("-workers -w number of processes to use."),
      FIO_CLI_INT("-threads -t number of threads per process."),
      FIO_CLI_PRINT_HEADER("HTTP Server:"),
      FIO_CLI_STRING("-public -www public folder, for static file service."),
      FIO_CLI_INT("-keep-alive -k HTTP keep-alive timeout (0..255). default: ~5s"),
      FIO_CLI_INT("-max-body -maxbd HTTP upload limit. default: ~50Mb"),
      FIO_CLI_BOOL("-log -v request verbosity (logging)."),
      FIO_CLI_PRINT_HEADER("WebSocket Server:"),
      FIO_CLI_INT("-ping websocket ping interval (0..255). default: ~40s"),
      FIO_CLI_INT("-max-msg -maxms incoming websocket message size limit. default: ~250Kb"));

  if (!fio_cli_get("-b")) {
    char *tmp = getenv("ADDRESS");
    if (tmp) {
      fio_cli_set("-b", tmp);
      fio_cli_set("-bind", tmp);
    }
  }
  if (!fio_cli_get("-p")) {
    char *tmp = getenv("PORT");
    if (!tmp && !fio_cli_get("-b"))
      tmp = "3000";
    /* Set default port */
    fio_cli_set("-p", tmp);
    fio_cli_set("-port", tmp);
  }
  if (!fio_cli_get("-public")) {
    char *tmp = getenv("HTTP_PUBLIC_FOLDER");
    if (tmp) {
      fio_cli_set("-public", tmp);
      fio_cli_set("-www", tmp);
    }
  }
}

void free_cli(void) { fio_cli_end(); }

/* TODO: edit this function to handle HTTP data and answer Websocket requests.*/
static void on_http_request(http_s *h) {
  /* set a response and send it (finnish vs. destroy). */
  http_send_body(h, "Hello World!", 12);
}

/* starts a listeninng socket for HTTP connections. */
void initialize_http_service(void) {
  /* listen for inncoming connections */
  if (http_listen(fio_cli_get("-p"), fio_cli_get("-b"),
                  .on_request = on_http_request,
                  .max_body_size = fio_cli_get_i("-maxbd") * 1024 * 1024,
                  .ws_max_msg_size = fio_cli_get_i("-max-msg") * 1024,
                  .public_folder = fio_cli_get("-public"),
                  .log = fio_cli_get_bool("-log"),
                  .timeout = fio_cli_get_i("-keep-alive"),
                  .ws_timeout = fio_cli_get_i("-ping")) == -1) {
    /* listen failed ?*/
    perror("ERROR: facil couldn't initialize HTTP service (already running?)");
    exit(1);
  }
}

