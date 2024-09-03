#ifndef BPM_FILTER_H
#define BPM_FILTER_H

#include <JuceHeader.h>
#include "../ColorPalette.h"
#include "BpmFilterModeSelector.h"
#include "BpmFilterSlider.h"

//=============================================================================
class BpmFilter : 
    public juce::Component,
    public BpmFilterModeSelector::Listener
{
public:
    BpmFilter();
    ~BpmFilter();

    void resized() override;
    void paint(juce::Graphics &g) override;

private:
    BpmFilterModeSelector filterModeSelector;
    BpmFilterSlider filterSlider;

    void updateMode(BpmFilterModeSelector::BpmFilterMode mode)
    {
        filterSlider.switchMode();
        if (mode == BpmFilterModeSelector::BpmFilterMode::Exact)
        {
        }
        if (mode == BpmFilterModeSelector::BpmFilterMode::Range)
        {
        }
    }
};

#endif // BPM_FITER_H
