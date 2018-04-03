#ifndef AVPlayer_H
#define AVPlayer_H
#include <iostream>

typedef void(*pfnPosChanged) (void *data, int iPos);  // 文件位置变化

struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_event_t;

class CAVPlayer
{
public:
	CAVPlayer(void);
	~CAVPlayer(void);

	//bool Play(const std::string &strPath);  // 播放路径为strPath的文件
	void Play();                           // 播放
	void Pause();                           // 暂停
	void Stop();                           // 停止
	bool Play(const std::string &strPath);             //只加载不Play？

	void Volume(int nVol);                  // 音量设置为nVol
	void VolumeIncrease();                  // 音量增大
	void VolumeReduce();                    // 音量减小 

	void SeekTo(int nPos);                  // 跳到指定位置nPos
	void SeekForward();                     // 快进
	void SeekBackward();                    // 快退
	void Refresh(int real_time);
	void SetTime(int time);// 设置时间

	void SetCallback(pfnPosChanged pfn);    // 设置文件位置改变时的回调函数
	pfnPosChanged GetCallback();            // 获取文件位置改变时的回调函数

	bool    IsOpen();                       // 文件是否打开
	bool    IsPlaying();                    // 文件是否正在播放
	int     GetPos();                       // 获取文件当前播放的位置
	__int64 GetTime();                      // 获取时间
	__int64 GetLength();                   //获取实际长度

private:
	libvlc_instance_t       *m_pVLC_Inst;   // VLC实例
	libvlc_media_player_t   *m_pVLC_Player; // VLC播放器
	pfnPosChanged           m_pfn;          // 文件位置改变时的回调函数

	void Init();                            // 初始化
	void Release();                         // 清理内存
};

#endif