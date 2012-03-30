#ifndef WAVDECODER_H
#define WAVDECODER_H

#include <plugin/IDecoder.h>
#include <inttypes.h>
#include <fstream>
using namespace std;
using namespace mous;

#pragma pack(push, 1)

struct WavHeader
{
    // RIFF chunk
    char riffId[4];
    uint32_t lenAfterRiff;
    char riffType[4];

    // format chunk
    char formatId[4];
    uint32_t formatChunkLen;
    uint16_t formatTag;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t avgBytesPerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;

    // data chunk
    char dataId[4];
    uint32_t dataChunkLen;
};

#pragma pack(pop)

class WavDecoder: public IDecoder
{
public:
    WavDecoder();
    virtual ~WavDecoder();

    virtual vector<string> GetFileSuffix() const;

    virtual EmErrorCode Open(const std::string& url);
    virtual void Close();

    virtual bool IsFormatVaild() const;

    virtual EmErrorCode DecodeUnit(char* data, uint32_t& used, uint32_t& unitCount);
    virtual EmErrorCode SetUnitIndex(uint64_t index);
    virtual uint32_t GetMaxBytesPerUnit() const;
    virtual uint64_t GetUnitIndex() const;
    virtual uint64_t GetUnitCount() const;

    virtual EmAudioMode GetAudioMode() const;
    virtual int32_t GetChannels() const;
    virtual int32_t GetBitsPerSample() const;
    virtual int32_t GetSampleRate() const;
    virtual int32_t GetBitRate() const;
    virtual uint64_t GetDuration() const;

private:
    ifstream m_InputStream;
    WavHeader m_WavHeader;
    const int SAMPLES_PER_BLOCK;

    size_t m_RawDataOffset;
    size_t m_RawDataLength;

    int m_SampleLength;
    int m_BlockLength;
    char* m_BlockBuffer;
    size_t m_BlockIndex;
    size_t m_TotalBlocks;

    uint32_t m_MaxBytesPerUnit;
    uint64_t m_UnitIndex;
    uint64_t m_UnitCount;

    uint64_t m_Duration;
};

#endif
