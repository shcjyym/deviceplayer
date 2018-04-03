#ifndef AVPlayer_H
#define AVPlayer_H
#include <iostream>

typedef void(*pfnPosChanged) (void *data, int iPos);  // �ļ�λ�ñ仯

struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_event_t;

class CAVPlayer
{
public:
	CAVPlayer(void);
	~CAVPlayer(void);

	//bool Play(const std::string &strPath);  // ����·��ΪstrPath���ļ�
	void Play();                           // ����
	void Pause();                           // ��ͣ
	void Stop();                           // ֹͣ
	bool Play(const std::string &strPath);             //ֻ���ز�Play��

	void Volume(int nVol);                  // ��������ΪnVol
	void VolumeIncrease();                  // ��������
	void VolumeReduce();                    // ������С 

	void SeekTo(int nPos);                  // ����ָ��λ��nPos
	void SeekForward();                     // ���
	void SeekBackward();                    // ����
	void Refresh(int real_time);
	void SetTime(int time);// ����ʱ��

	void SetCallback(pfnPosChanged pfn);    // �����ļ�λ�øı�ʱ�Ļص�����
	pfnPosChanged GetCallback();            // ��ȡ�ļ�λ�øı�ʱ�Ļص�����

	bool    IsOpen();                       // �ļ��Ƿ��
	bool    IsPlaying();                    // �ļ��Ƿ����ڲ���
	int     GetPos();                       // ��ȡ�ļ���ǰ���ŵ�λ��
	__int64 GetTime();                      // ��ȡʱ��
	__int64 GetLength();                   //��ȡʵ�ʳ���

private:
	libvlc_instance_t       *m_pVLC_Inst;   // VLCʵ��
	libvlc_media_player_t   *m_pVLC_Player; // VLC������
	pfnPosChanged           m_pfn;          // �ļ�λ�øı�ʱ�Ļص�����

	void Init();                            // ��ʼ��
	void Release();                         // �����ڴ�
};

#endif