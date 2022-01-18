#include <iostream>
#include "HPSocket.h"
#include "HPTypeDef.h"
#include "SocketInterface.h"
#include <unistd.h>

using namespace::std;


class CListenerImpl : public CUdpClientListener
{

public:
	virtual EnHandleResult OnPrepareConnect(IUdpClient* pSender, CONNID dwConnID, SOCKET socket) override
	{
		cout<<"OnPrepareConnect"<<endl;
		return HR_OK;
	}

	virtual EnHandleResult OnConnect(IUdpClient* pSender, CONNID dwConnID) override
	{
		cout<<"OnConnect"<<endl;
		return HR_OK;
	}

	virtual EnHandleResult OnHandShake(IUdpClient* pSender, CONNID dwConnID) override
	{
		return HR_OK;
	}

	virtual EnHandleResult OnReceive(IUdpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
		
		return HR_OK;
	}

	virtual EnHandleResult OnSend(IUdpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override
	{
		cout<<"OnSend"<<endl;
		return HR_OK;
	}

	virtual EnHandleResult OnClose(IUdpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) override
	{
		cout<<"client OnClose"<<endl;
		return HR_OK;
	}

};
int main()
{
	const BYTE *pBuffer = (const BYTE *)"yuyunou";
    CListenerImpl s_listener;
    IUdpClient* p_udp_client = HP_Create_UdpClient(&s_listener);

	LPCTSTR lpszBindAddress = "192.168.85.153";
	USHORT usPort = 8988;
	p_udp_client->SetDetectAttempts(0);//关闭心跳检测机制
	p_udp_client->Start(lpszBindAddress, usPort);
	
	sleep(5);
    while (1)
	{
		cout<<"###send"<<endl;
		p_udp_client->Send(pBuffer, 1);
		usleep(200 * 1000);
	}
    
    return 0;
}
















