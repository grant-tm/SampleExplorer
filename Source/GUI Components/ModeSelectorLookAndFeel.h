#ifndef MODE_SELECTOR_LOOK_AND_FEEL_H
#define MODE_SELECTOR_LOOK_AND_FEEL_H

#include <JuceHeader.h>
#include "ColorPalette.h"

class ModeSelectorLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ModeSelectorLookAndFeel(juce::String, juce::String);
    void drawToggleButton (juce::Graphics &g, juce::ToggleButton &button,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
private:
    juce::String modeAText;
    juce::String modeBText;
};

#endif // MODE_SELECTOR_LOOK_AND_FEEL_H