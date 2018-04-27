#include <string>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "AVPlayer.h"
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
	std::string strPath;
	//std::cin >> strPath;
	CAVPlayer   cAVPlayer;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	bool flag = false;
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, 0);
	
	sockaddr_in sin;
	sin.sin_family = AF_INET;//ѡ��IPV4
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	sin.sin_port = htons(8888);//�˿ں�

	bind(sclient, (sockaddr*)&sin, sizeof(sin));

	//inet_pton(AF_INET, "192.168.155.135", (void*)&sin.sin_addr.S_un.S_addr);//��ʮ����ת��Ϊ�����Ƹ�����������
	//char sendData[255]="192.168.155.136";

	ip_mreq multiCast;
	multiCast.imr_interface.S_un.S_addr = INADDR_ANY;
	multiCast.imr_multiaddr.S_un.S_addr = inet_addr("234.2.2.2");
	setsockopt(sclient, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast));
	int len = sizeof(sockaddr);

	while (true)
	{
		char recvData[100] = { 0 };
		recvfrom(sclient, recvData, sizeof(recvData) - 1, 0, (sockaddr*)&sin, &len);
		printf("%s\n", recvData);
		//δ��ʼ�����򲥷ţ��ѿ�ʼ����������ͣ�䲥��
		if (recvData[0] == 'a') {
			if (flag)
			{
				cAVPlayer.Play();
			}
			else
			{
				cAVPlayer.Play("test4.avi");
				flag = true;
			}
		}
		//��������ͣ
		if (recvData[0] == 'b') {
			cAVPlayer.Pause();
			std::cout << cAVPlayer.GetTime();
		}
		//ֹͣ��flag���ã����¿�ʼ�����ļ�·��
		if (recvData[0] == 'c') {
			cAVPlayer.Stop();
			flag = false;
		}
		//����ʱ�䣬ͬ����ĳһʱ���
		if (recvData[0]='2') {
			int time = atoi(recvData);
			//cAVPlayer.SetTime(time);// �ض������½��в�������Ӧ��ʱ��ѭ������
		}
	}

	closesocket(sclient);
	WSACleanup();
	return 0;
}

