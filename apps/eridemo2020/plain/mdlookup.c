#include "mdlookup.h"

/*
int callback(void *, int, char **, char **);

sqlite3 *open_db(char *dbfile) {
    int rc = sqlite3_open(dbfile, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

void close_db(sqlite3 *db)
    sqlite3_close(db);
}
*/

/*
    char *err_msg = 0;
    char *sql = "SELECT * FROM Cars";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    } 
    

int callback(void *notUsed, int argc, char **argv, char **azColName) {
    notUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

*/
