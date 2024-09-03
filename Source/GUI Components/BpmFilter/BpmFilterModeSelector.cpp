#include "BpmFilterModeSelector.h"

//-----------------------------------------------------------------------------

BpmFilterModeSelector::BpmFilterModeSelector() : juce::Component()
{
    addAndMakeVisible(exactToggleButton);
    exactToggleButton.addListener(this);
    exactToggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    exactToggleButton.setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(rangeToggleButton);
    rangeToggleButton.addListener(this);
    rangeToggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    rangeToggleButton.setLookAndFeel(&lookAndFeel);
}

BpmFilterModeSelector::~BpmFilterModeSelector()
{
    exactToggleButton.removeListener(this);
    exactToggleButton.setLookAndFeel(nullptr);

    rangeToggleButton.removeListener(this);
    rangeToggleButton.setLookAndFeel(nullptr);
}

//-----------------------------------------------------------------------------

void BpmFilterModeSelector::resized()
{
    auto bounds = getLocalBounds();

    auto exactBounds = bounds.removeFromLeft(bounds.getWidth() / 2);
    exactToggleButton.setBounds(exactBounds);

    auto rangeBounds = bounds;
    rangeToggleButton.setBounds(rangeBounds);
}

void BpmFilterModeSelector::setListener(BpmFilterModeSelector::Listener *lstner)
{
    this->listener = lstner;
}

void BpmFilterModeSelector::buttonClicked(juce::Button *button)
{
    if (button->getButtonText() == "Exact")
    {
        auto state = exactToggleButton.getToggleState();
        rangeToggleButton.setToggleState(!state, juce::NotificationType::dontSendNotification);
        if (listener)
        {
            auto mode = state ? BpmFilterMode::Range : BpmFilterMode::Exact;
            listener->updateMode(mode);
        }
    }
    if (button->getButtonText() == "Range")
    {
        auto state = rangeToggleButton.getToggleState();
        exactToggleButton.setToggleState(!state, juce::NotificationType::dontSendNotification);
        if (listener)
        {
            auto mode = state ? BpmFilterMode::Exact : BpmFilterMode::Range;
            listener->updateMode(mode);
        }
    }
}