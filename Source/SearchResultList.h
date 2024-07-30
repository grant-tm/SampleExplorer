#ifndef SEARCH_RESULT_LIST_H
#define SEARCH_RESULT_LIST_H

#include <JuceHeader.h>

#ifndef MORTCOLORS
    #define GUI_ACCENT          juce::Colour(0xFFFF0000)

    #define GUI_PRIMARY_ELEV0   juce::Colour(0xFF111111)
    #define GUI_PRIMARY_ELEV1   juce::Colour(0xFF222222)
    #define GUI_PRIMARY_ELEV2   juce::Colour(0xFF333333)
    #define GUI_PRIMARY_ELEV3   juce::Colour(0xFF444444)

    #define GUI_TEXT_WHITE      juce::Colour(0xFFE3E3E3)
    #define GUI_TEXT_GRAY       juce::Colour(0xFF959595)
#endif

class SearchResultsLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawScrollbar(juce::Graphics &g, juce::ScrollBar &scrollbar, 
        int x, int y, int width, int height,
        bool isScrollbarVertical, int thumbStartPosition, int thumbSize,
        bool isMouseOver, bool isMouseDown) override
    {
        // set the color for the scroll bar background
        g.fillAll(GUI_PRIMARY_ELEV0);

        // set the color for the scroll bar thumb
        juce::Colour thumbColour = isMouseOver ? GUI_ACCENT : GUI_PRIMARY_ELEV1;
        if (thumbSize > 0)
        {
            juce::Rectangle<int> thumbBounds;

            if (isScrollbarVertical)
                thumbBounds.setBounds (x, thumbStartPosition, width, thumbSize);
            else
                thumbBounds.setBounds (thumbStartPosition, y, thumbSize, height);

            g.setColour (thumbColour);
            g.fillRect (thumbBounds);
        }
    }
};

class SearchResultsListBox : public juce::ListBox
{
public:
    SearchResultsListBox() = delete;
    SearchResultsListBox(juce::String name) : juce::ListBox(name)
    {
        setLookAndFeel(&lookAndFeel);
        
        // Set the background color
        setColour(juce::ListBox::backgroundColourId, GUI_PRIMARY_ELEV0);

        // Set the outline color
        setColour(juce::ListBox::outlineColourId, GUI_TEXT_GRAY);

        // Set the text color
        setColour(juce::ListBox::textColourId, GUI_TEXT_WHITE);
    }

    ~SearchResultsListBox() override = default;

private:
    SearchResultsLookAndFeel lookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SearchResultsListBox)
};

class SearchResultsListBoxModel : public juce::ListBoxModel
{
public:
    SearchResultsListBoxModel(const juce::StringArray &items) : listItems(items) 
    {
    }

    int getNumRows() override
    {
        return listItems.size();
    }

    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
        {
            g.fillAll(GUI_ACCENT);
        }
        g.setColour(GUI_TEXT_WHITE);
        g.drawText(listItems[rowNumber], 0, 0, width, height, juce::Justification::centredLeft);
    }

    void listBoxItemClicked(int row, const juce::MouseEvent &) override
    {
        DBG("Item clicked: " << listItems[row]);
    }

    void setItems(juce::StringArray stringArray)
    {
        listItems = stringArray;
    }

    juce::StringArray listItems;
private:
    
};

#endif SEARCH_RESULT_LIST_H
