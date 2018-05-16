#include "rj_msg.h"
#include "rj_msg_mgr.h"
#include "hshead.h"

#include "Include/biz_comp_interface.h"
#include "Include/f2core_interface.h"
#include "IncludeFm/s_liblogpublic.h"
#include "IncludeFm/s_libpublic.h"

//账户信息
int FUNCTION_CALL_MODE F2615211(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920001】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920001", "jc_tfundinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//资产单元
int FUNCTION_CALL_MODE F2615212(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920002】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920002", "jc_tasset");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//组合信息
int FUNCTION_CALL_MODE F2615213(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920003】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920003", "jc_tcombi");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}



//股东信息
int FUNCTION_CALL_MODE F2615215(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920005】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920005", "jc_tstockholder");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//股东与账户关系
int FUNCTION_CALL_MODE F2615216(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920006】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920006", "jc_tentruststockholder");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//席位信息
int FUNCTION_CALL_MODE F2615217(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920007】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920007", "jc_tseat");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//席位与账户信息
int FUNCTION_CALL_MODE F2615218(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920008】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920008", "jc_ttradeseat");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//交易日
int FUNCTION_CALL_MODE F2615220(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920010】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920010", "jc_ttradedate");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//操作员
int FUNCTION_CALL_MODE F2615221(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920011】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920011", "jc_toperator");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//账户权限
int FUNCTION_CALL_MODE F2615222(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920012】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920012", "jc_tfundright");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//券商信息
int FUNCTION_CALL_MODE F2615223(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920013】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920013", "jc_tbroker");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//营业部信息
int FUNCTION_CALL_MODE F2615224(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920014】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920014", "jc_tsecuritiesbranch");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//市场信息
int FUNCTION_CALL_MODE F2615225(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920015】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920015", "jc_tmarketinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//证券资料
int FUNCTION_CALL_MODE F2615226(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920016】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920016", "jc_tstock");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//债权属性
int FUNCTION_CALL_MODE F2615227(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920017】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920017", "jc_tbondproperty");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//债券利息税信息
int FUNCTION_CALL_MODE F2615228(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920018】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920018", "jc_tbonddetailproperty");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//期货信息
int FUNCTION_CALL_MODE F2615229(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920019】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920019", "jc_tfuturesinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//期权信息
int FUNCTION_CALL_MODE F2615230(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920020】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920020", "jc_toptionproperty");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ETF信息
int FUNCTION_CALL_MODE F2615231(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920021】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920021", "jc_tetfbasicinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ETF证券
int FUNCTION_CALL_MODE F2615232(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920022】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920022", "jc_tetfstocklistinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//回购参数
int FUNCTION_CALL_MODE F2615233(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920023】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920023", "jc_thgratio");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//期货保证金比例
int FUNCTION_CALL_MODE F2615237(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920027】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920027", "jc_tfuturedepositratio");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//期权保证金
int FUNCTION_CALL_MODE F2615238(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920028】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920028", "jc_toptiondepositset");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//发行人信息
int FUNCTION_CALL_MODE F2615240(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920030】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920030", "jc_tissuer");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//交易对手信息
int FUNCTION_CALL_MODE F2615242(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920032】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920032", "jc_ttraderival");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//公司信息
int FUNCTION_CALL_MODE F2615244(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920034】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920034", "jc_tcompany");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//融资融券标的券
int FUNCTION_CALL_MODE F2615251(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920041】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920041", "jc_trzrqstock");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}



//沪深交易费配置
int FUNCTION_CALL_MODE F2615263(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920053】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920053", "jc_ttradefeeconfighs");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}



//部门信息
int FUNCTION_CALL_MODE F2615266(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920056】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920056", "jc_tdept");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//融资融券证券参数
int FUNCTION_CALL_MODE F2615267(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920057】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920057", "jc_trzrqstockset");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//营业部扩展属性
int FUNCTION_CALL_MODE F2615272(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920062】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920062", "jc_tsecuritiesbranchex");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//债券利息信息
int FUNCTION_CALL_MODE F2615273(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920063】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920063", "jc_tbondrate");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//期货套利代码
int FUNCTION_CALL_MODE F2615275(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920065】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920065", "jc_tfuturearbitrageinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//系统参数值
int FUNCTION_CALL_MODE F2615276(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920066】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920066", "jc_tsysparamvalue");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//公司行为
int FUNCTION_CALL_MODE F2615278(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920068】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920068", "jc_tcorpactioninfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//融资融券配置
int FUNCTION_CALL_MODE F2615281(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920071】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920071", "jc_trzrqconfig");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//汇率表
int FUNCTION_CALL_MODE F2615283(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920073】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920073", "jc_tcurrencyrate");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//利率参数
int FUNCTION_CALL_MODE F2615284(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920074】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920074", "jc_tinterestrate");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//上证LOF基金业务参数
int FUNCTION_CALL_MODE F2615291(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920081】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920081", "jc_tloffundparam");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//银行信息
int FUNCTION_CALL_MODE F2615294(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920084】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920084", "jc_tbankinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//期货品种
int FUNCTION_CALL_MODE F2615295(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920085】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920085", "jc_tfuturekind");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//最小差价
int FUNCTION_CALL_MODE F2615296(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920086】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920086", "jc_tpriceinterval");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//营业部资金账户信息
int FUNCTION_CALL_MODE F2615297(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920087】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920087", "jc_tbranchcaptacctinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//账户分组
int FUNCTION_CALL_MODE F2615299(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920089】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920089", "jc_taccountgroup");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//账户分组对应基金组合
int FUNCTION_CALL_MODE F2615300(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920090】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920090", "jc_tgroupfundcombi");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//操作员账户分组类型权限
int FUNCTION_CALL_MODE F2615301(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920091】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920091", "jc_topacctgrouptyperight");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//费用套属性
int FUNCTION_CALL_MODE F2615304(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920094】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920094", "jc_tfeesetproperty");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//交易费包含的费用设置费用套表
int FUNCTION_CALL_MODE F2615305(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920095】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920095", "jc_tcontainfeeset");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}


//操作员状态信息
int FUNCTION_CALL_MODE F2615313(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920103】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920103", "jc_toperatorstatus");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}


//TA接口数据处理模板
int FUNCTION_CALL_MODE F2615317(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920107】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920107", "jc_ttadealconfig");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//期货跨品种套利组合
int FUNCTION_CALL_MODE F2615318(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920122】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920122", "jc_tfuturekindarbitragecombi");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//证券自定义分类
int FUNCTION_CALL_MODE F2615319(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920123】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920123", "jc_tcustomclass");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//自定义分类
int FUNCTION_CALL_MODE F2615320(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920124】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920124", "jc_tcustomdictionary");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//特殊业务属性
int FUNCTION_CALL_MODE F2615321(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920125】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920125", "jc_tbusinessspecial");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//投资基金信息
int FUNCTION_CALL_MODE F2615325(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920129】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920129", "jc_tinvestfundinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//证券发行信息
int FUNCTION_CALL_MODE F2615323(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920131】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920131", "jc_tstockissueinfo");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//外部评级机构信息
int FUNCTION_CALL_MODE F2615324(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.extjc.920137】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.extjc.920137", "jc_torganization");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//期货费用信息
int FUNCTION_CALL_MODE F2615264(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920054】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920054", "jc_tfeeqh");
//	CRjMsg *RjMsg2 = new CRjMsg(lpContext,  "fund.jc.920054", "jc_tfeedetailqh");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
//	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg2);
		
    return 0;
}

//沪深费用信息
int FUNCTION_CALL_MODE F2615261(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920051】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920051", "jc_tfeehs");
//	CRjMsg *RjMsg2 = new CRjMsg(lpContext,  "fund.jc.920051", "jc_tfeedetailhs");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
//	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg2);
		
    return 0;
}

//禁买权限设置
int FUNCTION_CALL_MODE F2615316(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920100】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920100", "uft_tautoriskpermission");
//	CRjMsg *RjMsg2 = new CRjMsg(lpContext, "fund.jc.920100", "uft_tautoriskparam");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
//	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg2);
			
    return 0;
}

//资金账户
int FUNCTION_CALL_MODE F2615214(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920004】");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920004", "jc_tcapitalaccount");
	
	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//估值科目定义
int FUNCTION_CALL_MODE F2615326(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920147】");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920147", "jc_tfasubjectdefine");

	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//系统科目定义
int FUNCTION_CALL_MODE F2615327(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920148】");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920148", "jc_tsubjectdefine");

	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//产品科目固定计提
int FUNCTION_CALL_MODE F2615328(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920149】");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920149", "jc_tfundsubjectcount");

	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//估值证券代码转换方法模板
int FUNCTION_CALL_MODE F2615329(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920150】");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920150", "jc_tfachangemethod");

	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//估值证券代码转换明细
int FUNCTION_CALL_MODE F2615330(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920151】");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920004", "jc_tfachangedetail");

	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//估值市场代码转换信息
int FUNCTION_CALL_MODE F2615331(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "收到日间消息，主题名【fund.jc.920152】");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920004", "jc_tfachangemarket");

	// 把新增的日间消息放入待处理队列
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

int FUNCTION_CALL_MODE GetBizFunctionsInfo(int Index, LPBIZ_FUNC_INFO ppv)
{
    int iReturnCode = ASFC_EXISTS;
    switch (Index)
    {
        case 0:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615211;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615211;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_日间数据同步_账户信息";
            }
            break;
		case 1:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615212;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615212;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_日间数据同步_资产单元";
            }
            break;
		case 2:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615213;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615213;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_日间数据同步_组合信息";
            }
            break;
		case 3:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615215;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615215;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_日间数据同步_股东信息";
            }
            break;
		case 4:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615216;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615216;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_日间数据同步_股东与账户关系";
            }
            break;
		case 5:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615217;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615217;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_日间数据同步_席位信息";
            }
            break;
		case 6:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615218;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615218;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_日间数据同步_席位与账户信息";
            }
            break;
		case 7:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615220;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615220;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_交易日";
			}
			break;
		case 8:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615221;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615221;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_操作员";
			}
			break;
		case 9:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615222;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615222;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_账户权限";
			}
			break;
		case 10:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615223;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615223;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_券商信息";
			}
			break;
		case 11:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615224;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615224;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_营业部信息";
			}
			break;
		case 12:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615225;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615225;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_市场信息";
			}
			break;
		case 13:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615226;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615226;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_证券信息";
			}
			break;
		case 14:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615227;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615227;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_债券属性";
			}
			break;
		case 15:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615228;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615228;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_债券利息税信息";
			}
			break;
		case 16:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615229;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615229;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_期货信息";
			}
			break;
		case 17:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615230;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615230;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_期权属性";
			}
			break;
		case 18:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615231;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615231;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_ETF信息";
			}
			break;
		case 19:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615232;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615232;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_ETF证券";
			}
			break;
		case 20:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615233;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615233;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_回购参数";
			}
			break;
		case 21:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615237;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615237;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_期货保证金比例";
			}
			break;
		case 22:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615238;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615238;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_期权保证金";
			}
			break;
		case 23:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615240;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615240;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_发行人";
			}
			break;
		case 24:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615242;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615242;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_交易对手信息";
			}
			break;
		case 25:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615244;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615244;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_公司信息";
			}
			break;
		case 26:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615251;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615251;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_融资融券标的券";
			}
			break;
		case 27:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615263;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615263;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_沪深交易费配置";
			}
			break;
		case 28:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615266;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615266;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_部门信息";
			}
			break;
		case 29:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615267;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615267;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_融资融券证券参数";
			}
			break;
		case 30:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615272;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615272;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_营业部扩展属性";
			}
			break;
		case 31:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615273;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615273;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_债券利息信息";
			}
			break;
		case 32:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615275;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615275;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_期货套利代码";
			}
			break;
		case 33:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615276;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615276;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_系统参数值";
			}
			break;
		case 34:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615278;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615278;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_公司行为";
			}
			break;
		case 35:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615281;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615281;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_融资融券配置信息";
			}
			break;
		case 36:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615283;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615283;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_汇率表";
			}
			break;
		case 37:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615284;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615284;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_利率参数";
			}
			break;
		case 38:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615291;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615291;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_上证LOF基金业务参数";
			}
			break;
		case 39:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615294;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615294;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_银行信息";
			}
			break;
		case 40:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615295;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615295;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_期货品种";
			}
			break;
		case 41:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615296;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615296;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_最小差价";
			}
			break;
		case 42:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615297;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615297;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_营业部资金账号信息";
			}
			break;
		case 43:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615299;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615299;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_账户分组";
			}
			break;
		case 44:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615300;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615300;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_账户分组对应基金组合";
			}
			break;
		case 45:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615301;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615301;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_操作员账户分组类型权限";
			}
			break;
		case 46:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615304;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615304;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_费用套属性表";
			}
			break;
		case 47:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615305;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615305;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_交易费包含的费用设置费用套表";
			}
			break;
		case 48:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615313;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615313;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_操作员状态信息";
			}
			break;
		case 49:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615317;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615317;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_TA接口数据处理模板";
			}
			break;
		case 50:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615318;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615318;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_期货跨品种套利组合";
			}
			break;
		case 51:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615319;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615319;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_证券自定义分类";
			}
			break;
		case 52:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615320;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615320;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_自定义分类";
			}
			break;
		case 53:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615325;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615325;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_投资基金信息";
			}
			break;
		case 54:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615321;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615321;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_特殊业务属性";
			}
			break;
		case 55:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615323;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615323;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_证券发行信息";
			}
			break;
		case 56:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615324;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615324;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_外部评级机构信息";
			}
			break;
		case 57:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615264;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615264;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_feeqh";
			}
			break;
		case 58:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615261;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615261;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_feehs";
			}
			break;
		case 59:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615316;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615316;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_禁买权限设置";
			}
			break;
		case 60:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615214;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615214;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_资金账户";
			}
			break;
		case 61:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615326;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615215;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_估值科目定义";
			}
			break;
		case 62:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615327;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615327;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_系统科目定义";
			}
			break;
		case 63:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615328;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615328;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_产品科目固定计提";
			}
			break;
		case 64:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615329;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615329;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_估值证券代码转换方法模板";
			}
			break;
		case 65:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615330;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615330;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_估值证券代码转换明细";
			}
			break;
		case 66:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615331;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615331;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_日间数据同步_估值市场代码转换信息";
			}
			break;
		default:
			iReturnCode = ASFC_NONE;
    }
    return iReturnCode;
}

char * ASFC_CALL_MODE GetLibVersion()
{
    return "2.0.1.1";
}

void FUNCTION_CALL_MODE OnLoad(char * arg)
{		
	return;
}

void FUNCTION_CALL_MODE OnUnload()
{
	return;
}

void FUNCTION_CALL_MODE OnStart()
{
	return;
}

void FUNCTION_CALL_MODE OnStop()
{
	return;
}


