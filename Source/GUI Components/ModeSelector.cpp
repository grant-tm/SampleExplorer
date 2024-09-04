#include "ModeSelector.h"

//-----------------------------------------------------------------------------

ModeSelector::ModeSelector(juce::String modeAText, juce::String modeBText)
{
    lookAndFeel = new ModeSelectorLookAndFeel(modeAText, modeBText);
    setLookAndFeel(lookAndFeel);
}

ModeSelector::~ModeSelector()
{
    setLookAndFeel(nullptr);
    delete lookAndFeel;
}