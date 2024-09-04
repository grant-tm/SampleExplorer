#include "ModeSelectorLookAndFeel.h"

ModeSelectorLookAndFeel::ModeSelectorLookAndFeel(juce::String A, juce::String B)
{
    modeAText = A;
    modeBText = B;
}

void ModeSelectorLookAndFeel::drawToggleButton (juce::Graphics &g,
    juce::ToggleButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    // set button colors
    const auto selectedBackgroundColor   = juce::Colour(0xFF292929);
    const auto deselectedBackgroundColor = GUI_PRIMARY_ELEV3;

    // set text colors
    const auto selectedTextColor   = juce::Colour(0xFFD9D9D9);
    const auto deselectedTextColor = juce::Colour(0xFF595959);

    // set font size
    const auto fontSize = juce::jmin(15.0f, button.getHeight() * 0.75f);
    g.setFont(fontSize);

    // calculate button bounds
    auto bounds = button.getLocalBounds();
    const auto modeABounds = bounds.removeFromLeft(bounds.getWidth() / 2);
    const auto modeBBounds = bounds;
    
    const auto mode = button.getToggleState();

    // draw mode A background
    const auto modeABackgroundColor = mode ? selectedBackgroundColor : deselectedBackgroundColor;
    g.setColour(modeABackgroundColor);
    g.fillRoundedRectangle(modeABounds.toFloat(), 5);
    
    // draw mode A text
    const auto modeATextColor = !mode ? selectedTextColor : deselectedTextColor;
    g.setColour(modeATextColor);
    g.drawFittedText(modeAText, modeABounds, juce::Justification::centred, 10);

    // draw mode B background
    const auto modeBBackgroundColor = !mode ? selectedBackgroundColor : deselectedBackgroundColor;
    g.setColour(modeBBackgroundColor);
    g.fillRoundedRectangle(modeBBounds.toFloat(), 5);

    // draw mode B text
    const auto modeBTextColor = mode ? selectedTextColor : deselectedTextColor;
    g.setColour(modeBTextColor);
    g.drawFittedText(modeBText, modeBBounds, juce::Justification::centred, 10);
}