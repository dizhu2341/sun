set term     off
set wrap     off
set colsep   ''
set feedback off
INSERT INTO QS_TFLOWLOG
  (BUSINESS_DATE,
   SERIAL_NO,
   DB_DATE,
   DB_TIME,
   FLOW_INFO_TYPE,
   MARKET_GROUP_NO,
   FLOW_ID,
   FUND_ID,
   OPERATOR_NO,
   INFORMATION
   )
VALUES
  (to_number(to_char(sysdate, ' yyyymmdd ')),
   qs_seqtransit.Nextval,
   to_number(to_char(sysdate, ' yyyymmdd ')),
   to_number(to_char(sysdate, ' hh24miss ')),
   '&1',
   &2,
   &3,
   0,
   &4,
   '&5'
   );
COMMIT;
quit;