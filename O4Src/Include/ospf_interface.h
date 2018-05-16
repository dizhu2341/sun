///金融基础件2.0OSPF模块接口定义 
/*******************************************************
  源程序名:	ospf_interface.h
  软件版权: 恒生电子股份有限公司
  系统名称: 金融基础件2.0
  模块名称: OSPF模块
  功能说明: 定义一个OSPF库
            1、提供下跳路由计算
            2、收集提供拓扑图信息
  作    者: 研发中心
  开发日期: 20080103
  备    注: 

  修改人员：
  修改日期：
  修改说明：
*********************************************************/

#ifndef __OSPF_INTERFACE_H__
#define __OSPF_INTERFACE_H__

#include <Include/service_interface.h>
#include <Include/glbdef.h>

/// 管理接口定义
//@{
/// OSPF模块管理信息(共用部分可能需要统一定义)
#define GET_FUNCTION_ID			0
#define GET_TOPO				1				// 获取拓扑图
#define GET_ARID				3				// 返回AR名字
#define PRINT_AVL_TREE			4				// 在文件里输出AVL树

/// 获取内部运行状态
#define GET_NBR_NUM				5				// 邻居队列长度
#define GET_LSA_DB_NUM			6				// LSA数据库维护条目
#define GET_RETRANS_NUM			7				// 重发队列的长度(包括LSA、LSR)
#define GET_FLOOD_TIMES			8				// 获取泛洪次数
#define REV_PACKETS				9				// 接收到的包的个数
#define SEND_PACKETS			10				// 已发送包的个数
#define GET_AGING_LSA_NUM		11				// 获取已老化的LSA条数
#define GET_PROXY_NAME			12				// 获取OSPF代理的客户端名字以及已经启动的客户端
#define GET_NBR					14				// 获取邻居名以及类型
#define GET_AGE_BINS			15				// 获取年龄箱的信息
#define GET_HISTORY_INFO		16				// 获取历史动作信息, 只有配置history=1才有效
#define GET_MSG_LIST_INFO		17
//@}


typedef struct tagDestAR
{
	char			szARName[IDENTITY_NAME_LENGTH + 1];		// AR组名
	unsigned char	byFlag;									// Server/Client的标志。1：Client 2：Server
} DestAR;

/// OSPF调用接口，启动线程工作前最好组内同步好
/// 与Router之间的交互主要用IService提供的接口
struct IOspf : IMessageService
{
	/// 获取下一跳路径, lpDest第一个存放的地址为负载均衡最佳地址, 之后存放所有等价路径
	/** 参数:	@char*			lpARName			目标地址
	 *			@DestAR*		lpDest				决定的下跳地址
	 *			@uint16			*wPath				(in)lpDest提供的DestAR结构个数, (out)指下跳等价的所有地址
	 *	返回:	
	 */
	virtual void GetRoute(char *szName, DestAR *lpDest, uint16 *wPath) = 0;

};


#ifdef __cplusplus
extern "C" { 
#endif

	///组件初始化
	/**
	 *@return int 版本号 yyyymmdd形式
	 */
	int  FUNCTION_CALL_MODE OSPFInit(void *lp, PFOnSetTimeOut);
	
	///取服务接口句柄
	/**
	 *@return void * 孤子模式
	 */
	IKnown * FUNCTION_CALL_MODE GetOSPFInstance(void);

	///取服务接口依赖服务
	/**
	 *@param iIndex 
	 *@return IKnown * 依赖服务标识 
	 */
	char * FUNCTION_CALL_MODE GetOSPFDependService(void *lp);
	
	///返回统一的AS基础服务组件查询接口 getxxxInfo()
	/**当基础服务组件动态加载时，通过本接口或以获取服务信息(包括xxxxInit(),getxxxxInterface()函数指针)
	 *@param void ** ppv    基础服务组件信息(输出参数)，
	 *@return 返回0表示查到所要的接口，否则返回负数
	 */
	int FUNCTION_CALL_MODE GetOSPFInfo(int iIndex, tagBaseServiceInfo * ppv);

#ifdef __cplusplus
}
#endif


#endif


