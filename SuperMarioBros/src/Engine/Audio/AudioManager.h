#pragma once

struct IXAudio2;
struct IXAudio2MasteringVoice;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	IXAudio2* GetAudioEngine();
	
private:
	IXAudio2* xAudio;
	IXAudio2MasteringVoice* masterVoice;
};