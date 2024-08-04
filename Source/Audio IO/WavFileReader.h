#ifndef WAV_FILE_READER_H
#define WAV_FILE_READER_H

#include <JuceHeader.h>
#include "ByteReader.h"

class WavFileReader : public ByteReader
{
public:
    WavFileReader() : ByteReader() {};
    WavFileReader(const juce::String &string) : ByteReader(string) {};

    ParseResult parse();
};

#endif // WAV_FILE_READER_H