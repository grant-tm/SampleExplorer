#ifndef BYTE_READER_H
#define BYTE_READER_H

#include <JuceHeader.h>
#include <windows.h>

enum ParseResult
{
	PARSE_SUCCESS,
	PARSE_ERROR
};

class ByteReader {
public:

	// constructors / destructors
	ByteReader();
	ByteReader(const juce::String &);
	~ByteReader(void);

	// file management
	void open(const	juce::String &filePath);
	bool isOpen(void);
	void close(void);

	// random access read
	unsigned char getByte (size_t);

	// read at cursor
	unsigned char readByte (void);
	void readBytes (std::vector<unsigned char> *container, int bytes);
	int readInt (int);
	std::string readString (int length);
	bool readCompare (const char *);

	// fast sample reads
	void readUints16SIMD(const unsigned char *buf, uint32_t *output, int numSamples);
	void readUints24(const unsigned char *buf, uint32_t *output, int numSamples);
	void readUints24SIMD(const unsigned char *buf, uint32_t *output, int numSamples);

	// move cursor
	int gotoByte (int);
	int seekBytes (int);
	size_t getCursor (void);

	// get memory locations
	const unsigned char *getLoc (void);
	const unsigned char *getByteLoc (size_t);

protected:

	juce::String filePath;
	juce::AudioBuffer<int> samples;

private:

	HANDLE fileHandle;
	HANDLE mapHandle;

	const unsigned char *buffer;
	size_t bufferSize;
	size_t currentIndex;
};

#endif // BYTE_READER
