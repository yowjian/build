#ifndef _MDLOOKUP_H_
#define _MDLOOKUP_H_

#include <sqlite3.h>
#include <stdio.h>

void stop_database(void);
void start_database(char *dbfile);
int  lookup(char *fname, char *mi, char *lname);

#endif /* _MDLOOKUP_H_ */
