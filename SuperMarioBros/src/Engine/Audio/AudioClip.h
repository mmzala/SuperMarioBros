#pragma once

#include <xaudio2.h>

class AudioClip
{
public:
	AudioClip(const char* file, bool loop = false);
	~AudioClip();

	void Play();
	void Stop();
	void SetVolume(float volume);

private:
	void CreateSourceVoice();
	void InitializeDataFromFile(const char* file);
	HRESULT CreateFile(const char* file, HANDLE& hFile);
	HRESULT FindChunk(HANDLE file, DWORD type, DWORD& chunkSize, DWORD& chunkDataPosition);
	HRESULT ReadChunkData(HANDLE file, void* buffer, DWORD bufferSize, DWORD bufferOffset);

private:
	IXAudio2SourceVoice* sourceVoice;

	XAUDIO2_BUFFER buffer;
	WAVEFORMATEXTENSIBLE wfx;
};