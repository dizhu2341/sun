set termout  off  --//��ʾ�ű��е������ִ�н����ȱʡΪon 
set term     off
set timi     off
set wrap     off
set colsep   ''   --//������ָ��� 
set heading  off; -- //�������⣬ȱʡΪon 
set pagesize 0;   --//���ÿҳ������ȱʡΪ24,Ϊ�˱����ҳ�����趨Ϊ0�� 
set feedback off; --//���Ա���sql�����ļ�¼������ȱʡΪon 
set linesize 120;
set verify off

spool &2/session.txt

select 'sid=' || s.sid ||'��machine=' ||s.machine||'��program='||s.program||
                  '��locked_object='||o.object_name ||'��lock_mode='||l.locked_mode||'��' as sessioninfo
             from v$session s, v$locked_object l, all_objects o 
            where s.sid=l.session_id and o.object_id=l.object_id and upper(o.owner)=upper('&1');
            
spool off
quit
