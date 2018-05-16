#include "rj_msg.h"
#include "rj_msg_mgr.h"
#include "hshead.h"

#include "Include/biz_comp_interface.h"
#include "Include/f2core_interface.h"
#include "IncludeFm/s_liblogpublic.h"
#include "IncludeFm/s_libpublic.h"

//�˻���Ϣ
int FUNCTION_CALL_MODE F2615211(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920001��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920001", "jc_tfundinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//�ʲ���Ԫ
int FUNCTION_CALL_MODE F2615212(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920002��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920002", "jc_tasset");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//�����Ϣ
int FUNCTION_CALL_MODE F2615213(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920003��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920003", "jc_tcombi");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}



//�ɶ���Ϣ
int FUNCTION_CALL_MODE F2615215(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920005��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920005", "jc_tstockholder");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ɶ����˻���ϵ
int FUNCTION_CALL_MODE F2615216(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920006��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920006", "jc_tentruststockholder");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//ϯλ��Ϣ
int FUNCTION_CALL_MODE F2615217(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920007��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920007", "jc_tseat");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//ϯλ���˻���Ϣ
int FUNCTION_CALL_MODE F2615218(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920008��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920008", "jc_ttradeseat");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//������
int FUNCTION_CALL_MODE F2615220(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920010��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920010", "jc_ttradedate");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//����Ա
int FUNCTION_CALL_MODE F2615221(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920011��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920011", "jc_toperator");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�˻�Ȩ��
int FUNCTION_CALL_MODE F2615222(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920012��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920012", "jc_tfundright");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ȯ����Ϣ
int FUNCTION_CALL_MODE F2615223(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920013��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920013", "jc_tbroker");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//Ӫҵ����Ϣ
int FUNCTION_CALL_MODE F2615224(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920014��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920014", "jc_tsecuritiesbranch");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�г���Ϣ
int FUNCTION_CALL_MODE F2615225(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920015��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920015", "jc_tmarketinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//֤ȯ����
int FUNCTION_CALL_MODE F2615226(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920016��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920016", "jc_tstock");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ծȨ����
int FUNCTION_CALL_MODE F2615227(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920017��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920017", "jc_tbondproperty");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ծȯ��Ϣ˰��Ϣ
int FUNCTION_CALL_MODE F2615228(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920018��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920018", "jc_tbonddetailproperty");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ڻ���Ϣ
int FUNCTION_CALL_MODE F2615229(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920019��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920019", "jc_tfuturesinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��Ȩ��Ϣ
int FUNCTION_CALL_MODE F2615230(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920020��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920020", "jc_toptionproperty");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ETF��Ϣ
int FUNCTION_CALL_MODE F2615231(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920021��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920021", "jc_tetfbasicinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ETF֤ȯ
int FUNCTION_CALL_MODE F2615232(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920022��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920022", "jc_tetfstocklistinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ع�����
int FUNCTION_CALL_MODE F2615233(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920023��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920023", "jc_thgratio");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ڻ���֤�����
int FUNCTION_CALL_MODE F2615237(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920027��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920027", "jc_tfuturedepositratio");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��Ȩ��֤��
int FUNCTION_CALL_MODE F2615238(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920028��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920028", "jc_toptiondepositset");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��������Ϣ
int FUNCTION_CALL_MODE F2615240(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920030��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920030", "jc_tissuer");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//���׶�����Ϣ
int FUNCTION_CALL_MODE F2615242(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920032��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920032", "jc_ttraderival");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��˾��Ϣ
int FUNCTION_CALL_MODE F2615244(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920034��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920034", "jc_tcompany");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//������ȯ���ȯ
int FUNCTION_CALL_MODE F2615251(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920041��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920041", "jc_trzrqstock");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}



//����׷�����
int FUNCTION_CALL_MODE F2615263(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920053��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920053", "jc_ttradefeeconfighs");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}



//������Ϣ
int FUNCTION_CALL_MODE F2615266(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920056��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920056", "jc_tdept");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//������ȯ֤ȯ����
int FUNCTION_CALL_MODE F2615267(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920057��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920057", "jc_trzrqstockset");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//Ӫҵ����չ����
int FUNCTION_CALL_MODE F2615272(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920062��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920062", "jc_tsecuritiesbranchex");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ծȯ��Ϣ��Ϣ
int FUNCTION_CALL_MODE F2615273(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920063��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920063", "jc_tbondrate");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ڻ���������
int FUNCTION_CALL_MODE F2615275(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920065��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920065", "jc_tfuturearbitrageinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//ϵͳ����ֵ
int FUNCTION_CALL_MODE F2615276(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920066��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920066", "jc_tsysparamvalue");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��˾��Ϊ
int FUNCTION_CALL_MODE F2615278(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920068��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920068", "jc_tcorpactioninfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//������ȯ����
int FUNCTION_CALL_MODE F2615281(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920071��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920071", "jc_trzrqconfig");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//���ʱ�
int FUNCTION_CALL_MODE F2615283(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920073��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920073", "jc_tcurrencyrate");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//���ʲ���
int FUNCTION_CALL_MODE F2615284(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920074��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920074", "jc_tinterestrate");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��֤LOF����ҵ�����
int FUNCTION_CALL_MODE F2615291(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920081��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920081", "jc_tloffundparam");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//������Ϣ
int FUNCTION_CALL_MODE F2615294(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920084��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920084", "jc_tbankinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ڻ�Ʒ��
int FUNCTION_CALL_MODE F2615295(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920085��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920085", "jc_tfuturekind");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��С���
int FUNCTION_CALL_MODE F2615296(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920086��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920086", "jc_tpriceinterval");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//Ӫҵ���ʽ��˻���Ϣ
int FUNCTION_CALL_MODE F2615297(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920087��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920087", "jc_tbranchcaptacctinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�˻�����
int FUNCTION_CALL_MODE F2615299(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920089��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920089", "jc_taccountgroup");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�˻������Ӧ�������
int FUNCTION_CALL_MODE F2615300(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920090��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920090", "jc_tgroupfundcombi");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//����Ա�˻���������Ȩ��
int FUNCTION_CALL_MODE F2615301(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920091��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920091", "jc_topacctgrouptyperight");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//����������
int FUNCTION_CALL_MODE F2615304(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920094��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920094", "jc_tfeesetproperty");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//���׷Ѱ����ķ������÷����ױ�
int FUNCTION_CALL_MODE F2615305(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920095��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920095", "jc_tcontainfeeset");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}


//����Ա״̬��Ϣ
int FUNCTION_CALL_MODE F2615313(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920103��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920103", "jc_toperatorstatus");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}


//TA�ӿ����ݴ���ģ��
int FUNCTION_CALL_MODE F2615317(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920107��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920107", "jc_ttadealconfig");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ڻ���Ʒ���������
int FUNCTION_CALL_MODE F2615318(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920122��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920122", "jc_tfuturekindarbitragecombi");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//֤ȯ�Զ������
int FUNCTION_CALL_MODE F2615319(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920123��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920123", "jc_tcustomclass");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�Զ������
int FUNCTION_CALL_MODE F2615320(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920124��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920124", "jc_tcustomdictionary");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//����ҵ������
int FUNCTION_CALL_MODE F2615321(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920125��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920125", "jc_tbusinessspecial");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//Ͷ�ʻ�����Ϣ
int FUNCTION_CALL_MODE F2615325(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920129��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920129", "jc_tinvestfundinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//֤ȯ������Ϣ
int FUNCTION_CALL_MODE F2615323(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920131��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920131", "jc_tstockissueinfo");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//�ⲿ����������Ϣ
int FUNCTION_CALL_MODE F2615324(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.extjc.920137��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.extjc.920137", "jc_torganization");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
  return 0;
}

//�ڻ�������Ϣ
int FUNCTION_CALL_MODE F2615264(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920054��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920054", "jc_tfeeqh");
//	CRjMsg *RjMsg2 = new CRjMsg(lpContext,  "fund.jc.920054", "jc_tfeedetailqh");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
//	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg2);
		
    return 0;
}

//���������Ϣ
int FUNCTION_CALL_MODE F2615261(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920051��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920051", "jc_tfeehs");
//	CRjMsg *RjMsg2 = new CRjMsg(lpContext,  "fund.jc.920051", "jc_tfeedetailhs");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
//	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg2);
		
    return 0;
}

//����Ȩ������
int FUNCTION_CALL_MODE F2615316(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920100��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920100", "uft_tautoriskpermission");
//	CRjMsg *RjMsg2 = new CRjMsg(lpContext, "fund.jc.920100", "uft_tautoriskparam");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
//	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg2);
			
    return 0;
}

//�ʽ��˻�
int FUNCTION_CALL_MODE F2615214(IAS2Context* lpContext, IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker)
{
    DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920004��");
	
	CRjMsg *RjMsg = new CRjMsg(lpContext,  "fund.jc.920004", "jc_tcapitalaccount");
	
	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);
		
    return 0;
}

//��ֵ��Ŀ����
int FUNCTION_CALL_MODE F2615326(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920147��");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920147", "jc_tfasubjectdefine");

	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//ϵͳ��Ŀ����
int FUNCTION_CALL_MODE F2615327(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920148��");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920148", "jc_tsubjectdefine");

	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//��Ʒ��Ŀ�̶�����
int FUNCTION_CALL_MODE F2615328(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920149��");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920149", "jc_tfundsubjectcount");

	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//��ֵ֤ȯ����ת������ģ��
int FUNCTION_CALL_MODE F2615329(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920150��");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920150", "jc_tfachangemethod");

	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//��ֵ֤ȯ����ת����ϸ
int FUNCTION_CALL_MODE F2615330(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920151��");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920004", "jc_tfachangedetail");

	// ���������ռ���Ϣ������������
	CRjMsgMgr::GetInstance().AddRjMsg(RjMsg);

	return 0;
}

//��ֵ�г�����ת����Ϣ
int FUNCTION_CALL_MODE F2615331(IAS2Context* lpContext,
		IF2UnPacker * lpInUnPacker, IF2Packer * lpOutPacker) {
	DLOGEVENT(lpContext, "�յ��ռ���Ϣ����������fund.jc.920152��");

	CRjMsg *RjMsg = new CRjMsg(lpContext, "fund.jc.920004", "jc_tfachangemarket");

	// ���������ռ���Ϣ������������
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
                ppv->Caption = "AS_�ռ�����ͬ��_�˻���Ϣ";
            }
            break;
		case 1:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615212;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615212;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_�ռ�����ͬ��_�ʲ���Ԫ";
            }
            break;
		case 2:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615213;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615213;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_�ռ�����ͬ��_�����Ϣ";
            }
            break;
		case 3:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615215;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615215;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_�ռ�����ͬ��_�ɶ���Ϣ";
            }
            break;
		case 4:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615216;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615216;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_�ռ�����ͬ��_�ɶ����˻���ϵ";
            }
            break;
		case 5:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615217;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615217;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_�ռ�����ͬ��_ϯλ��Ϣ";
            }
            break;
		case 6:
            if (ppv != NULL)
            {
                ppv->dwFunctionNo = 2615218;
                ppv->iVersion = 20170331;
                ppv->ReqProc = F2615218;
                ppv->AnsProc = NULL;
                ppv->Caption = "AS_�ռ�����ͬ��_ϯλ���˻���Ϣ";
            }
            break;
		case 7:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615220;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615220;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_������";
			}
			break;
		case 8:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615221;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615221;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_����Ա";
			}
			break;
		case 9:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615222;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615222;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�˻�Ȩ��";
			}
			break;
		case 10:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615223;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615223;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ȯ����Ϣ";
			}
			break;
		case 11:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615224;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615224;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_Ӫҵ����Ϣ";
			}
			break;
		case 12:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615225;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615225;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�г���Ϣ";
			}
			break;
		case 13:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615226;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615226;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_֤ȯ��Ϣ";
			}
			break;
		case 14:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615227;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615227;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ծȯ����";
			}
			break;
		case 15:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615228;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615228;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ծȯ��Ϣ˰��Ϣ";
			}
			break;
		case 16:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615229;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615229;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ڻ���Ϣ";
			}
			break;
		case 17:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615230;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615230;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��Ȩ����";
			}
			break;
		case 18:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615231;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615231;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ETF��Ϣ";
			}
			break;
		case 19:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615232;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615232;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ETF֤ȯ";
			}
			break;
		case 20:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615233;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615233;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ع�����";
			}
			break;
		case 21:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615237;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615237;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ڻ���֤�����";
			}
			break;
		case 22:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615238;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615238;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��Ȩ��֤��";
			}
			break;
		case 23:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615240;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615240;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_������";
			}
			break;
		case 24:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615242;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615242;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_���׶�����Ϣ";
			}
			break;
		case 25:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615244;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615244;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��˾��Ϣ";
			}
			break;
		case 26:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615251;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615251;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_������ȯ���ȯ";
			}
			break;
		case 27:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615263;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615263;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_����׷�����";
			}
			break;
		case 28:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615266;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615266;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_������Ϣ";
			}
			break;
		case 29:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615267;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615267;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_������ȯ֤ȯ����";
			}
			break;
		case 30:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615272;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615272;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_Ӫҵ����չ����";
			}
			break;
		case 31:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615273;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615273;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ծȯ��Ϣ��Ϣ";
			}
			break;
		case 32:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615275;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615275;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ڻ���������";
			}
			break;
		case 33:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615276;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615276;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ϵͳ����ֵ";
			}
			break;
		case 34:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615278;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615278;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��˾��Ϊ";
			}
			break;
		case 35:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615281;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615281;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_������ȯ������Ϣ";
			}
			break;
		case 36:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615283;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615283;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_���ʱ�";
			}
			break;
		case 37:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615284;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615284;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_���ʲ���";
			}
			break;
		case 38:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615291;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615291;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��֤LOF����ҵ�����";
			}
			break;
		case 39:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615294;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615294;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_������Ϣ";
			}
			break;
		case 40:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615295;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615295;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ڻ�Ʒ��";
			}
			break;
		case 41:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615296;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615296;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��С���";
			}
			break;
		case 42:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615297;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615297;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_Ӫҵ���ʽ��˺���Ϣ";
			}
			break;
		case 43:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615299;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615299;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�˻�����";
			}
			break;
		case 44:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615300;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615300;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�˻������Ӧ�������";
			}
			break;
		case 45:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615301;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615301;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_����Ա�˻���������Ȩ��";
			}
			break;
		case 46:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615304;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615304;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_���������Ա�";
			}
			break;
		case 47:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615305;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615305;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_���׷Ѱ����ķ������÷����ױ�";
			}
			break;
		case 48:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615313;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615313;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_����Ա״̬��Ϣ";
			}
			break;
		case 49:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615317;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615317;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_TA�ӿ����ݴ���ģ��";
			}
			break;
		case 50:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615318;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615318;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ڻ���Ʒ���������";
			}
			break;
		case 51:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615319;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615319;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_֤ȯ�Զ������";
			}
			break;
		case 52:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615320;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615320;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�Զ������";
			}
			break;
		case 53:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615325;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615325;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_Ͷ�ʻ�����Ϣ";
			}
			break;
		case 54:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615321;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615321;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_����ҵ������";
			}
			break;
		case 55:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615323;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615323;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_֤ȯ������Ϣ";
			}
			break;
		case 56:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615324;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615324;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ⲿ����������Ϣ";
			}
			break;
		case 57:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615264;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615264;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_feeqh";
			}
			break;
		case 58:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615261;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615261;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_feehs";
			}
			break;
		case 59:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615316;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615316;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_����Ȩ������";
			}
			break;
		case 60:
			if (ppv != NULL)
			{
				ppv->dwFunctionNo = 2615214;
				ppv->iVersion = 20170331;
				ppv->ReqProc = F2615214;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_�ʽ��˻�";
			}
			break;
		case 61:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615326;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615215;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��ֵ��Ŀ����";
			}
			break;
		case 62:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615327;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615327;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_ϵͳ��Ŀ����";
			}
			break;
		case 63:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615328;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615328;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��Ʒ��Ŀ�̶�����";
			}
			break;
		case 64:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615329;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615329;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��ֵ֤ȯ����ת������ģ��";
			}
			break;
		case 65:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615330;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615330;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��ֵ֤ȯ����ת����ϸ";
			}
			break;
		case 66:
			if (ppv != NULL) {
				ppv->dwFunctionNo = 2615331;
				ppv->iVersion = 20170608;
				ppv->ReqProc = F2615331;
				ppv->AnsProc = NULL;
				ppv->Caption = "AS_�ռ�����ͬ��_��ֵ�г�����ת����Ϣ";
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


