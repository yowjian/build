#include "mdlookup.h"

static sqlite3 *get_database(const char *dbfile) {
  static sqlite3 *db = NULL;
  if (dbfile) {
    if (db) sqlite3_close(db);
    int rc = sqlite3_open(dbfile, &db);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      db = NULL;
    }
  }
  return db;
}

void stop_database(void) {
  sqlite3 *db = get_database(NULL);
  if (db) sqlite3_close(db);
}

void start_database(const char *dbfile) {
  if (!get_database(dbfile)) perror("ERROR opening database");
}

int callback(void *notUsed, int argc, char **argv, char **azColName) {
  notUsed = 0;
  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int lookup(const char *fname, const char *mi, const char *lname) {
  sqlite3 *db = get_database(NULL);
  char *err_msg = 0;
  char *sql = "SELECT * FROM mdata";
  int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
  if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  } 
  return -1;
}

