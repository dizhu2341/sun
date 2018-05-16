set term     off
set wrap     off
set colsep   ''
set feedback off
declare
v_type varchar2(20):='';
begin
v_type := '&1';
if v_type = '2' then
update qs_tdealfiles t set t.import_flag='2' where t.file_type='&2' and t.file_path='&3';
end if;
if v_type = '0' then
update qs_tdealfiles t set t.import_flag='0' where t.file_path like '%&3';
end if ;
commit;
end;
/
quit