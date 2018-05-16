#include "Common.h"

//int ConnectToDB()
//{
//    EXEC SQL WHENEVER SQLERROR continue;
//    
//    //�����û��������������
//    EXEC SQL BEGIN DECLARE SECTION;
//    char sDBUser[50],sDBPasswd[50],sDBServer[10];
//    EXEC SQL END DECLARE SECTION;
//    
//    //����ORACLE��ʶ��
//    EXEC SQL DECLARE O3DB DATABASE;
//    EXEC SQL DECLARE JCDB DATABASE;
//    
//    //��ȡDB������Ϣ
//    const char sCfgFileName[32] = "o4basecfg.ini";
//    
//    //������O3���ݿ������
//    read_profile_string("SrcDB", "DBServer", sDBServer, 10, "", sCfgFileName);
//    read_profile_string("SrcDB", "DBUser", sDBUser, 50, "", sCfgFileName);
//    read_profile_string("SrcDB", "DBPasswd", sDBPasswd, 50, "", sCfgFileName);
//    
//    EXEC SQL CONNECT :sDBUser IDENTIFIED BY :sDBPasswd AT O3DB USING :sDBServer;
//    if (sqlca.sqlcode != 0)
//    {
//        printf("����O3���ݿ�ʧ�ܣ�%s", sqlca.sqlerrm.sqlerrmc);
//        LOGERROR(sqlca.sqlcode, "����O3���ݿ�ʧ�ܣ�"<<sqlca.sqlerrm.sqlerrmc);
//        return -1;
//    }
//    
//    //������O4���ݿ������
//    read_profile_string("DstDB", "DBServer", sDBServer, 10, "", sCfgFileName);
//    read_profile_string("DstDB", "DBUser", sDBUser, 50, "", sCfgFileName);
//    read_profile_string("DstDB", "DBPasswd", sDBPasswd, 50, "", sCfgFileName);
//    EXEC SQL CONNECT :sDBUser IDENTIFIED BY :sDBPasswd AT JCDB USING :sDBServer;
//    
//    if (sqlca.sqlcode != 0)
//    {
//        printf("����O4���ݿ�ʧ�ܣ�%s", sqlca.sqlerrm.sqlerrmc);
//        LOGERROR(sqlca.sqlcode, "����O4���ݿ�ʧ�ܣ�"<<sqlca.sqlerrm.sqlerrmc);
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
