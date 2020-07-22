#include "webapp.h"

void initialize_cli(int argc, char const *argv[]) {
  fio_cli_start(
      argc, argv, 0, 0, NULL, 
      FIO_CLI_PRINT_HEADER("Address binding:"),
      FIO_CLI_INT("-port -p port number to listen to. default: port 3000"),
      FIO_CLI_STRING("-bind -b address to listen to. default: any available."),
      FIO_CLI_PRINT_HEADER("Concurrency:"),
      FIO_CLI_INT("-workers -w number of processes to use."),
      FIO_CLI_INT("-threads -t number of threads per process."),
      FIO_CLI_PRINT_HEADER("HTTP Server:"),
      FIO_CLI_STRING("-public -www public folder, for static file service."),
      FIO_CLI_INT("-keep-alive -k HTTP keep-alive timeout (0..255). default: ~5s"),
      FIO_CLI_INT("-max-body -maxbd HTTP upload limit. default: ~50Mb"),
      FIO_CLI_BOOL("-log -v request verbosity (logging)."),
      FIO_CLI_PRINT_HEADER("Database:"),
      FIO_CLI_STRING("-database -db The database adrress (URL)."));

  if (!fio_cli_get("-b")) {
    char *tmp = getenv("ADDRESS");
    if (tmp) {
      fio_cli_set("-b", tmp);
      fio_cli_set("-bind", tmp);
    }
  }
  if (!fio_cli_get("-p")) {
    char *tmp = getenv("PORT");
    if (!tmp && !fio_cli_get("-b")) tmp = "3000";
    fio_cli_set("-p", tmp);
    fio_cli_set("-port", tmp);
  }
  if (!fio_cli_get("-www")) {
    char *tmp = getenv("HTTP_PUBLIC_FOLDER");
    if (tmp) {
      fio_cli_set("-public", tmp);
      fio_cli_set("-www", tmp);
    }
  }
  if (!fio_cli_get("-db")) {
    char *tmp = getenv("DBURI");
    if (!tmp) tmp = "sqlite://./eridemo2020.sqlite3.db";
    fio_cli_set("-database", tmp);
    fio_cli_set("-db", tmp);
  }
}

void housekeep_http_service(void) { 
  fio_cli_end(); 
}

static void on_http_request(http_s *h);

/* starts a listeninng socket for HTTP connections. */
void initialize_http_service(int argc, char const *argv[]) {
  initialize_cli(argc, argv);
  if (http_listen(fio_cli_get("-p"), fio_cli_get("-b"),
                  .on_request    = on_http_request,
                  .public_folder = fio_cli_get("-www"),
                  .timeout       = fio_cli_get_i("-k"),
                  .max_body_size = fio_cli_get_i("-maxbd") * 1024 * 1024,
                  .log           = fio_cli_get_bool("-v")) == -1) {
    perror("ERROR: facil couldn't initialize HTTP service (already running?)");
    exit(1);
  }
  fio_start(.threads = fio_cli_get_i("-t"), .workers = fio_cli_get_i("-w"));
}

static void on_http_request(http_s *h) {
  #define ERRCLN(x) if(x) perror(x);http_send_error(h,404);goto cleanup;
  fio_str_info_s path, method, tmp;
  path = fiobj_obj2cstr(h->path);
  method = fiobj_obj2cstr(h->method);

  if ((strcmp(path.data,"/check_person") != 0) 
      || (strcmp(method.data,"POST") != 0)
      || (http_parse_body(h) == -1)) { ERRCLN(NULL) }

  tmp = fiobj_obj2cstr(http_req2str(h));
  fprintf(stderr, "%s",  tmp.data);

  /* get image file, extract features from image and call recognizer */

  /* get form fields, query metadata */
 
  /* check if image ID and metadata ID match */

  /* construct response and send depending on outcome */

  int outcome = 0;
  if (outcome) {
    http_send_body(h, "PERMITTED!", 10);
  } else {
    http_send_body(h, "DENIED!", 7);
  }

  cleanup: http_finish(h); return;
}

