#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C"  
{  
#endif

#include "spub.h"
#include "t2callserver.h"


typedef struct _TBeginStockEnable
{
  int business_date;
  int combi_id;
  char market_no;
  char stockholder_id[11];
  char bind_seat[7];
  char invest_type;
  char position_type;
  int inter_code;
  int enable_calc_factor;
  double factor_value_stock;
  char stock_type;
  char etf_type;
  char entrust_direction;
  char o3_inter_code[9];
}TBeginStockEnable;

typedef struct _TBeginBalanceEnable
{
  int business_date;
  int asset_id;
  char currency_no[4];
  int enable_calc_factor;
  double factor_value_cash;
  int fund_id;
}TBeginBalanceEnable;

void addBalanceEnableData(IF2Packer* outPack,TBeginBalanceEnable *pArrBeginBalanceEnable,int nRow,int nEnableCalcFactor);

void addStockEnableData(IF2Packer* outPack,TBeginStockEnable *pArrBeginStockEnable,int nRow,int nEnableCalcFactor);

int get_enable_balance(IF2UnPacker* inPack, IF2Packer* outPack);

int get_stock_enable(IF2UnPacker* inPack, IF2Packer* outPack);

#ifdef __cplusplus
}
#endif
