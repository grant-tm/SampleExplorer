#ifndef BPM_FILTER_H
#define BPM_FILTER_H

#include <JuceHeader.h>
#include "../ColorPalette.h"
#include "BpmFilterModeSelector.h"

//=============================================================================
class BpmFilter : public juce::Component
{
public:
    BpmFilter();

    void resized() override;
    void paint(juce::Graphics &g) override;

private:
    BpmFilterModeSelector filterModeSelector;

};

#endif // BPM_FITER_H
