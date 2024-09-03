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

    void sliderValueChanged(juce::Slider *) override;
    void switchMode() override;
};
#endif // BPM_FITER_H