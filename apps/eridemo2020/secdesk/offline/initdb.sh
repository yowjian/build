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
(666, "Hannibal", "", "Lecter"),
(007, "Daniel", "", "Craig"),
(101, "Alan", "", "Grant"),
(102, "Clarie", "", "Dearing"),
(103, "Ellie", "", "Sattler"),
(104, "Ian", "", "Malcolm"),
(105, "John", "", "Hammond"),
(106, "Owen", "", "Grady");

EOF

