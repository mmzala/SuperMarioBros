#include "AudioManager.h"
#include <xaudio2.h>

AudioManager::AudioManager()
	:
	xAudio(nullptr),
	masterVoice(nullptr)
{
	HRESULT result;
	result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to initialize COM!", L"Error!", MB_OK);
		PostQuitMessage(0);
	}
	
	result = XAudio2Create(&xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to create XAudio2 engine!", L"Error!", MB_OK);
		PostQuitMessage(0);
	}

	result = xAudio->CreateMasteringVoice(&masterVoice);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to create master voice for XAudio2!", L"Error!", MB_OK);
		PostQuitMessage(0);
	}
}

AudioManager::~AudioManager()
{
	//delete masterVoice; // This causes an error (this only happens when the player closes the program, so it does not matter that much :D)
	xAudio->Release();

	masterVoice = 0;
	xAudio = 0;
}

IXAudio2* AudioManager::GetAudioEngine()
{
	return xAudio;
}
