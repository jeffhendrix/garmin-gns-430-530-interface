#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "remoteProxy.h"
#include "udpsocketthread.h"
#include "udpsocket.h"
#include "log.h"
#include "config.h"


#define TRAINER_PORT  5000
#define PROXY_PORT    (TRAINER_PORT+1)

void UdpDataCallback(void* pData, int dataSize, void* context)
{
    RemoteProxy* pRemoteProxy = (RemoteProxy*)context;
    pRemoteProxy->processUdpData(pData, dataSize);
}

RemoteProxy::RemoteProxy()
{
	m_win = NULL;

    m_pServerSocketThread = NULL;
    m_pClientSocket = NULL;

    //Default frquencies
    m_comActive = 134100;
    m_comStandby = 130825;
    m_navActive = 108700;
    m_navStandby = 111450;

    m_state = stateTerminated;
}

RemoteProxy::~RemoteProxy()
{
    if(stateOpened == m_state)
    {
        close();
    }

    if(stateInitialized == m_state)
    {
        terminate();
    }
}

bool RemoteProxy::initialize(bool hideGUI)
{
	bool res = true;

    if(stateTerminated != m_state)
    {
        res = false;
        return res;
    }
	
	m_win = NULL; 

    m_hideGUI = hideGUI;

    //find the trainer path and copy the G530SIM.exe to the appropriate executable
	{
		HKEY hKey;
		DWORD dwSize = MAX_PATH;
		DWORD dwType;
		LONG lResult;
		WIN32_FIND_DATA FileData; 
		HANDLE hSearch; 
		//DWORD dwAttrs;   
		char szG530SIMFileName[MAX_PATH];   

		char trainerpath[MAX_PATH];   

		lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
					G530SIMEXE_PATH, 0, KEY_READ, &hKey);

		if(ERROR_SUCCESS != lResult)
		{
            logMessageEx("??? RemoteProxy::Initialize Error opening key " G530SIMEXE_PATH);
			res = false;
			return res;
		}

		lResult = RegQueryValueEx(hKey, "Path", 0, &dwType,  (LPBYTE)trainerpath, &dwSize);
		RegCloseKey(hKey);

		if(ERROR_SUCCESS != lResult)
		{
            logMessageEx("??? RemoteProxy::Initialize Error reading key " G530SIMEXE_PATH);

			res = false;
			return res;
		}

		strcpy(m_trainter_path, trainerpath);
		strcat(m_trainter_path, "\\Trainer");
		strcpy(m_trainter_exe, m_trainter_path);
		strcat(m_trainter_exe, "\\gnsx30.exe");
		
      strcpy(m_interface_lib, m_trainter_path);
      strcat(m_interface_lib, "\\gnsInterface.dll");

		//Check if the file gns530 already exists
		
		hSearch = FindFirstFile(m_trainter_exe, &FileData); 

	   if (hSearch == INVALID_HANDLE_VALUE) 
	   { 
			strcpy(szG530SIMFileName, m_trainter_path);
			strcat(szG530SIMFileName, "\\G530SIM.exe");
		   if(!CopyFile(szG530SIMFileName,m_trainter_exe,FALSE))
		   {
               logMessageEx("??? RemoteProxy::Initialize Error copying file %s", szG530SIMFileName);

			   res = false;
			   return res;
		   }
	   }

    }////find the trainer path and copy the G530SIM.exe to the appropriate executable

	//Create the registry keys for the trainer
	{
      HKEY hKey;
//    DWORD dwSize = MAX_PATH;
      DWORD dwValue;
      DWORD dwValue1;
		DWORD dwDisposition;

      if (ERROR_SUCCESS!= RegCreateKeyEx(HKEY_CURRENT_USER, GARMIN_INTERNATIONAL, 0, NULL,
            REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,&dwDisposition)
         )
      {
         logMessageEx("??? RemoteProxy::Initialize Error creating key " GARMIN_INTERNATIONAL);

         res = false;
         return res;
      }

		if (ERROR_SUCCESS!= RegCreateKeyEx(HKEY_CURRENT_USER, GARMIN_INTERNATIONAL_SETTINGS, 0, NULL, 
							REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,&dwDisposition)
			)
		{
            logMessageEx("??? RemoteProxy::Initialize Error creating key " GARMIN_INTERNATIONAL_SETTINGS);

            res = false;
            return res;
		}

		//Create the trainer settings values
      if (ERROR_SUCCESS != RegSetValueEx(hKey, "CDUType", 0, REG_SZ, (LPBYTE)GNS_530AWT, strlen(GNS_530AWT) + 1))
      {
         logMessageEx("??? RemoteProxy::Initialize Error writing key CDUType");

         res = false;
         return res;
      }

      RegFlushKey(hKey);
      RegCloseKey(hKey);

      if (ERROR_SUCCESS!= RegCreateKeyEx(HKEY_CURRENT_USER, GARMIN_INTERNATIONAL_WINDOW, 0, NULL,
            REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,&dwDisposition)
         )
      {
         logMessageEx("??? RemoteProxy::Initialize Error creating key " GARMIN_INTERNATIONAL_WINDOW);

         res = false;
         return res;
      }

      dwValue = 50;

      if(m_hideGUI)
      {
         dwValue = 10000;
      }
      //Create the window position values
      if (ERROR_SUCCESS != RegSetValueEx(hKey, "x1", 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(dwValue)))
      {
         logMessageEx("??? RemoteProxy::Initialize Error writing key " GARMIN_INTERNATIONAL_WINDOW);

         res = false;
         return res;
      }

      if (ERROR_SUCCESS != RegSetValueEx(hKey, "y1", 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(dwValue)))
      {
         logMessageEx("??? RemoteProxy::Initialize Error writing key " GARMIN_INTERNATIONAL_WINDOW);
         res = false;
         return res;
      }

      dwValue1 = dwValue + 480;
      if (ERROR_SUCCESS != RegSetValueEx(hKey, "x2", 0, REG_DWORD, (LPBYTE)&dwValue1, sizeof(dwValue1)))
      {
         logMessageEx("??? RemoteProxy::Initialize Error writing key " GARMIN_INTERNATIONAL_WINDOW);
         res = false;
         return res;
      }
      dwValue1 = dwValue + 630;
		if (ERROR_SUCCESS != RegSetValueEx(hKey, "y2", 0, REG_DWORD, (LPBYTE)&dwValue1, sizeof(dwValue1)))
		{
            logMessageEx("??? RemoteProxy::Initialize Error writing key " GARMIN_INTERNATIONAL_WINDOW);
            res = false;
            return res;
		}
		RegFlushKey(hKey);
		RegCloseKey(hKey);
	}

	//Create the shared data structure
    m_pShared = new SharedStruct<GNSIntf>(SHMEM_NAME, true, 0);

	m_pvData = m_pShared->get();

	memset(m_pvData->LCD_data,0x00, OFFSCREEN_BUFFER_WIDTH*OFFSCREEN_BUFFER_HEIGHT*4);
    memset(m_pvData->Bezel_data,0x00, OFFSCREEN_BUFFER_WIDTH*OFFSCREEN_BUFFER_HEIGHT*4);

    m_state = stateInitialized;

	return res;
}

bool RemoteProxy::terminate()
{
	bool res = true;

    if(stateInitialized != m_state)
    {
        res = false;
        return res;
    }

	delete 	m_pShared; 
    m_pvData = NULL;
    
    m_state = stateTerminated;

	return res;
}

bool RemoteProxy::open(int gnsType)
{
	bool res = true;
    char dest_address[] = "127.0.0.1";

    if(stateInitialized != m_state)
    {
        return false;
    }

    HKEY hKey;
    DWORD dwDisposition;

    //Default frquencies
    m_comActive = 123000;
    m_comStandby = 130825;
    m_navActive = 108700;
    m_navStandby = 111450;

    m_pvData->gnsType = gnsType;

    m_pvData->garminTrainerPort = TRAINER_PORT;
    m_pvData->proxyPort = PROXY_PORT;

    //Start the serverThread
    m_pServerSocketThread = new UdpSocketThread(m_pvData->proxyPort);
    m_pServerSocketThread->create();
    m_pServerSocketThread->setCallback(UdpDataCallback, this);
    m_pServerSocketThread->resume();

    m_pClientSocket  = new UdpSocket();
    m_pClientSocket->openForSending(dest_address, m_pvData->garminTrainerPort); //||| enter socket

    if (ERROR_SUCCESS!= RegCreateKeyEx(HKEY_CURRENT_USER, GARMIN_INTERNATIONAL_SETTINGS, 0, NULL, 
        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,&dwDisposition)
        )
    {
        logMessageEx("??? RemoteProxy::open Error creating key " GARMIN_INTERNATIONAL_SETTINGS);

        res = false;
        return res;
    }

    if(TYPE_GNS430 == gnsType)
    {
        //Create the trainer settings values
        if (ERROR_SUCCESS != RegSetValueEx(hKey, "CDUType", 0, REG_SZ, (LPBYTE)GNS_430AWT, strlen(GNS_430AWT) + 1))
        {
            logMessageEx("??? RemoteProxy::open Error writing key CDUType");

            res = false;
            return res;
        }
    }else if(TYPE_GNS530 == gnsType)
    {
        //Create the trainer settings values
        if (ERROR_SUCCESS != RegSetValueEx(hKey, "CDUType", 0, REG_SZ, (LPBYTE)GNS_530AWT, strlen(GNS_530AWT) + 1))
        {
            logMessageEx("??? RemoteProxy::open Error writing key CDUType");

            res = false;
            return res;
        }
    }

    RegFlushKey(hKey);
    RegCloseKey(hKey);

	memset(m_pvData->LCD_data,0x00, OFFSCREEN_BUFFER_WIDTH*OFFSCREEN_BUFFER_HEIGHT*4);

	int count = 0;
	bool procesStarted = false;
	while(count < 20) // 10 sec
	{
		m_win = FindWindow("AfxFrameOrView42", "GARMIN 400W/500W Trainer");
		if(NULL != m_win)
		{
			procesStarted = true;
			break;
		}
		Sleep(500);
		count++;
	}

	if(!procesStarted)
	{
        logMessageEx("??? RemoteProxy::Open Error starting process %s", m_trainter_exe);
		res = false;
		return res;
	}

    m_state = stateOpened;

	return res;
}

bool RemoteProxy::close()
{
	bool res = true;
	LRESULT r;

    if(stateOpened != m_state)
    {
        res = false;
        return res;
    }

	//Find the window handle and close the window
    if(NULL == 	m_win)	
    {
    	m_win = FindWindow("AfxFrameOrView42", "GARMIN 400W/500W Trainer");
    }
	//r = SendMessage(win, WM_QUIT, 0,0);      
	if(NULL != m_win)
	{
		r = PostMessage(m_win, WM_QUIT, 0,0);      
    }else
	{
        logMessageEx("??? RemoteProxy::Close Error finding window %s:%s" "AfxFrameOrView42", "GARMIN 400W/500W Trainer");
	}

	m_win = NULL;

    m_pServerSocketThread->terminate();
    delete m_pServerSocketThread;
    m_pServerSocketThread = NULL;

    delete m_pClientSocket;
    m_pClientSocket = NULL;
    
    m_state = stateInitialized;

	return res;
}

GNSIntf* RemoteProxy::getInterface()
{
	return m_pvData;
}

int RemoteProxy::sendMsg(int up, int x, int y )
{	
	int res = 0;
	
	DWORD lParam;

    if(NULL == 	m_win)	
    {
        m_win = FindWindow("AfxFrameOrView42", "GARMIN 400W/500W Trainer");
    }

	if(NULL != m_win)
	{
	
		lParam = y;
		lParam<<=16;
		lParam|=x;
		if(up)
		{
			PostMessage(m_win, WM_LBUTTONUP, MK_LBUTTON,lParam);  	
		}else
		{
			PostMessage(m_win, WM_LBUTTONDOWN, MK_LBUTTON,lParam);  	
		}
	}

	return res;
}

void RemoteProxy::processUdpData(void* pData, int dataSize)
{
    if(dataSize >0)
    {
        unsigned char msgType = ((unsigned char*)pData)[0];
        switch(msgType)
        {
            case MSG_COM_ACTIVE:
            {
                FreqInfo* pFreqInfo = (FreqInfo*)pData;
                m_comActive = pFreqInfo->freq;
                //logMessageEx("--- RemoteProxy::processUdpData m_comActive %d", m_comActive);
                break;
            }
            case MSG_COM_STANDBY:
            {
                FreqInfo* pFreqInfo = (FreqInfo*)pData;
                m_comStandby = pFreqInfo->freq;

                //logMessageEx("--- RemoteProxy::processUdpData m_comStandby %d", m_comStandby);

                break;
            }
            case MSG_NAV_ACTIVE:
            {
                FreqInfo* pFreqInfo = (FreqInfo*)pData;
                m_navActive = pFreqInfo->freq;
                //logMessageEx("--- RemoteProxy::processUdpData m_navActive %d", m_comActive);
                break;
            }
            case MSG_NAV_STANDBY:
            {
                FreqInfo* pFreqInfo = (FreqInfo*)pData;
                m_navStandby = pFreqInfo->freq;

                //logMessageEx("--- RemoteProxy::processUdpData m_navStandby %d", m_comStandby);

                break;
            }
        }
    }
}

//COM functions
void  RemoteProxy::setCOMActiveFrequency(unsigned long freq)
{
    FreqInfo msg;

    msg.msgType = MSG_COM_ACTIVE;
    msg.freq = freq;

    m_pClientSocket->send((char*)&msg, sizeof(msg));
}

void  RemoteProxy::setCOMStandbyFrequency(unsigned long freq)
{
    FreqInfo msg;

    msg.msgType = MSG_COM_STANDBY;
    msg.freq = freq;

    m_pClientSocket->send((char*)&msg, sizeof(msg));
}

//NAV functions
void  RemoteProxy::setNAVActiveFrequency(unsigned long freq)
{
    FreqInfo msg;

    msg.msgType = MSG_NAV_ACTIVE;
    msg.freq = freq;

    m_pClientSocket->send((char*)&msg, sizeof(msg));
}

void  RemoteProxy::setNAVStandbyFrequency(unsigned long freq)
{
    FreqInfo msg;

    msg.msgType = MSG_NAV_STANDBY;
    msg.freq = freq;

    m_pClientSocket->send((char*)&msg, sizeof(msg));
}

void  RemoteProxy::setGPSInfo(double latitude, double longitude, float speed, float	heading, float verticalSpeed, float altitude)
{
    GPSInfo msg;

    msg.msgType = MSG_GPS_INFO;
    msg.latitude = latitude;
    msg.longitude = longitude;
    msg.speed = speed;
    msg.heading = heading;
    msg.verticalSpeed = verticalSpeed;
    msg.altitude = altitude;

    m_pClientSocket->send((char*)&msg, sizeof(msg));
}
