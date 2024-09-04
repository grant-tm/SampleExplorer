#ifndef BLACK_KEY_LOOK_AND_FEEL_H
#define BLACK_KEY_LOOK_AND_FEEL_H

#include <JuceHeader.h>
#include "../ColorPalette.h"

class BlackKeyLookAndFeel : public juce::LookAndFeel_V4
{
public:
	void BlackKeyLookAndFeel::drawToggleButton (juce::Graphics &g,
		juce::ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
};

#endif // BLACK_KEY_LOOK_AND_FEEL_H
