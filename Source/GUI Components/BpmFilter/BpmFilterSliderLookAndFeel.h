#ifndef BPM_FILTER_SLIDER_LOOK_AND_FEEL_H
#define BPM_FILTER_SLIDER_LOOK_AND_FEEL_H

#include <JuceHeader.h>
#include "../ColorPalette.h"

class BpmFilterSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
	void drawLinearSlider(juce::Graphics &, int, int, int, int,
		float, float, float, juce::Slider::SliderStyle, juce::Slider &) override;
};

#endif // BPM_FILTER_SLIDER_LOOK_AND_FEEL_H