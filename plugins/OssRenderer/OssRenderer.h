#ifndef OSS_RENDERER_H
#define OSS_RENDERER_H

#include <plugin/IRenderer.h>
using namespace mous;

class OssRenderer: public IRenderer
{
public:
    OssRenderer();

public:
    virtual ~OssRenderer();

    virtual EmErrorCode OpenDevice(const std::string& path);
    virtual void CloseDevice();
    virtual EmErrorCode SetupDevice(int32_t channels, int32_t sampleRate, int32_t bitsPerSample);
    virtual EmErrorCode WriteDevice(const char* buf, uint32_t len);

private:
    std::string m_PrevPath;
    int m_Fd;
    bool m_IsOpened;
    int32_t m_Channels;
    int32_t m_SampleRate;
    int32_t m_BitsPerSample;
};

#endif
