#include "initenable.h"

#ifdef __cplusplus
extern "C" {
#endif

void addBalanceEnableData(IF2Packer* outPack,TBeginBalanceEnable *pArrBeginBalanceEnable,int nRow,int nEnableCalcFactor)
{
	outPack->AddInt(pArrBeginBalanceEnable[nRow].business_date);
	outPack->AddInt(pArrBeginBalanceEnable[nRow].asset_id);
	outPack->AddStr(pArrBeginBalanceEnable[nRow].currency_no);
	outPack->AddInt(nEnableCalcFactor);
	outPack->AddDouble(pArrBeginBalanceEnable[nRow].factor_value_cash);
}

void addStockEnableData(IF2Packer* outPack,TBeginStockEnable *pArrBeginStockEnable,int nRow,int nEnableCalcFactor)
{
	 outPack->AddInt(pArrBeginStockEnable[nRow].business_date);
	 outPack->AddInt(pArrBeginStockEnable[nRow].combi_id);
	 outPack->AddChar(pArrBeginStockEnable[nRow].market_no);
	 outPack->AddStr(pArrBeginStockEnable[nRow].stockholder_id);
	 outPack->AddStr(pArrBeginStockEnable[nRow].bind_seat);
	 outPack->AddChar(pArrBeginStockEnable[nRow].invest_type);
	 outPack->AddChar(pArrBeginStockEnable[nRow].position_type);
	 outPack->AddInt(pArrBeginStockEnable[nRow].inter_code);
	 outPack->AddInt(nEnableCalcFactor);
	 outPack->AddDouble(pArrBeginStockEnable[nRow].factor_value_stock);
}

int get_enable_balance(IF2UnPacker* inPack, IF2Packer* outPack)
{
  TPackage* pkgEnable = NULL;
  int i,j,rec_count = 0;
  int ret = 0;
  char rec_name[64];
  char rec_value[102400];
  char Sendbuffer[MAX_LINE_LEN];
  char RecvBuffer[MAX_LINE_LEN];
  int account_id = 0;
  int asset_id = 0;
  double enable_t1_balance = 0.00;
  TBeginBalanceEnable *pArrBeginBalanceEnable = NULL;
  int iNo = 0;
  int iAllRows = 0;
  int nRow = 0;
  int nRowCount = 0;
  int nColCount = 0;
  
  iAllRows = 600;
  nRowCount = inPack->GetRowCount();
  nColCount = inPack->GetColCount();
  
  pArrBeginBalanceEnable = (TBeginBalanceEnable *)malloc(sizeof(TBeginBalanceEnable) * (unsigned int)nRowCount);
  if (pArrBeginBalanceEnable == NULL)
  {
    hsWriteLog(1, "[get_enable_balance]pArrBeginBalanceEnable malloc申请内存失败");
    return -1;
  }
  memset(pArrBeginBalanceEnable, 0, sizeof(TBeginBalanceEnable) * (unsigned int)nRowCount);  
  while (!inPack->IsEOF())
  {
  	if (pkgEnable == NULL)
  	    pkgEnable = PInit();
  	iNo = nRow%iAllRows;
  	pArrBeginBalanceEnable[nRow].business_date = inPack->GetInt("BUSINESS_DATE");
  	pArrBeginBalanceEnable[nRow].asset_id = inPack->GetInt("ASSET_ID");
  	strcpy(pArrBeginBalanceEnable[nRow].currency_no,inPack->GetStr("CURRENCY_NO"));
  	pArrBeginBalanceEnable[nRow].enable_calc_factor = inPack->GetInt("ENABLE_CALC_FACTOR");
  	pArrBeginBalanceEnable[nRow].factor_value_cash = inPack->GetDouble("FACTOR_VALUE_CASH");
  	pArrBeginBalanceEnable[nRow].fund_id = inPack->GetInt("FUND_ID");
  	
		sprintf(rec_name, "record%d", iNo); /*recordN从0开始计数,最大为l_query_count-1*/
		sprintf(rec_value, "%d|%d|0|0|0|%s", pArrBeginBalanceEnable[nRow].fund_id, pArrBeginBalanceEnable[nRow].asset_id,pArrBeginBalanceEnable[nRow].currency_no);
		PAddItemString(pkgEnable,rec_name, rec_value);
		
		if ((iNo == iAllRows - 1) || (nRow == nRowCount - 1))
		{
      PAddItemString(pkgEnable,"vc_query_type", "ENTRUSTENABLE");
      PAddItemInt(pkgEnable,"l_query_count",iNo+1);
			//准备服务入参
			memset(Sendbuffer,0,MAX_LINE_LEN);
			memset(RecvBuffer,0,MAX_LINE_LEN);
			PGetText(pkgEnable, Sendbuffer, MAX_LINE_LEN);
			PFree(pkgEnable);
			pkgEnable = NULL;
			hsWriteLog(2,"[get_entrust_balance]svc_qry_balance 传入参数:%s",Sendbuffer);
			//获取可用
			//ret = GetEnableBalance(Sendbuffer, RecvBuffer);
			ret = CallService("svc_qry_balance", Sendbuffer, RecvBuffer);
			if (ret != 0)
			{
				hsWriteLog(2,"[get_entrust_balance]取可用出错");
				if (pArrBeginBalanceEnable != NULL)
             free(pArrBeginBalanceEnable);
				return -1;
			}
			//解析出参
			pkgEnable=PInit();
	  	PSetText(pkgEnable,RecvBuffer);
	  	if (PGetItemInt(pkgEnable,"l_return_count",&rec_count))
	  	{
	   		hsWriteLog(2,"[get_entrust_balance]取l_return_count出错");
	    	PFree(pkgEnable);
	    	if (pArrBeginBalanceEnable != NULL)
             free(pArrBeginBalanceEnable);
	    	return -1;  
	  	}
	  	for(i=0;i<rec_count;i++)
  		{
    		sprintf(rec_name, "record%d", i);
    		if (PGetItemString(pkgEnable,rec_name,rec_value))
    		{
      		hsWriteLog(2,"[get_entrust_balance]取%s出错",rec_name);
      		continue;
    		}
    		hsWriteLog(2,"[get_entrust_balance]取可用返回:%s",rec_value);
    		GetColInteger(rec_value, &account_id, '|', 0);
        GetColInteger(rec_value, &asset_id, '|', 1);
		    GetColDouble(rec_value, &enable_t1_balance, '|', 6);//获取服务返回值中T+1可用金额
		    for (j=0;j<=nRow;j++)
		    {
		    	if ((pArrBeginBalanceEnable[j].fund_id == account_id) && (pArrBeginBalanceEnable[j].asset_id == asset_id))
		    	{
		    	   pArrBeginBalanceEnable[j].factor_value_cash = enable_t1_balance;	 
		    	}
		    }
  		}
  		PFree(pkgEnable);
  		pkgEnable = NULL;
	  }
    inPack->Next();
	  nRow++;
	}
  //------------------------------------------------------
  // 打包到输出结果集
  outPack->BeginPack();
  inPack->First();
  nRow = 0;
  //打包t2包头
  for (i=0; i < nColCount; ++i)
  {
  	if (i == 5) /*UFT资金可用同步初始化接口字段个数*/
  		 break;
   	outPack->AddField(inPack->GetColName(i), inPack->GetColType(i));
  } 	
  while(!inPack->IsEOF())
  {
  	hsWriteLog(3,"pArrBeginBalanceEnable[%d].business_date=%d",nRow,pArrBeginBalanceEnable[nRow].business_date);
  	hsWriteLog(3,"pArrBeginBalanceEnable[%d].asset_id=%d",nRow,pArrBeginBalanceEnable[nRow].asset_id);
  	hsWriteLog(3,"pArrBeginBalanceEnable[%d].currency_no=%s",nRow,pArrBeginBalanceEnable[nRow].currency_no);
  	hsWriteLog(3,"pArrBeginBalanceEnable[%d].enable_calc_factor=%d",nRow,pArrBeginBalanceEnable[nRow].enable_calc_factor);
  	hsWriteLog(3,"pArrBeginBalanceEnable[%d].factor_value_cash=%f",nRow,pArrBeginBalanceEnable[nRow].factor_value_cash);
  	hsWriteLog(3,"pArrBeginBalanceEnable[%d].fund_id=%d",nRow,pArrBeginBalanceEnable[nRow].fund_id);
  	
  	addBalanceEnableData(outPack,pArrBeginBalanceEnable,nRow,3);
  	nRow++;
    inPack->Next();
  }
  outPack->EndPack();
  //释放空间
  if (pArrBeginBalanceEnable != NULL)
      free(pArrBeginBalanceEnable);
  return 0;
}

/*现货数量可用*/
int get_stock_enable(IF2UnPacker* inPack, IF2Packer* outPack)
{
  TPackage* pkgEnable = NULL;
  int i,rec_count = 0;
  int ret = 0;
  char rec_name[64];
  char rec_value[102400];
  char Sendbuffer[MAX_LINE_LEN];
  char RecvBuffer[MAX_LINE_LEN];
  double enable_t1_amount = 0.00;
  TBeginStockEnable *pArrBeginStockEnable = NULL; /*二级市场可用*/
  int nRowCount = 0;
  int nColCount = 0;
  int iNo = 0;
  int iAllRows = 0;
  int nRow = 0;
  int nQueryCount = 0;
  int *pArrEnableIndex = NULL;
  
  iAllRows = 400;
  nRowCount = inPack->GetRowCount();
  nColCount = inPack->GetColCount();
  
  pArrBeginStockEnable = (TBeginStockEnable *)malloc(sizeof(TBeginStockEnable) * (unsigned int)nRowCount);
  if (pArrBeginStockEnable == NULL)
  {
    hsWriteLog(1, "[get_stock_enable]系统异常，pArrBeginStockEnable malloc申请内存失败");
    return -1;
  }
  memset(pArrBeginStockEnable, 0, sizeof(TBeginStockEnable) * (unsigned int)nRowCount);
  
  pArrEnableIndex = new int[nRowCount];
  memset(pArrEnableIndex, 0, sizeof(int)*nRowCount);
  
  while (!inPack->IsEOF())
  {
  	if (pkgEnable == NULL)
  	    pkgEnable = PInit();
  	iNo = nRow%iAllRows;
  	pArrBeginStockEnable[nRow].business_date = inPack->GetInt("BUSINESS_DATE");
  	pArrBeginStockEnable[nRow].combi_id = inPack->GetInt("COMBI_ID");
  	pArrBeginStockEnable[nRow].market_no = inPack->GetChar("MARKET_NO");
  	strcpy(pArrBeginStockEnable[nRow].stockholder_id,inPack->GetStr("STOCKHOLDER_ID"));
  	strcpy(pArrBeginStockEnable[nRow].bind_seat,inPack->GetStr("BIND_SEAT"));
  	pArrBeginStockEnable[nRow].invest_type = inPack->GetChar("INVEST_TYPE");
  	pArrBeginStockEnable[nRow].position_type = inPack->GetChar("POSITION_TYPE");
  	pArrBeginStockEnable[nRow].inter_code = inPack->GetInt("INTER_CODE");
  	pArrBeginStockEnable[nRow].enable_calc_factor = inPack->GetInt("ENABLE_CALC_FACTOR");
  	pArrBeginStockEnable[nRow].factor_value_stock = inPack->GetDouble("FACTOR_VALUE_STOCK");
  	pArrBeginStockEnable[nRow].stock_type = inPack->GetChar("STOCK_TYPE");
  	pArrBeginStockEnable[nRow].etf_type = inPack->GetChar("ETF_TYPE");
  	pArrBeginStockEnable[nRow].entrust_direction = inPack->GetChar("ENTRUST_DIRECTION");
  	strcpy(pArrBeginStockEnable[nRow].o3_inter_code,inPack->GetStr("O3_INTER_CODE"));
  	/*只有现货才调可用服务，个股期权、股指期货、商品期货、国债期货的可用数量，在SQL中已计算*/
    if (strchr("RWv()",pArrBeginStockEnable[nRow].stock_type) == NULL)
  	{
  		 sprintf(rec_name,"record%d",nQueryCount);
       sprintf(rec_value,"%c|0|0|%d|%s|%s|%s|%c",pArrBeginStockEnable[nRow].entrust_direction,pArrBeginStockEnable[nRow].combi_id,pArrBeginStockEnable[nRow].o3_inter_code,pArrBeginStockEnable[nRow].stockholder_id,pArrBeginStockEnable[nRow].bind_seat,pArrBeginStockEnable[nRow].invest_type);/*委托方向|预置指令序号|当日指令序号|组合|证券内码|股东|席位|投资类型*/
       PAddItemString(pkgEnable,rec_name, rec_value);
       pArrEnableIndex[nQueryCount] = nRow; /*需要计算可用的下标*/
       nQueryCount++;
    }
    if ((iNo == iAllRows - 1) || (nRow == nRowCount - 1))
		{
       PAddItemInt(pkgEnable,"l_query_count", nQueryCount);/*查询数量*/
       PAddItemString(pkgEnable,"vc_query_type", "ENTRUSTENABLE");
       PAddItemChar(pkgEnable,"c_busin_class", '1');/*业务分类*/
       nQueryCount = 0;
       memset(Sendbuffer,0,MAX_LINE_LEN);
       memset(RecvBuffer,0,MAX_LINE_LEN);
       PGetText(pkgEnable, Sendbuffer, MAX_LINE_LEN);
			 PFree(pkgEnable);
			 pkgEnable = NULL;
       hsWriteLog(2,"[get_stock_enable]svc_qry_amount 传入参数:%s",Sendbuffer);
       //ret = GetEnableAmount(Sendbuffer, RecvBuffer);
       ret = CallService("svc_qry_amount", Sendbuffer, RecvBuffer);     
       if (ret != 0)
       {
          hsWriteLog(2,"[get_stock_enable]取可用出错");
          delete[] pArrEnableIndex;
          if (pArrBeginStockEnable != NULL)
             free(pArrBeginStockEnable);
          return -1;
       }
       //解析出参
       pkgEnable=PInit();
	  	 PSetText(pkgEnable,RecvBuffer); 
       if (PGetItemInt(pkgEnable,"l_return_count",&rec_count))
       {
          hsWriteLog(2,"[get_stock_enable]取l_return_count出错");
          PFree(pkgEnable);
          delete[] pArrEnableIndex;
          if (pArrBeginStockEnable != NULL)
             free(pArrBeginStockEnable);
          return -1;  
       }
       hsWriteLog(2,"[get_stock_enable]rec_count=%d",rec_count);
       for(i=0;i<rec_count;i++)
       {
       	 sprintf(rec_name, "record%d", i);
       	 if (PGetItemString(pkgEnable,rec_name,rec_value))
       	 {
       	 	 hsWriteLog(2,"[get_stock_enable]取%s出错",rec_name);
       	 	 continue;
       	 }
       	 hsWriteLog(2,"[get_stock_enable]取可用返回:%s",rec_value);
       	 GetColDouble(rec_value, &enable_t1_amount, '|', 3);//获取服务返回值中T+1可用数量	
       	 pArrBeginStockEnable[pArrEnableIndex[i]].factor_value_stock = enable_t1_amount;
       }
       PFree(pkgEnable);
       pkgEnable = NULL;
    }
    inPack->Next();
    nRow++;
  }
  if (pArrEnableIndex != NULL)
  	delete[] pArrEnableIndex;
	//------------------------------------------------------
  // 打包到输出结果集
  outPack->BeginPack();
  inPack->First();
  nRow = 0;
  for (i=0; i < nColCount; ++i)
  {
  	if (i == 10) /*UFT持仓可用同步初始化接口字段个数*/
  		  break;
   	outPack->AddField(inPack->GetColName(i), inPack->GetColType(i));   //打包t2包头
  } 	
  while(!inPack->IsEOF())
  {
  	hsWriteLog(3,"pArrBeginStockEnable[%d].business_date=%d",nRow,pArrBeginStockEnable[nRow].business_date);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].combi_id=%d",nRow,pArrBeginStockEnable[nRow].combi_id);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].market_no=%c",nRow,pArrBeginStockEnable[nRow].market_no);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].stockholder_id=%s",nRow,pArrBeginStockEnable[nRow].stockholder_id);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].bind_seat=%s",nRow,pArrBeginStockEnable[nRow].bind_seat);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].invest_type=%c",nRow,pArrBeginStockEnable[nRow].invest_type);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].position_type=%c",nRow,pArrBeginStockEnable[nRow].position_type);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].inter_code=%d",nRow,pArrBeginStockEnable[nRow].inter_code);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].enable_calc_factor=%d",nRow,pArrBeginStockEnable[nRow].enable_calc_factor);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].factor_value_stock=%f",nRow,pArrBeginStockEnable[nRow].factor_value_stock);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].stock_type=%c",nRow,pArrBeginStockEnable[nRow].stock_type);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].etf_type=%c",nRow,pArrBeginStockEnable[nRow].etf_type);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].entrust_direction=%c",nRow,pArrBeginStockEnable[nRow].entrust_direction);
  	hsWriteLog(3,"pArrBeginStockEnable[%d].o3_inter_code=%s",nRow,pArrBeginStockEnable[nRow].o3_inter_code);
  	
  	if ((pArrBeginStockEnable[nRow].stock_type == '1') || ((pArrBeginStockEnable[nRow].stock_type == 'F') && (pArrBeginStockEnable[nRow].etf_type != '0')))  /*股票和ETF基金*/
    {
    	 addStockEnableData(outPack,pArrBeginStockEnable,nRow,2); /*一级市场可用*/
    	 addStockEnableData(outPack,pArrBeginStockEnable,nRow,1); /*二级市场可用*/
    	 addStockEnableData(outPack,pArrBeginStockEnable,nRow,6); /*标的券备兑可用*/
    	 addStockEnableData(outPack,pArrBeginStockEnable,nRow,8); /*标的券锁定可用*/
    }
    else if(strchr("()",pArrBeginStockEnable[nRow].stock_type) != NULL) /*期权*/
    {
    	 addStockEnableData(outPack,pArrBeginStockEnable,nRow,9);
    }
    else if(strchr("RWv",pArrBeginStockEnable[nRow].stock_type) != NULL) /*期货*/
    {
    	 addStockEnableData(outPack,pArrBeginStockEnable,nRow,10); 
    }	
    else  /*其他证券*/
    {
    	 addStockEnableData(outPack,pArrBeginStockEnable,nRow,1);
    }
    nRow++;
    inPack->Next();
  }
  outPack->EndPack();
  //释放空间
  if (pArrBeginStockEnable != NULL)
      free(pArrBeginStockEnable);
  return 0; 
}

#ifdef __cplusplus
}
#endif

