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

select 'DROP ' || uo.object_type || ' ' || uo.object_name || ';'
from user_objects uo 
where uo.object_type not in('INDEX','LOB','TABLE PARTITION') 
    union all
  select  'quit;' 
  from dual; 

spool off

quit