#include "ByteReader.h"

//=============================================================================
// CONSTRUCTORS / DESTRUCTORS

ByteReader::ByteReader() :
    fileHandle(INVALID_HANDLE_VALUE),
    mapHandle(INVALID_HANDLE_VALUE),
    buffer(nullptr),
    bufferSize(0),
    currentIndex(0)
{}

ByteReader::ByteReader (const juce::String &fileToRead)
{
    open(fileToRead);
    filePath = fileToRead;
}

ByteReader::~ByteReader (void)
{
    close();
}

//=============================================================================
// FILE MANAGEMENT

void ByteReader::open (const juce::String &filePath)
{
    // open file
    fileHandle = CreateFileW(filePath.toWideCharPointer(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    jassert(fileHandle != INVALID_HANDLE_VALUE);

    // read file size
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(fileHandle, &fileSize))
    {
        CloseHandle(fileHandle);
        fileHandle = INVALID_HANDLE_VALUE;
        jassert(false);
    }
    bufferSize = static_cast<size_t>(fileSize.QuadPart);

    // initialize map
    mapHandle = CreateFileMapping(
        fileHandle,
        NULL,
        PAGE_READONLY,
        0,
        0,
        NULL
    );

    // checking for null instead of INVALID_HANDLE_VALUE
    // because of CreateFileMapping call above
    if (mapHandle == NULL)
    {
        CloseHandle(fileHandle);
        fileHandle = INVALID_HANDLE_VALUE;
        jassert(false);
    }

    // map files into buffer
    buffer = static_cast<unsigned char *>(MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, 0));
    if (buffer == NULL)
    {
        CloseHandle(mapHandle);
        CloseHandle(fileHandle);
        fileHandle = INVALID_HANDLE_VALUE;
        mapHandle = INVALID_HANDLE_VALUE;
        jassert(false);
    }

    currentIndex = 0;
}

bool ByteReader::isOpen (void)
{
    return fileHandle != INVALID_HANDLE_VALUE;
}

void ByteReader::close()
{
    if (buffer)
    {
        UnmapViewOfFile(buffer);
        buffer = nullptr;
    }
    if (mapHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(mapHandle);
        mapHandle = INVALID_HANDLE_VALUE;
    }
    if (fileHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(fileHandle);
        fileHandle = INVALID_HANDLE_VALUE;
    }
    bufferSize = 0;
    currentIndex = 0;
}

//=============================================================================
// MOVE CURSOR

int ByteReader::seekBytes (int bytes)
{
    currentIndex += bytes;
    currentIndex = juce::jmax(currentIndex, size_t(0));
    currentIndex = juce::jmin(currentIndex, bufferSize - 1);
    return (int)currentIndex;
}

size_t ByteReader::getCursor (void)
{
    return currentIndex;
}

int ByteReader::gotoByte (int byte)
{
    currentIndex = juce::jmax(byte, 0);
    currentIndex = juce::jmin(currentIndex, bufferSize - 1);
    currentIndex = byte;
    return (int)currentIndex;
}

//=============================================================================
// READ

unsigned char ByteReader::getByte (size_t index)
{
    if (index < 0 || index > bufferSize) {
        return NULL;
    }
    return buffer[index];
}

unsigned char ByteReader::readByte (void)
{
    if (currentIndex >= bufferSize || currentIndex < 0)
    {
        return NULL;
    }
    return buffer[currentIndex++];
}

void ByteReader::readBytes (std::vector<unsigned char> *container, int bytes)
{

    if (container == nullptr)
    {
        currentIndex = juce::jmin(currentIndex + bytes, bufferSize);
        return;
    }

    if (currentIndex + bytes > bufferSize)
    {
        bytes = (int)(bufferSize - currentIndex);
    }

    container->assign(buffer + currentIndex, buffer + currentIndex + bytes);
    currentIndex += bytes;
}

bool ByteReader::readCompare(const char *string) {
    size_t length = std::strlen(string);
    
    if (currentIndex + length > bufferSize) {
        return false;
    }

    bool result = std::memcmp(buffer + currentIndex, string, length) == 0;
    if (result)
    {
        currentIndex += length;
    }
    return result;
}

std::string ByteReader::readString (int length)
{
    if (length < 0 || currentIndex + length > bufferSize)
    {
        return "";
    }

    std::string result(buffer + currentIndex, buffer + currentIndex + length);
    currentIndex += length;

    return result;
}

int ByteReader::readInt (int numBytes)
{
    if (currentIndex + numBytes > bufferSize)
    {
        return -1;
    }

    int result = 0;
    for (int i = 0; i < numBytes; i++)
    {
        result |= buffer[currentIndex + i] << (i * 8);
    }
    currentIndex += numBytes;

    return result;
}

//=============================================================================
// GET MEMORY LOCATIONS

const unsigned char *ByteReader::getLoc (void)
{
    if (currentIndex < 0 || currentIndex > bufferSize)
    {
        return nullptr;
    }

    return buffer + currentIndex;
}

const unsigned char *ByteReader::getByteLoc (size_t index)
{
    if (index < 0 || index > bufferSize)
    {
        return nullptr;
    }

    return buffer + index;
}

//=============================================================================
// FAST SAMPLE READS

void ByteReader::readUints24(const unsigned char *buf, uint32_t *output, int numSamples)
{
    const int bitDepth = 24;
    const int bytesPerUint = 3;

    alignas(16) uint32_t unpacked[4];
    for (int i = 0; i < numSamples; i += 4)
    {
        for (int j = 0; j < 4 && (i + j) < numSamples; ++j)
        {
            const uint8_t *addr = buf + (i + j) * bytesPerUint;
            
            unpacked[j] = (static_cast<int32_t>(addr[0]) << 8)
                | (static_cast<uint32_t>(addr[1]) << 16)
                | (static_cast<uint32_t>(addr[2]) << 24);
            
            unpacked[j] >>= 8;
        }
        for (int j = 0; j < 4 && (i + j) < numSamples; ++j)
        {
            output[i + j] = unpacked[j];
        }
    }
}

void ByteReader::readUints24SIMD(const unsigned char *buf, uint32_t *output, int numSamples)
{
    int sampleIndex = 0;
    for (sampleIndex; sampleIndex <= (numSamples - 5); sampleIndex += 5)
    {
        __m128i data = _mm_loadu_si128(reinterpret_cast<const __m128i *>(buf + sampleIndex * 3));
        auto q0 = _mm_extract_epi32(data, 0); // { 3,  2,  1,  0}
        auto q1 = _mm_extract_epi32(data, 1); // { 7,  6,  5,  4}
        auto q2 = _mm_extract_epi32(data, 2); // {11, 10,  9,  8}
        auto q3 = _mm_extract_epi32(data, 3); // {15, 14, 13, 12}

        // sample 1: {2, 1, 0}
        output[sampleIndex+0] = q0 & 0x00FFFFFF;

        // sample 2: {5, 4, 3}
        output[sampleIndex+1] = 
            ((q1 << 8) & 0x00FFFF00)|  // {7, 6, 5, 4} <<  8 & 0x00FFFF00 -> {0, 5, 4, 0}
            ((q0 >> 24) & 0x000000FF); // {3, 2, 1, 0} >> 24 & 0x000000FF -> {0, 0, 0, 3}

        // sample 3: {8, 7, 6}
        output[sampleIndex+2] = 
            ((q2 << 16) & 0x00FF0000)| // {11, 10, 9, 8} << 16 & 0x00FF0000 -> {0, 8, 0, 0}
            ((q1 >> 16) & 0x0000FFFF); // { 7,  6, 5, 4} >> 16 & 0x0000FFFF -> {0, 0, 7, 6}

        // sample 4: {11, 10, 9}
        output[sampleIndex+3] = ((q2 >> 8) & 0x00FFFFFF); // {11, 10, 9, 8} >> 8 & 0x00FFFFFF -> {0, 11, 10, 9}

        // sample 5: {14, 13, 12}
        output[sampleIndex+4] = q3 & 0x00FFFFFF;
    }

    // read remaining samples one by one
    alignas(16) uint32_t unpacked[4];
    for (sampleIndex; sampleIndex < numSamples; sampleIndex += 1)
    {
        for (int j = 0; j < 4 && (sampleIndex + j) < numSamples; ++j)
        {
            const uint8_t *addr = buf + (sampleIndex + j) * 3;
            unpacked[j] = (static_cast<int32_t>(addr[0]) << 8)
                | (static_cast<uint32_t>(addr[1]) << 16)
                | (static_cast<uint32_t>(addr[2]) << 24);
            unpacked[j] >>= 8;
        }
        for (int j = 0; j < 4 && (sampleIndex + j) < numSamples; ++j)
        {
            output[sampleIndex + j] = unpacked[j];
        }
    }
    
}