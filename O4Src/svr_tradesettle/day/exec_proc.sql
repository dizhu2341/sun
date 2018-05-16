set term     off
set wrap     off
set colsep   ''
set feedback off
EXEC qs_sp_import(&1,&2,&3,&4);
quit;