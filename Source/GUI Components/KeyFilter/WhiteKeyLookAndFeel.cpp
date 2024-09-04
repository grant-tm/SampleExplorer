#include "WhiteKeyLookAndFeel.h"

void WhiteKeyLookAndFeel::drawToggleButton (juce::Graphics &g,
    juce::ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds();

    auto color = button.getToggleState() ? GUI_ACCENT : juce::Colour(0xFFD9D9D9);
    g.setColour(color);
    g.fillRoundedRectangle(bounds.toFloat(), 5);
}