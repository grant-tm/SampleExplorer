#ifndef BPM_FILTER_MODE_SELECTOR_H
#define BPM_FILTER_MODE_SELECTOR_H

#include <JuceHeader.h>
#include "../ColorPalette.h"
#include "BpmFilterModeSelectorLookAndFeel.h"

class BpmFilterModeSelector :
    public juce::Component,
    public juce::Button::Listener
{
public:
    BpmFilterModeSelector();
    ~BpmFilterModeSelector();

    void resized() override;
    void paint(juce::Graphics &g) override {};

private:
    juce::ToggleButton exactToggleButton = juce::ToggleButton("Exact");
    juce::ToggleButton rangeToggleButton = juce::ToggleButton("Range");
    BpmFilterModeSelectorLookAndFeel lookAndFeel;

    void buttonClicked(juce::Button *button) override;
};

#endif // BPM_FILTER_MODE_SELECTOR_H