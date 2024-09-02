#ifndef BPM_FILTER_MODE_SELECTOR_LNF_H
#define BPM_FILTER_MODE_SELECTOR_LNF_H

#include <JuceHeader.h>
#include "../ColorPalette.h"

class BpmFilterModeSelectorLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawToggleButton (juce::Graphics &g, juce::ToggleButton &button,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};

#endif // BPM_FILTER_MODE_SELECTOR_LNF_H