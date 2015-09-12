#include "../include/CDBSHandlerFunc.hpp"

int32 CDBSHandlerFunc::testfunc(CSession *session, char *pMsg, int32 msglen)
{
    test_package::testMsg recvmsg;
    recvmsg.ParseFromArray(pMsg, msglen);
    LOGFMTI("protocol==sendtime:%d====server recv:%s\n", recvmsg.sendtime(), recvmsg.msg().c_str());
    return session->getNetWorkObject()->processSend(1, 4, pMsg, msglen);
}

int32 CDBSHandlerFunc::checkuser(CSession *session, char *pMsg, int32 msglen)
{
    test_package::acc_2_dbs_checkuser recvmsg;
    recvmsg.ParseFromArray(pMsg, msglen);
    CSqlConn *sqlInst = DBSvr::GetInstance()->getDBInstFactory()->allocate();
    std::string sql = "select a, b from tbl where a ='";
    sql.append(recvmsg.name());
    sql.append("', and b = '");
    sql.append(recvmsg.passwd());
    sql.append("'");
    CQuery query(sqlInst, sql, sql.length());
    CResult res;
    int32 retcode = 1;
    if (query.exequery(&res))
    {
        while (res.hasNext())
        {
            char *name = res.getString(0);
            char *passwd = res.getString(1);
            printf("db query result name:%s, passwd:%s\n", name, passwd);
            retcode = 0;
            break;
        }
    }
    //LOGFMTI("protocol==sendtime:%d====server recv:%s\n", recvmsg.sendtime(), recvmsg.msg().c_str());

    test_package::dbs_2_acc_checkuser sendmsg;
    sendmsg.set_retcode(retcode);

    int32 sendlen = sendmsg.ByteSize();
    char pmsg[sendlen];
    sendmsg.SerializeToArray(pmsg, sendlen);

    return session->getNetWorkObject()->processSend((uint16)eServerMessage_DBServer, (uint16)DBS_ACCS_CHECKLOGINUSER_RET, pmsg, sendlen);
}
