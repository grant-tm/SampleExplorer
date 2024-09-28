#ifndef KEYWORD_FILTER_H
#define KEYWORD_FILTER_H

#include <JuceHeader.h>
#include "../ColorPalette.h"

#define KEYWORD_FILTER_MAX_BUTTONS 25

class KeywordToggleLNF : public juce::LookAndFeel_V4
{
public:
    void drawToggleButton(juce::Graphics &g, juce::ToggleButton &button,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto bounds = button.getLocalBounds().toFloat();

        juce::Colour baseColour = button.getToggleState() ? GUI_ACCENT : GUI_PRIMARY_ELEV2;
        g.setColour(baseColour);
        g.fillRoundedRectangle(bounds, 4.f);

        juce::Colour textColour = button.getToggleState() ? GUI_TEXT_WHITE : juce::Colour(0xFF959595);
        g.setColour(textColour);
        g.setFont(juce::Font(16.0f, juce::Font::bold));
        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, true);
    }
};

//=============================================================================
class KeywordFilter : 
    public juce::Component,
    public juce::Button::Listener
{
public:
    KeywordFilter();
    ~KeywordFilter();

    void resized() override;
    void paint(juce::Graphics &g) override;

    void setItems(juce::StringArray items)
    {
        listItems = items;
        getMostCommonKeywords(items);
        resized();
    }

    void buttonClicked(juce::Button *) override {}
    void buttonStateChanged(juce::Button *) override;
    void renderButtons();

private:
    juce::Label label = juce::Label("Keyword Filter Label", "Keywords");
    
    juce::StringArray listItems;
    juce::StringArray selectedItems;
    juce::StringArray savedKeywords;
    std::vector<std::pair<juce::String, int>> keywords;
    juce::ToggleButton buttons[KEYWORD_FILTER_MAX_BUTTONS];
    KeywordToggleLNF lnf;

    juce::StringArray KeywordFilter::splitStringByDelimiters(const juce::String &str);
    void KeywordFilter::getMostCommonKeywords(const juce::StringArray &filenames);
};



#endif // KEYWORD_FILTER_H