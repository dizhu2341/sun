#ifndef jc_figher_h
#define jc_figher_h


/*******************************************************************************
 * 功能：新增指纹数据
 * 参数：同服务入口参数。
*******************************************************************************/
extern int InsertFingerImage(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);


/*******************************************************************************
 * 功能：更新指纹数据
 * 参数：同服务入口参数。
*******************************************************************************/
extern int UpdateFingerImage(IAS2Context* lpContext,IF2UnPacker * lpInUnPacker,IF2Packer * lpOutPacker);

#endif
