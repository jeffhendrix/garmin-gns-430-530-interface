#ifndef REMOTEPROXY_H
#define REMOTEPROXY_H

//#include "sharedstruct.h"
#include "gnsTypes.h"

class UdpSocketThread;
class UdpSocket;

class RemoteProxy
{
public:
    RemoteProxy();
    bool open(char *dest_address);
    bool terminate();
    bool close();

private:
    GNSIntf*				m_pvData;

    UdpSocketThread*        m_pServerSocketThread; //This socket thread will receive data form the Garming Sim
    UdpSocket*              m_pClientSocket; //This socket thread will send data to the Garming Sim

};

#endif // REMOTEPROXY_H
