#ifndef KEY_FILTER_H
#define KEY_FILTER_H

#include <JuceHeader.h>
#include "../ColorPalette.h"
#include "../ModeSelector.h"
#include "Keyboard.h"

class KeyFilter : public juce::Component
{
public:
	KeyFilter();
	~KeyFilter();

	void resized() override;
	void paint(juce::Graphics &g) override;

private:
	juce::Label label = juce::Label("Key Filter Label", "Key");
	Keyboard keyboard;
	ModeSelector keyModeSelector = ModeSelector("Major", "Minor");
};

#endif // KEY_FILTER_H