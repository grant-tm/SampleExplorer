#include "WavFileReader.h"

ParseResult WavFileReader::parse (void)
{

    // prerequisites
    if (!isOpen())
    {
        DBG("FILE IS NOTE OPEN");
        //jassert(false);
        return PARSE_ERROR;
    }
    gotoByte(0);

    // parse riff section
    if (!readCompare("RIFF"))
    {
        DBG("No RIFF header in " << filePath);
        //jassert(false);
        return PARSE_ERROR;
    }

    const int size = readInt(4);

    // parse wave description section
    if (!readCompare("WAVE"))
    {
        DBG("No WAVE desc header in " << filePath);
        //jassert(false);
        return PARSE_ERROR;
    }

    // parse format section
    int attempts = 0;
    int maxAttempts = 10;
    while (++attempts < maxAttempts)
    {
        std::string read = readString(4);
        if (read == std::string("fmt "))
            break;

        int jumpSize = readInt(4);
        if (jumpSize % 2 != 0)
            jumpSize++;
        seekBytes(jumpSize);
    }
    if (attempts >= maxAttempts)
    {
        DBG("Failed to locate format chunk in " << filePath);
        //jassert(false);
        return PARSE_ERROR;
    }

    const int chunkSize = readInt(4);
    const int waveFormat = readInt(2);
    const int numChannels = readInt(2);
    const int sampleRate = readInt(4);
    const int dataRate = readInt(4);
    const int blockAlign = readInt(2);
    const int bitDepth = readInt(2);
    if (chunkSize > 16)
        seekBytes(chunkSize - 16);

    attempts = 0;
    maxAttempts = 10;
    while (++attempts < maxAttempts)
    {
        std::string read = readString(4);
        if (read == std::string("data"))
            break;

        int jumpSize = readInt(4);
        if (jumpSize % 2 != 0)
            jumpSize++;
        seekBytes(jumpSize);
    }
    if (attempts >= maxAttempts)
    {
        DBG("Failed to locate data chunk in " << filePath);
        //jassert(false);
        return PARSE_ERROR;
    }

    const int dataLen = readInt(4);
    int bytesPerSample = bitDepth / 8;
    int numSamples = dataLen / bytesPerSample;
    auto startLocation = getLoc();

    uint32_t *samples = new uint32_t[numSamples];

    switch (bitDepth)
    {
        case 8:
            //DBG("8 bit not implemented");
            break;

        case 16:
            //DBG("16 bit not implemented");
            break;
        
        case 24:
            readUints24SIMD(startLocation, samples, numSamples);
            break;

        case 32:
            //DBG("32 bit not implemented");
            break;

        default:
            break;
    }

    delete[] samples;
    return PARSE_SUCCESS;
}