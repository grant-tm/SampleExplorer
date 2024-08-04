#include "SamplePlayer.h"

SamplePlayer::SamplePlayer() : juce::Thread("Audio Player Thread")
{
    formatManager.registerBasicFormats();
}

SamplePlayer::~SamplePlayer()
{
    stopPlayback();
}

void SamplePlayer::playSample(juce::File fileToPlay)
{
    if (isThreadRunning())
        stopPlayback();
    
    setFile(fileToPlay);
    startThread();
}

void SamplePlayer::stopPlayback()
{
    if (!isThreadRunning())
        return;

    signalThreadShouldExit();
    stopThread(100);
}

void SamplePlayer::setFile(juce::File fileToRead)
{
    auto reader = formatManager.createReaderFor(fileToRead);
    if (reader != nullptr)
    {
        source.reset(new juce::AudioFormatReaderSource(reader, true));
    }
}

void SamplePlayer::run()
{
    if (!source)
        return;

    deviceManager.initialiseWithDefaultDevices(0, 2);
    juce::AudioIODevice *device = deviceManager.getCurrentAudioDevice();

    if (!device)
        return;

    source->prepareToPlay(device->getDefaultBufferSize(), device->getCurrentSampleRate());
    player.setSource(source.get());
    deviceManager.addAudioCallback(&player);

    while (!threadShouldExit() && source->getNextReadPosition() < source->getTotalLength())
    {
        juce::Thread::sleep(50);
    }

    player.setSource(nullptr);
    deviceManager.removeAudioCallback(&player);
}
