set termout  off
set term     off
set timi     off
set wrap     off
set colsep   ''
set heading  off;
set pagesize 0;
set feedback off;
set linesize 546
set verify off
col linestr  format A546
spool &2/path_load.txt

select distinct rpad(upper(trim(t.table_name)), '30', ' ') ||
                t.file_type||rpad(upper(trim(t.file_subtype)), '3', ' ') ||
                2||
                t.file_path
  from qs_tdealfiles t
 where t.file_type in (&1)
   AND T.IMPORT_FLAG<>'2'
   and exists
   (select 1 from qs_tdealfiles t1
    where upper(trim(t.table_name))=upper(trim(t1.table_name))
      and t1.file_type in (&1)
      and t1.import_flag='2'
   )
union all
select distinct rpad(upper(trim(t.table_name)), '30', ' ') ||
                t.file_type||rpad(upper(trim(t.file_subtype)), '3', ' ') ||
                1||
                t.file_path
  from qs_tdealfiles t
 where t.file_type in (&1)
   AND T.IMPORT_FLAG<>'2'
   and not exists
   (select 1 from qs_tdealfiles t1
    where upper(trim(t.table_name))=upper(trim(t1.table_name))
      and t1.file_type in (&1)
      and t1.import_flag='2'
   ) ;
spool off
quit
