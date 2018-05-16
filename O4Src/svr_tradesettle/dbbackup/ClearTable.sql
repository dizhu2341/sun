set termout off
set term     off
set linesize 100
set feedback off
set colsep ' '
set echo off
set heading off
set trimout off
set trimspool off
set wrap off
set verify off
set pagesize 0

spool &1

select 'truncate table ' || table_name || ';'
 from qs_tbackupconfig where subsys_no= &2  union all
 select 'quit;' 
 from dual;


spool off

quit