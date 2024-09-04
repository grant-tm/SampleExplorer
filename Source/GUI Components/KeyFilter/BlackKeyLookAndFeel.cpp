#include "BlackKeyLookAndFeel.h"

void BlackKeyLookAndFeel::drawToggleButton (juce::Graphics &g,
    juce::ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds();

    auto color = button.getToggleState() ? juce::Colour(0xFF0066CC) : juce::Colour(0xFF090909);
    g.setColour(color);
    g.fillRoundedRectangle(bounds.toFloat(), 5);
}