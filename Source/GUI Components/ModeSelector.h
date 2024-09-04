#ifndef MODE_SELECTOR_H
#define MODE_SELECTOR_H

#include <JuceHeader.h>
#include "ColorPalette.h"
#include "ModeSelectorLookAndFeel.h"

class ModeSelector : public juce::ToggleButton
{
public:
    ModeSelector(juce::String, juce::String);
    ~ModeSelector();
private:
    ModeSelectorLookAndFeel *lookAndFeel = nullptr;
};

#endif // MODE_SELECTOR_H