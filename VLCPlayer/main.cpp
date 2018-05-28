#include <string>
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "AVPlayer.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

struct Command
{
	uint16_t head;
	uint16_t type;
	uint16_t order;
	SYSTEMTIME time;
	uint16_t tail;
};

int main(int argc, char* argv[])
{
	Command Cmd;
	std::string strPath;
	//std::cin >> strPath;
	CAVPlayer   cAVPlayer;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, 0);
	bool flag = false;
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
	int len = sizeof(sin);

	while (true)
	{
		char recvData[1000] = { 0 };
		recvfrom(sclient, recvData, 1000, 0, (struct sockaddr*)&sin, &len);
		Cmd = *(Command*)recvData;
		cout << "type: " << Cmd.type <<"   "<< "order: " << Cmd.order << endl;
		//δ��ʼ�����򲥷ţ��ѿ�ʼ����������ͣ�䲥��
		if (Cmd.type == 2 && Cmd.order == 1 && flag == true) {
			cAVPlayer.Play();
		}
		if (Cmd.type == 1 && Cmd.order == 1) {
			cAVPlayer.Play("test.avi");
			flag = true;
		}
		//��������ͣ
		if (Cmd.type == 2 && Cmd.order == 2) {
			cAVPlayer.Pause();
			std::cout << "realtime-device: " << cAVPlayer.GetTime() << endl;
		}
		//ֹͣ��flag���ã����¿�ʼ�����ļ�·��
		if (Cmd.type == 2 && Cmd.order == 3) {
			cAVPlayer.Stop();
			flag = false;
		}
		//����ʱ�䣬ͬ����ĳһʱ���
		if (Cmd.type == 3) {
			int time = Cmd.order;
			cAVPlayer.SetTime(time);// �ض������½��в�������Ӧ��ʱ��ѭ������
		}
	}
		closesocket(sclient);
		WSACleanup();
		return 0;
	}
