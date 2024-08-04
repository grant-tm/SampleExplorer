#include "SearchBar.h"
#include "MainComponent.h"

SearchBar::SearchBar() : juce::TextEditor()
{
    setReadOnly(false);
    setTextToShowWhenEmpty("Search...", SEARCHBAR_UNFOCUSED_TEXT_COLOR);

    // single line
    setMultiLine(false);
    setReturnKeyStartsNewLine(false);
    setScrollbarsShown(false);

    // caret and popup visibility
    setCaretVisible(true);
    setPopupMenuEnabled(false);

    // set keys to ignore
    setTabKeyUsedAsCharacter(false);
    setEscapeAndReturnKeysConsumed(true);
    setEscapeAndReturnKeysConsumed(true);

    // colors
    auto transparent = juce::Colour(0xFFFFFFFF).withAlpha(0.f);
    setColour(juce::TextEditor::ColourIds::outlineColourId, transparent);
    setColour(juce::TextEditor::ColourIds::focusedOutlineColourId, transparent);
    setColour(juce::TextEditor::ColourIds::backgroundColourId, SEARCHBAR_BACKGROUND_COLOR);
    setColour(juce::TextEditor::ColourIds::textColourId, SEARCHBAR_FOCUSED_TEXT_COLOR);
    setColour(juce::TextEditor::ColourIds::highlightColourId, juce::Colours::black);

    // font style and justification
    juce::FontOptions defaultOptions;
    juce::Font font = juce::Font(defaultOptions);
    font.setSizeAndStyle(18, font.getDefaultMonospacedFontName(), 1.f, 0.f);
    setFont(font);
    setJustification(juce::Justification::centredLeft);
}