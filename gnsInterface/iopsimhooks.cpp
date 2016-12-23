#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "apihijack.h"
#include "hooks.h"
#include "iopsimhooks.h"
#include "log.h"

#define RAD2DEG (57.2957795f)

#define IOP_REGISTER3e8 (0x3e8) // 29
#define IOP_REGISTER3f8 (0x3f8) // 4
#define IOP_REGISTER412 (0x412) // 16
#define IOP_REGISTER413 (0x413) // 4 float altitude meters (auto pilot?)
#define IOP_REGISTER414 (0x414) // 1
#define IOP_REGISTER415 (0x415) // 4 (might be float) maybe obs from hsi
#define IOP_REGISTER416 (0x416) // 16
#define IOP_REGISTER417 (0x417) // 8 seen lots, looks like number (double) counting up
#define IOP_REGISTER418 (0x418) // 1
#define IOP_REGISTER419 (0x419) // 4 float speed meters/sec auto pilot
#define IOP_REGISTER422 (0x422) // 16
#define IOP_REGISTER7e9 (0x7e9) // 84
#define IOP_REGISTER7f0 (0x7f0) // 4  #define COM_ACTIVE_REGISTER (0x7f0)
#define IOP_REGISTER7f2 (0x7f2) // 4  #define NAV_ACTIVE_REGISTER (0x7f2)
// #define COM_STANDBY_REGISTER (0x7f4)
// #define NAV_STANDBY_REGISTER (0x7f6)
// #define COM_UNKNOWN_REGISTER (0x7e8) //size 1

#pragma pack(push, 1)

typedef struct _send_msg_ex_0x12
{
	unsigned long unknown1; // b,c,d,e
    unsigned short hfom;    // f,0
    unsigned short unknown2; // 1,2
    unsigned short vfom;	 // 3,4
	unsigned long unknown3;  // 5,6,7,8
	unsigned short unknown4; // 9,a
	float	altitude; // m	 // b,c,d,e
    float	speed; //m/s     // f,0,1,2
    float	heading; //0=> pi, -pi=>0  // 3,4,5,6
    float	verticalSpeed; //0=>       // 7,8,9,a
    float	altitude2; // m            // b,c,d,e
    double	latitude; //radians        // f,0,1,2,3,4,5,6
    double	longitude; //radians       // 7,8,9,a,b,c,d,e
    unsigned char	month;
    unsigned char	day;
    unsigned short	year;
    unsigned short	hour;
    unsigned char	minute;
    unsigned char	sec;
}send_msg_ex_0x12;

#pragma pack(pop)


static unsigned long __cdecl my_TSK_pvg_send_msg_ex(unsigned long p1, unsigned long p2)
{
    return IopSimHooks::instanace()->TSK_pvg_send_msg_ex(p1, p2);
}

static unsigned long __cdecl my_reg_read(unsigned long num, unsigned long *addr, unsigned long size, unsigned long p4)
{
    return IopSimHooks::instanace()->reg_read(num, addr, size, p4);
}

static unsigned long __cdecl my_reg_write(unsigned long num, unsigned long *addr, unsigned long size, unsigned long p4)
{
    return IopSimHooks::instanace()->reg_write(num, addr, size, p4);
}

static unsigned long __cdecl my_SYS_pvg_var_ctrl(unsigned long p1, unsigned long p2)
{
    return IopSimHooks::instanace()->SYS_pvg_var_ctrl(p1, p2);
}

IopSimHooks* IopSimHooks::m_gInstance = NULL;

IopSimHooks::IopSimHooks()
{

    m_latitude = 0;
    m_longitude = 0;
    m_speed = 0;
    m_heading = 0;
    m_verticalSpeed = 0;
    m_altitude = 0;

    InitializeCriticalSection(&m_cs);
}

IopSimHooks::~IopSimHooks()
{
    DeleteCriticalSection(&m_cs);
}

IopSimHooks* IopSimHooks::instanace()
{
    if(NULL == m_gInstance)
    {
        m_gInstance = new IopSimHooks();
    }

    return m_gInstance;
}

void  IopSimHooks::lock()
{
    EnterCriticalSection(&m_cs);
}

void IopSimHooks::unlock()
{
    LeaveCriticalSection(&m_cs);
}


bool IopSimHooks::hook(SharedStruct<GNSIntf>*  pShared)
{

    bool res = true;
    int i;

    m_pShared = pShared;
    m_pData = pShared->get();

    HMODULE hiop_sim_sim = GetModuleHandle("IOP_SIM.dll");

    SDLLHook krnlsimHook = 
    {
        "krnlsim.dll",
		true, DefaultHook,
        //false, NULL, // Default hook disabled, NULL function pointer.
        {
            { "TSK_pvg_send_msg_ex", my_TSK_pvg_send_msg_ex},
			//{ "TSK_pvg_get_msg", my_TSK_pvg_get_msg },
            { "reg_read", my_reg_read},
            { "reg_write", my_reg_write},
            { "SYS_pvg_var_ctrl" , my_SYS_pvg_var_ctrl},
            { NULL, NULL }
        }
    };

    i=0;
    HookAPICallsMod(&krnlsimHook, hiop_sim_sim);
    m_TSK_pvg_send_msg_ex_fn = (TSK_pvg_send_msg_ex_t)krnlsimHook.Functions[i++].OrigFn;
    m_reg_read_fn = (reg_read_t)krnlsimHook.Functions[i++].OrigFn;
    m_reg_write_fn = (reg_write_t)krnlsimHook.Functions[i++].OrigFn;
    m_SYS_pvg_var_ctrl_fn = (SYS_pvg_var_ctrl_t)krnlsimHook.Functions[i++].OrigFn;

    return res;
}

void printMem(unsigned long *addr)
{
	unsigned long llval0 = *(unsigned long*)addr;
	unsigned long llval1 = *(unsigned long*)(addr + 1);
	unsigned long llval2 = *(unsigned long*)(addr + 2);
	unsigned long llval3 = *(unsigned long*)(addr + 3);
	unsigned long llval4 = *(unsigned long*)(addr + 4);
	unsigned long llval5 = *(unsigned long*)(addr + 5);
	unsigned long llval6 = *(unsigned long*)(addr + 6);
	unsigned long llval7 = *(unsigned long*)(addr + 7);

	logMessageEx("--- IopSimHooks::dump %08x, [%08x %08x %08x %08x %08x %08x %08x %08x]", addr, llval0, llval1, llval2, llval3, llval4, llval5, llval6, llval7);
}

unsigned long hist12[20];
unsigned long hist16[3000];

unsigned long IopSimHooks::TSK_pvg_send_msg_ex(unsigned long p1, unsigned long p2)
{
    unsigned long res=0;

    lock();

	if (p1 != 0x16 && p1 != 0x12)
	{
		logMessageEx("NEW Message - IopSimHooks::TSK_pvg_send_msg_ex IN %08x, %08x", p1, p2);
	}

	if (0x16 == p1)
	{
		unsigned long* addr = (unsigned long*)p2;
		unsigned long addr_msg = *addr;	// *p2

		unsigned long  msg_type = *(unsigned long*)(addr_msg + 1 * 4); // *((*p2)+4)

		logMessageEx("--- IopSimHooks::TSK_pvg_send_msg_ex 0x16 msg_type %08x", msg_type);

		printMem(addr);
		printMem((unsigned long*)addr_msg);
		printMem((unsigned long*)(addr_msg + 32));
	}


    if(0x12 == p1)
    {
        static bool first_message=true;

		unsigned long* addr = (unsigned long*)p2;
        unsigned long addr_msg = *addr;	// *p2

        unsigned long  msg_type = *(unsigned long*)(addr_msg+1*4); // *((*p2)+4)

#if 1
		logMessageEx("--- IopSimHooks::TSK_pvg_send_msg_ex 0x12 msg_type %08x", msg_type);

		printMem(addr);
		printMem((unsigned long*)addr_msg);
		printMem((unsigned long*)(addr_msg + 32));
#endif

        if(0 == msg_type) // GPS location
        {
            send_msg_ex_0x12* pmsg  = (send_msg_ex_0x12*)(addr_msg+0x0b); // *((*p2)+b)

#if 1
            logMessageEx("--- GPS lat=%f, lon=%f, spe=%f head=%f vs=%f, alt=%f, alt2=%f", 
                pmsg->latitude*RAD2DEG,
                pmsg->longitude*RAD2DEG,
                pmsg->speed,
                pmsg->heading*RAD2DEG, 
                pmsg->verticalSpeed,
                pmsg->altitude,
                pmsg->altitude2);
			
			logMessageEx("--- GPS uk1=%08x, hfom=%04x, uk2=%04x, vfom=%04x, uk3=%08x, uk4=%04x",
				pmsg->unknown1, pmsg->hfom, pmsg->unknown2, pmsg->vfom, pmsg->unknown3, pmsg->unknown4);
#endif
#if 0
            if(first_message)
            {
                m_altitude2 = pmsg->altitude2;
                first_message = false;
            }

            pmsg->altitude = m_altitude;
            pmsg->altitude2 = m_altitude + m_altitude2;

            pmsg->speed = m_speed;
            pmsg->heading = m_heading;

            pmsg->latitude = m_latitude;
            pmsg->longitude = m_longitude;
#endif
#if 0
			logMessageEx("--- IopSimHooks::TSK_pvg_send_msg_ex lat=%f, lon=%f, spe=%f head=%f vs=%f, alt=%f, alt2=%f",
				pmsg->latitude*RAD2DEG,
				pmsg->longitude*RAD2DEG,
				pmsg->speed,
				pmsg->heading*RAD2DEG,
				pmsg->verticalSpeed,
				pmsg->altitude,
				pmsg->altitude2);

			logMessageEx("--- IopSimHooks::TSK_pvg_send_msg_ex uk1=%08x, hfom=%04x, uk2=%04x, vfom=%04x, uk3=%08x, uk4=%04x",
				pmsg->unknown1, pmsg->hfom, pmsg->unknown2, pmsg->vfom, pmsg->unknown3, pmsg->unknown4);
#endif
		}
    }

    res =  m_TSK_pvg_send_msg_ex_fn(p1, p2);

//    logMessageEx("--- IopSimHooks::TSK_pvg_send_msg_ex OUT %08x, %08x -> %08x", p1, p2, res);

    unlock();

    return res;
}

unsigned long histread[3000]; // 3e8 422 7f2
unsigned long histreadl[3][3000];

unsigned long IopSimHooks::reg_read(unsigned long num, unsigned long *addr, unsigned long size, unsigned long p4)
{
    unsigned long res=0;

    lock();

    res = m_reg_read_fn(num, addr, size, p4);

	unsigned char ucval = *(unsigned char*)addr;
	unsigned short usval = *(unsigned short*)addr;
	unsigned long val = *(unsigned long*)addr;
	float fval = *(float*)addr;
	unsigned long llval = *(unsigned long*)(addr + 1);
	unsigned long llval2 = *(unsigned long*)(addr + 2);
	unsigned long llval3 = *(unsigned long*)(addr + 3);

	switch (size) {
	case 1:
		if (histread[num] == ucval)	break;
		histread[num] = ucval;
		logMessageEx("--- IopSimHooks::reg_read %08x, %08x [%02x], %d, %08x -> %08x", num, addr, ucval, size, p4, res);
		break;
	case 2:
		if (histread[num] == usval) break;
		histread[num] = usval;
		logMessageEx("--- IopSimHooks::reg_read %08x, %08x [%04x], %d, %08x -> %08x", num, addr, usval, size, p4, res);
		break;
	case 4:
		if (histread[num] == val) break;
		histread[num] = val;
		logMessageEx("--- IopSimHooks::reg_read %08x, %08x [%08x]{%f}, %d, %08x -> %08x", num, addr, val, fval, size, p4, res);
		break;
	case 8:
		if (histread[num] == val && histreadl[0][num] == llval) break;
		histread[num] = val;
		histreadl[0][num] = llval;
		logMessageEx("--- IopSimHooks::reg_read %08x, %08x [%08x][%08x], %d, %08x -> %08x", num, addr, val, llval, size, p4, res);
		break;
	case 16:
	default:
		if (histread[num] == val && histreadl[0][num] == llval && histreadl[1][num] == llval2 && histreadl[2][num] == llval3) break;
		histread[num] = val;
		histreadl[0][num] = llval;
		histreadl[1][num] = llval2;
		histreadl[2][num] = llval3;
		logMessageEx("--- IopSimHooks::reg_read %08x, %08x [%08x][%08x][%08x][%08x], %d, %08x -> %08x", num, addr, val, llval, llval2, llval3, size, p4, res);
		break;
	}

	unlock();

    return res;
}

unsigned long histwrite[3000]; // 3e8 422 7f2

unsigned long IopSimHooks::reg_write(unsigned long num, unsigned long *addr, unsigned long size, unsigned long p4)
{
    unsigned long res=0;

    lock();

    res = m_reg_write_fn(num, addr, size, p4);

	unsigned char ucval = *(unsigned char*)addr;
	unsigned short usval = *(unsigned short*)addr;
	unsigned long val = *(unsigned long*)addr;
	float fval = *(float*)addr;
	double dval = *(double*)addr;
	unsigned long llval = *(unsigned long*)(addr + 1);
	float fvall = *(float*)(addr + 1);
	unsigned long llval2 = *(unsigned long*)(addr + 2);
	unsigned long llval3 = *(unsigned long*)(addr + 3);

	unlock();

	if (histwrite[num] == val) {
		return res;
	}
	histwrite[num] = val;

	switch (size) {
	case 1:
		logMessageEx("--- IopSimHooks::reg_write %08x, %08x [%02x], %d, %08x -> %08x", num, addr, ucval, size, p4, res);
		break;
	case 2:
		logMessageEx("--- IopSimHooks::reg_write %08x, %08x [%04x], %d, %08x -> %08x", num, addr, usval, size, p4, res);
		break;
	case 4:
		logMessageEx("--- IopSimHooks::reg_write %08x, %08x [%08x]{%f}, %d, %08x -> %08x", num, addr, val, fval, size, p4, res);
		break;
	case 8:
		logMessageEx("--- IopSimHooks::reg_write %08x, %08x [%08x][%08x]{%f}, %d, %08x -> %08x", num, addr, val, llval, dval, size, p4, res);
		break;
	case 16:
	default:
		logMessageEx("--- IopSimHooks::reg_write %08x, %08x [%08x][%08x][%08x][%08x], %d, %08x -> %08x", num, addr, val, llval, llval2, llval3, size, p4, res);
		break;
	}


    return res;
}

unsigned long IopSimHooks::SYS_pvg_var_ctrl(unsigned long p1, unsigned long p2)
{
    unsigned long res=0;

    lock();

    res = m_SYS_pvg_var_ctrl_fn(p1, p2);

    //logMessageEx("--- IopSimHooks::SYS_pvg_var_ctrl %08x, %08x", p1, p2);

    unlock();

    return res;
}

void  IopSimHooks::setGPSInfo(double latitude, double longitude, float speed, float	heading, float verticalSpeed, float altitude)
{
    lock();

    m_latitude = latitude;
    m_longitude = longitude;
    m_speed = speed;
    m_heading = heading;
    m_verticalSpeed = verticalSpeed;
    m_altitude = altitude;
	
    logMessageEx("--- IopSimHooks::setGPSInfo %f, %f, %f %f %f, %f", 
                   m_latitude,
                   m_longitude,
                   m_speed,
                   m_heading, 
                   m_verticalSpeed,
                   m_altitude);

    unlock();
}
