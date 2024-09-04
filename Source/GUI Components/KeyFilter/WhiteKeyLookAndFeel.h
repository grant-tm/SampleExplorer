#ifndef WHITE_KEY_LOOK_AND_FEEL_H
#define WHITE_KEY_LOOK_AND_FELL_H

#include <JuceHeader.h>
#include "../ColorPalette.h"

class WhiteKeyLookAndFeel : public juce::LookAndFeel_V4
{
public:
	//WhiteKeyLookAndFeel();
	//~WhiteKeyLookAndFeel();

	void drawToggleButton (juce::Graphics &g,
		juce::ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown);
};

#endif // WHITE_KEY_LOOK_AND_FEEL_H