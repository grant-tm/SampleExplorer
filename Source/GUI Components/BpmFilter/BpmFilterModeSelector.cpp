#include "BpmFilterModeSelector.h"

BpmFilterModeSelector::BpmFilterModeSelector() : juce::Component()
{
    addAndMakeVisible(exactToggleButton);
    exactToggleButton.addListener(this);
    exactToggleButton.setToggleState(false, false);
    exactToggleButton.setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(rangeToggleButton);
    rangeToggleButton.addListener(this);
    rangeToggleButton.setToggleState(true, false);
    rangeToggleButton.setLookAndFeel(&lookAndFeel);
}

BpmFilterModeSelector::~BpmFilterModeSelector()
{
    exactToggleButton.removeListener(this);
    exactToggleButton.setLookAndFeel(nullptr);

    rangeToggleButton.removeListener(this);
    rangeToggleButton.setLookAndFeel(nullptr);
}

void BpmFilterModeSelector::resized()
{
    auto bounds = getLocalBounds();

    auto exactBounds = bounds.removeFromLeft(bounds.getWidth() / 2);
    exactToggleButton.setBounds(exactBounds);

    auto rangeBounds = bounds;
    rangeToggleButton.setBounds(rangeBounds);
}


void BpmFilterModeSelector::buttonClicked(juce::Button *button)
{
    if (button->getButtonText() == "Exact")
    {
        auto state = exactToggleButton.getToggleState();
        rangeToggleButton.setToggleState(!state, false);
    }
    if (button->getButtonText() == "Range")
    {
        auto state = rangeToggleButton.getToggleState();
        exactToggleButton.setToggleState(!state, false);
    }
}