set termout  off  --//显示脚本中的命令的执行结果，缺省为on 
set term     off
set timi     off
set wrap     off
set colsep   ''   --//域输出分隔符 
set heading  off; -- //输出域标题，缺省为on 
set pagesize 0;   --//输出每页行数，缺省为24,为了避免分页，可设定为0。 
set feedback off; --//回显本次sql命令处理的记录条数，缺省为on 
set linesize 120;
set verify off

spool &2/session.txt

select 'sid=' || s.sid ||'，machine=' ||s.machine||'，program='||s.program||
                  '，locked_object='||o.object_name ||'，lock_mode='||l.locked_mode||'；' as sessioninfo
             from v$session s, v$locked_object l, all_objects o 
            where s.sid=l.session_id and o.object_id=l.object_id and upper(o.owner)=upper('&1');
            
spool off
quit
