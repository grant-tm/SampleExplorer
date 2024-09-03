#ifndef BPM_FILTER_SLIDER_H
#define BPM_FILTER_SLIDER_H

#include <JuceHeader.h>
#include "BpmFilterSliderLookAndFeel.h"

class BpmFilterSlider : public juce::Slider, public juce::Slider::Listener
{
public:
	BpmFilterSlider();
	~BpmFilterSlider();

	void switchMode();

private:

	BpmFilterSliderLookAndFeel filterSliderLNF;

	int sliderLowerThumbValue = 90;
	int sliderUpperThumbValue = 160;
	int sliderThumbValue = 120;

	void sliderValueChanged(juce::Slider *) override;

};

#endif // BPM_FILTER_SLIDER_H