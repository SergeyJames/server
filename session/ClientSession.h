#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include "../network/include/NetWorkObject.h"
#include "../include/baseHeader.h"
#include "../include/PackageHandler.hpp"
#include "../include/packHeader.hpp"
#include "../include/packageStruct.hpp"
#include "../include/acctTimeTool.hpp"


class ClientSession : public NetWorkObject
{
    public:
        ClientSession();
        virtual ~ClientSession();
        int32 onRecv(PkgHeader *header, char *msgbuf, int32 buffsize);
        int32 onRecv(PkgHeader *header, MsgHeader *msghead, char *msgbuf, int32 buffsize);
        int32 processSend(uint16 sysid, uint16 msgid, char *msg, int32 msgsize);
        int32 testRefectSvr(char *msgbuf, int32 bufsize);
        int32 testRefectSvr(MsgHeader *msghead, char *msgbuf, int32 bufsize);
    protected:
    private:
        uint64 m_llpkgCount;
        int32 m_nStatistic;
        int32 m_nNextTick;
};

#endif // CLIENTSESSION_H
