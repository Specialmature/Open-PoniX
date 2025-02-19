#------------------------------------------------------------------------------
# $File: sql,v 1.6 2009/09/19 16:28:12 christos Exp $
# sql:  file(1) magic for SQL files
#
# From: "Marty Leisner" <mleisner@eng.mc.xerox.com>
# Recognize some MySQL files.
#
0       beshort                 0xfe01          MySQL table definition file
>2	string			<1		invalid
>2	string			>\11		invalid
>2      byte                    x               Version %d
0       string		        \xfe\xfe\x03    MySQL MISAM index file
>3	string			<1		invalid
>3	string			>\11		invalid
>3      byte                    x               Version %d
0       string                  \xfe\xfe\x07    MySQL MISAM compressed data file
>3	string			<1		invalid
>3	string			>\11		invalid
>3      byte                    x               Version %d
0       string                  \xfe\xfe\x05    MySQL ISAM index file
>3	string			<1		invalid
>3	string			>\11		invalid
>3      byte                    x               Version %d
0       string                  \xfe\xfe\x06    MySQL ISAM compressed data file
>3	string			<1		invalid
>3	string			>\11		invalid
>3      byte                    x               Version %d
0       string                  \376bin         MySQL replication log

#------------------------------------------------------------------------------
# iRiver H Series database file 
# From Ken Guest <ken@linux.ie>
# As observed from iRivNavi.iDB and unencoded firmware
#
0   string              iRivDB  iRiver Database file
>11  string     >\0     Version %s
>39  string             iHP-100 [H Series]

#------------------------------------------------------------------------------
# SQLite database files
# Ken Guest <ken@linux.ie>, Ty Sarna, Zack Weinberg
#
# Version 1 used GDBM internally; its files cannot be distinguished
# from other GDBM files.
#
# Version 2 used this format:
0       string  **\x20This\x20file\x20contains\x20an\x20SQLite  SQLite 2.x database

# Version 3 of SQLite allows applications to embed their own "user version"
# number in the database.  Detect this and distinguish those files.

0   string  SQLite\x20format\x203
>60 string  _MTN               Monotone source repository
>60 belong  !0                 SQLite 3.x database, user version %u
>60 belong  0                  SQLite 3.x database
