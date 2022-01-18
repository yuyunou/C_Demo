#include <iostream>
#include "HPSocket.h"
#include "HPTypeDef.h"
#include "SocketInterface.h"


using namespace::std;

class CListenerImpl : public CUdpServerListener
{

public:
	virtual EnHandleResult OnPrepareListen(IUdpServer* pSender, SOCKET soListen) override
	{

		return HR_OK;
	}

	virtual EnHandleResult OnAccept(IUdpServer* pSender, CONNID dwConnID, UINT_PTR soClient) override
	{
		BOOL bPass = TRUE;
		TCHAR szAddress[100];
		int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
		USHORT usPort;

		cout<<"OnAccept"<<endl;

		return bPass ? HR_OK : HR_ERROR;
	}

	virtual EnHandleResult OnHandShake(IUdpServer* pSender, CONNID dwConnID) override
	{
		return HR_OK;
	}

	virtual EnHandleResult OnReceive(IUdpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
		cout<<"SERVER OnReceive"<<endl;
		cout<<"%s"<<pData<<endl;
		return HR_ERROR;
	}

	virtual EnHandleResult OnSend(IUdpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
	
		return HR_OK;
	}

	virtual EnHandleResult OnClose(IUdpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) override
	{
		cout<<"OnClose"<<endl;
		return HR_OK;
	}

	virtual EnHandleResult OnShutdown(IUdpServer* pSender) override
	{
		
		return HR_OK;
	}

};

int main()
{
    CListenerImpl s_listener;
    IUdpServer* p_udp_server = HP_Create_UdpServer(&s_listener);

	LPCTSTR lpszBindAddress = "192.168.85.153";
	 USHORT usPort = 8988;
	 p_udp_server->SetDetectAttempts(0);//关闭心跳检测机制
	 
	p_udp_server->Start(lpszBindAddress, usPort);
	
    while(1);
    
    return 0;
}
















