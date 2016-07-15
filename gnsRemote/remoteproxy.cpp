#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "remoteproxy.h"
#include "udpsocketthread.h"
#include "udpsocket.h"


#define TRAINER_PORT  5000
#define PROXY_PORT    (TRAINER_PORT+1)


void UdpDataCallback(void* pData, int dataSize, void* context)
{

}

RemoteProxy::RemoteProxy()
{
    m_pServerSocketThread = NULL;
    m_pClientSocket = NULL;
}

bool RemoteProxy::open(char *dest_address)
{
    m_pvData->garminTrainerPort = TRAINER_PORT;
    m_pvData->proxyPort = PROXY_PORT;

    //Start the serverThread
    m_pServerSocketThread = new UdpSocketThread(m_pvData->proxyPort);
    m_pServerSocketThread->create();
    m_pServerSocketThread->setCallback(UdpDataCallback, this);
    m_pServerSocketThread->resume();

    m_pClientSocket  = new UdpSocket();
    m_pClientSocket->openForSending(dest_address, m_pvData->garminTrainerPort); //||| enter socket

    return true;
}
