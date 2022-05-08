#include "AudioClip.h"
#include "../SMBEngine.h" // Getting AudioManager
#include "AudioManager.h" // Getting audio engine

#ifdef _XBOX // Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX // Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

AudioClip::AudioClip(const char* file, bool loop)
    :
    sourceVoice(nullptr),
    buffer({ 0 }),
    wfx({ 0 })
{
    InitializeDataFromFile(file);

    if (loop)
    {
        buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    }

    CreateSourceVoice();
}

AudioClip::~AudioClip()
{
    delete buffer.pAudioData;
    sourceVoice->DestroyVoice();
}

void AudioClip::Play()
{
    // We have to submit the buffer everytime we play the audio
    // https://gamedev.net/forums/topic/577468-xaudio2-how-come-i-am-only-able-to-play-sound-once-with-out-reloading-audio-data/4680833/
    SubmitSourceBuffer();

    if (FAILED(sourceVoice->Start(0)))
    {
        MessageBox(NULL, L"Failed to play Audio Clip!", L"Error!", MB_OK);
        PostQuitMessage(0);
    }
}

void AudioClip::Stop()
{
    if (FAILED(sourceVoice->Stop(0)))
    {
        MessageBox(NULL, L"Failed to stop Audio Clip!", L"Error!", MB_OK);
        PostQuitMessage(0);
    }
}

void AudioClip::SetVolume(float volume)
{
    sourceVoice->SetVolume(volume);
}

void AudioClip::CreateSourceVoice()
{
    HRESULT result;
    IXAudio2* xAudio = SMBEngine::GetInstance()->GetAudioManager()->GetAudioEngine();

    result = xAudio->CreateSourceVoice(&sourceVoice, (WAVEFORMATEX*)&wfx);
    if (FAILED(result))
    {
        MessageBox(NULL, L"Could not create Source Voice for an Audio Clip!", L"Error!", MB_OK);
        PostQuitMessage(0);
    }
}

void AudioClip::InitializeDataFromFile(const char* file)
{
    HANDLE hFile = 0;
    CreateFile(file, hFile);

    DWORD chunkSize = 0;
    DWORD chunkPosition = 0;

    // Check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(hFile, fourccRIFF, chunkSize, chunkPosition);
    DWORD filetype = 0;
    ReadChunkData(hFile, &filetype, sizeof(DWORD), chunkPosition);

    if (filetype != fourccWAVE)
    {
        MessageBox(NULL, L"Given audio file is not of .WAV type!", L"Error!", MB_OK);
        PostQuitMessage(0);
    }

    // Locate the 'fmt' chunk, and copy its contents into a wfx structure
    FindChunk(hFile, fourccFMT, chunkSize, chunkPosition);
    ReadChunkData(hFile, &wfx, chunkSize, chunkPosition);

    // Fill out the audio data buffer with the contents of the fourccDATA chunk
    FindChunk(hFile, fourccDATA, chunkSize, chunkPosition);
    BYTE* dataBuffer = new BYTE[chunkSize];
    ReadChunkData(hFile, dataBuffer, chunkSize, chunkPosition);

    // Populate buffer
    buffer.AudioBytes = chunkSize;  // Size of the audio buffer in bytes
    buffer.pAudioData = dataBuffer;  // Buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM; // Tell the source voice not to expect any data after this buffer
}

void AudioClip::SubmitSourceBuffer()
{
    HRESULT result;

    // We flush the buffer to make sure the buffer is empty before submitting
    result = sourceVoice->FlushSourceBuffers();
    if (FAILED(result))
    {
        MessageBox(NULL, L"Failed to flush the buffer of the Audio Clip!", L"Error!", MB_OK);
        PostQuitMessage(0);
    }

    result = sourceVoice->SubmitSourceBuffer(&buffer);
    if (FAILED(result))
    {
        MessageBox(NULL, L"Failed to submit buffer to Source Voice in an Audio Clip!", L"Error!", MB_OK);
        PostQuitMessage(0);
    }
}

HRESULT AudioClip::CreateFile(const char* file, HANDLE& hFile)
{
    hFile = CreateFileA(
        file,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

HRESULT AudioClip::FindChunk(HANDLE file, DWORD type, DWORD& chunkSize, DWORD& chunkDataPosition)
{
    HRESULT result = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(file, 0, NULL, FILE_BEGIN))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }   

    DWORD chunkType = 0;
    DWORD chunkDataSize = 0;
    DWORD RIFFDataSize = 0;
    DWORD fileType = 0;
    DWORD bytesRead = 0;
    DWORD offset = 0;

    while (result == S_OK)
    {
        DWORD read;
        if (ReadFile(file, &chunkType, sizeof(DWORD), &read, NULL) == 0)
        {
            result = HRESULT_FROM_WIN32(GetLastError());
        }

        if (ReadFile(file, &chunkDataSize, sizeof(DWORD), &read, NULL) == 0)
        {
            result = HRESULT_FROM_WIN32(GetLastError());
        }

        switch (chunkType)
        {
        case fourccRIFF:
            RIFFDataSize = chunkDataSize;
            chunkDataSize = 4;

            if (ReadFile(file, &fileType, sizeof(DWORD), &read, NULL) == 0)
            {
                result = HRESULT_FROM_WIN32(GetLastError());
            }
            break;

        default:
            if (SetFilePointer(file, chunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
            {
                return HRESULT_FROM_WIN32(GetLastError());
            }
        }

        offset += sizeof(DWORD) * 2;

        if (chunkType == type)
        {
            chunkSize = chunkDataSize;
            chunkDataPosition = offset;
            return S_OK;
        }

        offset += chunkDataSize;

        if (bytesRead >= RIFFDataSize) return S_FALSE;
    }

    return S_OK;
}

HRESULT AudioClip::ReadChunkData(HANDLE file, void* buffer, DWORD bufferSize, DWORD bufferOffset)
{
    HRESULT result = S_OK;
    if (SetFilePointer(file, bufferOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }
        
    DWORD read;

    if (ReadFile(file, buffer, bufferSize, &read, NULL) == 0)
    {
        result = HRESULT_FROM_WIN32(GetLastError());
    }

    return result;
}