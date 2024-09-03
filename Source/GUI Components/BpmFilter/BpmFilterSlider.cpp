#include "BpmFilterSlider.h"

//-----------------------------------------------------------------------------

BpmFilterSlider::BpmFilterSlider() : juce::Slider()
{
	setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	setLookAndFeel(&filterSliderLNF);
	addListener(this);
	
	setRange(60.0, 200.0, 1.0);
	setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	setValue(120.0);
}

BpmFilterSlider::~BpmFilterSlider()
{
	setLookAndFeel(nullptr);
	removeListener(this);
}

//-----------------------------------------------------------------------------

void BpmFilterSlider::switchMode()
{
	if (getSliderStyle() == juce::Slider::SliderStyle::LinearHorizontal)
	{
		setSliderStyle(juce::Slider::SliderStyle::TwoValueHorizontal);
		setMinAndMaxValues(sliderLowerThumbValue, sliderUpperThumbValue);
	}
	else
	{
		setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		setValue(sliderThumbValue);
	}
}

void BpmFilterSlider::sliderValueChanged(juce::Slider *slider)
{
	auto sliderStyle = slider->getSliderStyle();

	if (sliderStyle == juce::Slider::SliderStyle::LinearHorizontal)
	{
		sliderThumbValue = (int) slider->getValue();
	}
	if (sliderStyle == juce::Slider::SliderStyle::TwoValueHorizontal)
	{
		sliderLowerThumbValue = (int) slider->getMinValue();
		sliderUpperThumbValue = (int) slider->getMaxValue();
	}
	resized();
}