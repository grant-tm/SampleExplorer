#ifndef BPM_FILTER_H
#define BPM_FILTER_H

#include <JuceHeader.h>
#include "../ColorPalette.h"
#include "BpmFilterModeSelector.h"
#include "BpmFilterSlider.h"

//=============================================================================
class BpmFilter : 
    public juce::Component,
    public BpmFilterModeSelector::Listener,
    public juce::Slider::Listener
{
public:
    BpmFilter();
    ~BpmFilter();

    void resized() override;
    void paint(juce::Graphics &g) override;

private:

    juce::Label label = juce::Label("BPM Filter Label", "BPM");
    juce::Label valueDisplay = juce::Label("BPM Filter Value Display", "120");
    
    BpmFilterModeSelector filterModeSelector;
    BpmFilterSlider filterSlider;

    //void labelTextChanged(juce::Label *) override;

    void sliderValueChanged(juce::Slider *) override;

    void updateMode(BpmFilterModeSelector::BpmFilterMode mode)
    {
        filterSlider.switchMode();
        sliderValueChanged(&filterSlider);
    }
};

#endif // BPM_FITER_H
