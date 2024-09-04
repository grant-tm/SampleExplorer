#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <JuceHeader.h>
#include "WhiteKeyLookAndFeel.h"
#include "BlackKeyLookAndFeel.h"

class Keyboard : public juce::Component
{
public:
	Keyboard();
	~Keyboard();

	void resized() override;

private:
	WhiteKeyLookAndFeel whiteKeyLNF;
	BlackKeyLookAndFeel blackKeyLNF;
	juce::ToggleButton keys[12];
};

#endif // KEYBOARD_H