#include "BpmFilter.h"

BpmFilter::BpmFilter() : juce::Component()
{
    filterModeSelector.setListener(this);
	addAndMakeVisible(filterModeSelector);
    addAndMakeVisible(filterSlider);
}

BpmFilter::~BpmFilter()
{
    filterModeSelector.setListener(nullptr);
}

void BpmFilter::resized()
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop(bounds.getHeight() / 3);

    auto sliderBounds = bounds.removeFromTop(bounds.getHeight() / 2);
    filterSlider.setBounds(sliderBounds);

    auto modeSelectorBounds = bounds;
    modeSelectorBounds.removeFromBottom(7);
    modeSelectorBounds.removeFromLeft(12);
    modeSelectorBounds.removeFromRight(12);
    filterModeSelector.setBounds(modeSelectorBounds);
}

void BpmFilter::paint(juce::Graphics &g)
{
    g.fillAll(GUI_PRIMARY_ELEV1);
}