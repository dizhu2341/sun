set termout  off
set term     off
set timi     off
set wrap     off
set colsep   ''
set heading  off;
set pagesize 0;
set feedback off;
set linesize 92
set verify off
col linestr  format A92
spool &1/gztype.txt

select t.param_value from qs_tsysparamvalue t where t.sysparam_no=810004;

spool off
quit