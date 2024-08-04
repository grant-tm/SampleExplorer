#ifndef SAMPLE_PLAYER_H
#define SAMPLE_PLAYER_H

#include <JuceHeader.h>

class SamplePlayer : protected juce::Thread
{
public:
    SamplePlayer();
    ~SamplePlayer();

    void playSample(juce::File);
    void stopPlayback();

private:
    
    void setFile(juce::File);

    void run() override;
    
    juce::File file;
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> source;
    juce::AudioDeviceManager deviceManager;
    juce::AudioSourcePlayer player;
};

#endif // SAMPLE_PLAYER_H