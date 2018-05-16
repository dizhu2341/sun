set term     off
set timi     off
set wrap     off
set colsep   ''
set heading  off;
set pagesize 0;
set feedback off;
set linesize 132
set verify off
col linestr  format A132
spool &2/table_load.txt


with   v_tableload as (
select /*+ no_merge(v2) */
       v2.file_type,   v2.parse_type, v2.load_group, v2.table_name,  v2.column_name, v2.data_type,
       v2.data_length, v2.data_scale, v2.column_id,  v2.if_read,     v2.ctl_pos,
       decode(0,v2.if_read,v2.ctl_pos,null) grp,     v2.l_priority
from   (select /*+ no_merge(v1) */
               v1.table_name,  v1.file_type,  v1.parse_type, v1.load_group,  v1.column_name, v1.data_type,
               v1.data_length, v1.data_scale,
               row_number() over (partition by v1.table_name order by v1.column_id) column_id,
               v1.if_read,     V1.l_priority,
               sum(v1.load_length) over (partition by v1.table_name order by v1.column_id rows unbounded preceding) ctl_pos
        from   (select /*+ all_rows leading(t1) use_hash(t2) no_expand full(t1) full(t2) */
                      distinct upper(trim(t1.table_name))  table_name,      
                      upper(substr(t1.file_path,-3)) file_type,     
                       '2'   parse_type, 
                       '1'   load_group,
                       upper(t2.field_name) column_name,
                       t2.field_type data_type,     t2.field_width data_length,   t2.field_scale data_scale,    t2.field_index column_id,
                       decode(upper('N'),upper(t2.if_read),0,1) if_read,
                       decode(upper('N'),upper(t2.if_read),0,t2.field_width) load_length,
                        9  l_priority
                from   qs_tdealfiles t1,qs_tfilecolumn t2
                where  upper(trim(t1.table_name)) = upper(trim(t2.table_name))
                    and t1.file_type IN(&1)
		    and substr(t1.file_path,-3) in ('dbf','txt','DBF','TXT')
                ) v1) v2)
select /*+ no_merge(v8) */
       v8.linestr||lpad(to_char(v8.mem_cpy1),5,'0')||lpad(to_char(v8.mem_cpy2),5,'0')||load_group||v8.first_last||
       lpad(to_char(sum(case when v8.mem_cpy1=0 and v8.mem_cpy2>0 then v8.mem_cpy2 else 0 end) over (partition by v8.table_name)+1),5,'0')||
       lpad(to_char(sum(v8.mem_cpy1) over (partition by v8.table_name)+2),5,'0')||
       lpad(to_char(sum(case when v8.mem_cpy1>0 and v8.mem_cpy2>0 then 1 else 0 end) over (partition by v8.table_name)),4,'0')||
       lpad(to_char(count(*) over (partition by v8.table_name)),4,'0') linestr
from   (select /*+ no_merge(v7) */
               decode(0,v7.if_read,'N','Y')||
               decode(v7.column_id,1,'1','0')||
               v7.file_type||
               v7.parse_type||
               rpad(v7.table_name,30,' ')||
               rpad(v7.column_name,50,' ')||
               v7.data_type||
               lpad(to_char(v7.data_length),3,'0')||
               lpad(to_char(nvl(v7.data_scale,0)),2,'0')||
               lpad(to_char(v7.beg_pos),5,'0')||
               lpad(to_char(v7.end_pos),5,'0') linestr,
               nvl(case when v7.rn=1 then
                         case when v7.if_read=0 then
                                   case when v7.column_id=1 then 0 else v7.cpy1 end
                              else case when v7.mem_grp=v7.max_grp then v7.mem_step else null end end
                    else null end,0) mem_cpy1,
               nvl(case when v7.rn=1 then
                         case when v7.if_read=0 then
                                   case when v7.column_id=1 then v7.mem_step else v7.cpy2 end
                              else case when v7.mem_grp=v7.max_grp then v7.mem_step else null end end
                    else null end,0) mem_cpy2,
               to_char(v7.load_group) load_group,
               case when v7.column_id=v7.first_read then '1' when v7.column_id=v7.last_read then '2' else '0' end first_last,
               v7.l_priority,v7.table_name,v7.column_id
        from   (select /*+ no_merge(v6) */
                       v6.file_type,   v6.parse_type, v6.load_group, v6.table_name, v6.column_name, v6.data_type,
                       v6.data_length, v6.data_scale, v6.column_id,  v6.if_read,    v6.l_priority,  v6.beg_pos,
                       v6.end_pos,     v6.mem_grp,    v6.max_grp,    v6.mem_step,   v6.rn,
                       lag(v6.mem_step,1) over (partition by v6.table_name order by column_id) cpy1,
                       case when v6.rn=1 and v6.if_read=0 then lag(v6.mem_step,1) over (partition by v6.table_name order by column_id)+mem_step else null end cpy2,
                       min(case when v6.if_read=1 then v6.column_id else null end) over (partition by v6.table_name) first_read,
                       max(case when v6.if_read=1 then v6.column_id else 0 end) over (partition by v6.table_name) last_read
                from   (select /*+ no_merge(v5) */
                               v5.file_type,  v5.parse_type, v5.load_group, v5.table_name, v5.column_name, v5.data_type, v5.data_length,
                               v5.data_scale, v5.column_id,  v5.if_read,    v5.l_priority, v5.beg_pos,     v5.end_pos,   v5.mem_grp,
                               max(mem_grp)     over (partition by table_name) max_grp,
                               sum(data_length) over (partition by table_name,mem_grp) mem_step,
                               row_number()     over (partition by table_name,mem_grp order by column_id) rn
                        from   (select /*+ no_merge(v4) */
                                       v4.file_type,   v4.parse_type, v4.load_group, v4.table_name,  v4.column_name, v4.data_type,
                                       v4.data_length, v4.data_scale, v4.column_id,  v4.if_read,     v4.l_priority,
                                       decode(v4.if_read,0,0,v4.beg_pos)   beg_pos,
                                       decode(v4.if_read,0,0,v4.ctl_pos+1) end_pos,
                                       dense_rank() over (partition by v4.table_name order by v4.mem_grp,v4.if_read) mem_grp
                                from   (select /*+ no_merge(v3) */
                                               v3.file_type,   v3.parse_type, v3.load_group, v3.table_name, v3.column_name, v3.data_type,
                                               v3.data_length, v3.data_scale, v3.column_id,  v3.if_read,    v3.ctl_pos,     v3.l_priority,
                                               nvl(lag(v3.ctl_pos,1) over (partition by v3.table_name order by v3.column_id),0)+2 beg_pos,
                                               nvl(last_value(v3.grp ignore nulls) over (partition by v3.table_name order by v3.column_id rows unbounded preceding),0) mem_grp
                                        from   v_tableload v3) v4) v5) v6) v7) v8
order  by v8.load_group,v8.l_priority,v8.table_name,v8.column_id;
spool off
quit
