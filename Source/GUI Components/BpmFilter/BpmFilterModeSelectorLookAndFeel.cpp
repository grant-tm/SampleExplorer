#include "BpmFilterModeSelectorLookAndFeel.h"

void BpmFilterModeSelectorLookAndFeel::drawToggleButton (juce::Graphics &g,
    juce::ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds();

    // draw background
    auto backgroundColor = button.getToggleState() ? juce::Colour(0xFF292929) : GUI_PRIMARY_ELEV3;
    g.setColour(backgroundColor);
    g.fillRoundedRectangle(bounds.toFloat(), 5);

    //draw text
    auto textColor = button.getToggleState() ? juce::Colour(0xFF595959) : juce::Colour(0xFFD9D9D9);
    g.setColour(textColor);

    auto fontSize = juce::jmin(15.0f, button.getHeight() * 0.75f);
    g.setFont(fontSize);

    g.drawFittedText(button.getButtonText(), bounds.toNearestInt(), juce::Justification::centred, 10);
}