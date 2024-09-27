#include "BpmFilter.h"

BpmFilter::BpmFilter() : juce::Component()
{
    // main label
    addAndMakeVisible(label);
    label.setJustificationType(juce::Justification::centredLeft);
    label.setColour(juce::Label::textColourId, juce::Colour(0xFFD9D9D9));
    juce::FontOptions labelFontOptions(18.f, juce::Font::plain);
    label.setFont(labelFontOptions);

    // value display
    addAndMakeVisible(valueDisplay);
    valueDisplay.setJustificationType(juce::Justification::centredLeft);
    valueDisplay.setColour(juce::Label::textColourId, juce::Colour(0xFF959595));
    juce::FontOptions valueDisplayFontOptions(16.f, juce::Font::plain);
    valueDisplay.setFont(valueDisplayFontOptions);

    // filter value slider
    filterSlider.addListener(this);
    addAndMakeVisible(filterSlider);

    // filter mode selector buttons
    filterModeSelector.setListener(this);
	addAndMakeVisible(filterModeSelector);
}

BpmFilter::~BpmFilter()
{
    filterModeSelector.setListener(nullptr);
    filterSlider.removeListener(this);
}

void BpmFilter::resized()
{
    auto bounds = getLocalBounds();
    auto headerBounds = bounds.removeFromTop((bounds.getHeight() / 3));
    headerBounds.removeFromLeft(4);
    
    // main label
    auto font = label.getFont();
    auto labelBounds = headerBounds.removeFromLeft(40);
    label.setBounds(labelBounds);

    // value section
    auto valueBounds = headerBounds;
    valueDisplay.setBounds(valueBounds);

    // filter slider
    auto sliderBounds = bounds.removeFromTop(bounds.getHeight() / 2);
    filterSlider.setBounds(sliderBounds);

    // filter mode selector buttons
    auto modeSelectorBounds = bounds;
    modeSelectorBounds.removeFromBottom(7);
    modeSelectorBounds.removeFromLeft(12);
    modeSelectorBounds.removeFromRight(12);
    filterModeSelector.setBounds(modeSelectorBounds);
}

void BpmFilter::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    g.setColour(GUI_PRIMARY_ELEV1);
    g.fillRoundedRectangle(bounds.toFloat(), 2);
}

void BpmFilter::sliderValueChanged(juce::Slider *slider)
{
    if (slider->getSliderStyle() == juce::Slider::SliderStyle::LinearHorizontal)
    {
        const juce::String exactValue = juce::String(filterSlider.getValue());
        valueDisplay.setText(exactValue, juce::NotificationType::dontSendNotification);
    }
    if (slider->getSliderStyle() == juce::Slider::SliderStyle::TwoValueHorizontal)
    {
        const juce::String minValue = juce::String(filterSlider.getMinValue());
        const juce::String maxValue = juce::String(filterSlider.getMaxValue());
        const juce::String fullString = minValue + "-" + maxValue;
        valueDisplay.setText(fullString, juce::NotificationType::dontSendNotification);
    }
    resized();
}

void BpmFilter::switchMode()
{
    filterSlider.switchMode();
    sliderValueChanged(&filterSlider);
}