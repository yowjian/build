#!/bin/bash
rm -f secdesk.db && sqlite3 secdesk.db <<EOF

CREATE TABLE IF NOT EXISTS "mdata"
(
  anonid INTEGER PRIMARY KEY NOT NULL,
  fname  VARCHAR(20),
  mi     VARCHAR(6),
  lname  VARCHAR(20)
);

INSERT INTO "mdata" (anonid, fname, mi, lname)
VALUES
(108, "Anjeze", "G." , "Bojaxhiu"),
(666, "Hannibal", "", "Lecter");

EOF

