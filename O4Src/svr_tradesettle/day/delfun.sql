
DELETE FROM QS_TFLOWTRANSACTION T WHERE T.FUND_ID=-1 AND T.MARKET_GROUP_NO=&1 AND T.FLOW_ID=&2 AND T.FUNC_ID=&3
AND EXISTS
(SELECT 1 FROM 
(select  T1.MARKET_GROUP_NO,min(t1.liquidate_date) liquidate_date
from qs_tmarketgroup t1 
where t1.market_group_no=&1 or &1 = -1
GROUP BY T1.MARKET_GROUP_NO
order by t1.market_group_no desc) S2 WHERE T.BUSINESS_DATE=S2.liquidate_date
)
;
commit;
delete from qs_tflowlog t where t.market_group_no = &1 and t.flow_id = &2 and t.operator_no = &4;
commit;
quit
