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
    void paint(juce::Graphics &g) override { juce::ignoreUnused(g); }

    enum BpmFilterMode
    {
        Exact,
        Range
    };

    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void switchMode() = 0;
    };
    void setListener(BpmFilterModeSelector::Listener *);

private:
    juce::ToggleButton exactToggleButton = juce::ToggleButton("Exact");
    juce::ToggleButton rangeToggleButton = juce::ToggleButton("Range");
    BpmFilterModeSelectorLookAndFeel lookAndFeel;

    BpmFilterModeSelector::Listener *listener = nullptr;

    void buttonClicked(juce::Button *button) override;
};

#endif // BPM_FILTER_MODE_SELECTOR_H