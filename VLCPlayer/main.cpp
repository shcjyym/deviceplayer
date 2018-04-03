#include <string>
#include <stdio.h>
#include <winsock2.h>
#include<WS2tcpip.h>
#include "AVPlayer.h"
#pragma comment(lib,"ws2_32.lib")


int main(int argc, char* argv[])
{
	std::string strPath;
	//std::cin >> strPath;
	CAVPlayer   cAVPlayer;
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	bool flag = false;
	if (WSAStartup(socketVersion, &wsaData) != 0){
		printf("failed to initial client\n");
		return 0;
	}
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;//选择IPV4
	sin.sin_port = htons(8888);//端口号
//	sin.sin_addr.S_un.S_addr = inet_addr("192.168.155.135");
	inet_pton(AF_INET, "192.168.155.135", (void*)&sin.sin_addr.S_un.S_addr);//点十进制转换为二进制给第三个参数
	int len = sizeof(sin);
	char sendData[255]="192.168.155.135";
	sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);
	while (true)
	{
		char recvData[255];
		int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);
		if (ret > 0)
		{
			recvData[ret] = 0x00;
			printf(recvData);
		}
		//未开始播放则播放，已开始播放则由暂停变播放
		if (recvData[0] == '2') {
			if (flag)
			{
				cAVPlayer.Play();
			}
			else 
			{
				cAVPlayer.Play("D:\\test4.avi");
				flag = true;
			}
		}
		//播放中暂停
		if (recvData[0] == '3') {
			cAVPlayer.Pause();
		}
		//停止，flag重置，重新开始输入文件路径
		if (recvData[0] == '4') {
			cAVPlayer.Stop();
			flag = false;
		}
		//调整时间，同步到某一时间点
		if (recvData[0] == '5') {
			int time = atoi(recvData);
			cAVPlayer.SetTime(time);
		}
	}
	system("pause");
	closesocket(sclient);
	WSACleanup();
	return 0;
}

