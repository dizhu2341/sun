#include "Common.h"

//int ConnectToDB()
//{
//    EXEC SQL WHENEVER SQLERROR continue;
//    
//    //声明用户名、口令、服务名
//    EXEC SQL BEGIN DECLARE SECTION;
//    char sDBUser[50],sDBPasswd[50],sDBServer[10];
//    EXEC SQL END DECLARE SECTION;
//    
//    //声明ORACLE标识符
//    EXEC SQL DECLARE O3DB DATABASE;
//    EXEC SQL DECLARE JCDB DATABASE;
//    
//    //获取DB配置信息
//    const char sCfgFileName[32] = "o4basecfg.ini";
//    
//    //建立到O3数据库的连接
//    read_profile_string("SrcDB", "DBServer", sDBServer, 10, "", sCfgFileName);
//    read_profile_string("SrcDB", "DBUser", sDBUser, 50, "", sCfgFileName);
//    read_profile_string("SrcDB", "DBPasswd", sDBPasswd, 50, "", sCfgFileName);
//    
//    EXEC SQL CONNECT :sDBUser IDENTIFIED BY :sDBPasswd AT O3DB USING :sDBServer;
//    if (sqlca.sqlcode != 0)
//    {
//        printf("连接O3数据库失败：%s", sqlca.sqlerrm.sqlerrmc);
//        LOGERROR(sqlca.sqlcode, "连接O3数据库失败："<<sqlca.sqlerrm.sqlerrmc);
//        return -1;
//    }
//    
//    //建立到O4数据库的连接
//    read_profile_string("DstDB", "DBServer", sDBServer, 10, "", sCfgFileName);
//    read_profile_string("DstDB", "DBUser", sDBUser, 50, "", sCfgFileName);
//    read_profile_string("DstDB", "DBPasswd", sDBPasswd, 50, "", sCfgFileName);
//    EXEC SQL CONNECT :sDBUser IDENTIFIED BY :sDBPasswd AT JCDB USING :sDBServer;
//    
//    if (sqlca.sqlcode != 0)
//    {
//        printf("连接O4数据库失败：%s", sqlca.sqlerrm.sqlerrmc);
//        LOGERROR(sqlca.sqlcode, "连接O4数据库失败："<<sqlca.sqlerrm.sqlerrmc);
//        return -1;
//    }
//    return 0;
//}

int PackAnswerPackage(IF2Packer* lpOutPacker, int nErrorNo, char* sErrorInfo, char* sErrorPathInfo)
{
    lpOutPacker->AddField("error_no");
    lpOutPacker->AddField("error_info");
    if (nErrorNo != 0)
    {
        lpOutPacker->AddField("error_pathinfo");
    }

    lpOutPacker->AddInt(nErrorNo);
    lpOutPacker->AddStr(sErrorInfo);

    if (nErrorNo != 0)
    {
        lpOutPacker->AddStr(sErrorPathInfo);
    }

    return nErrorNo;
}
