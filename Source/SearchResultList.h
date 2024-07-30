#ifndef SEARCH_RESULT_LIST_H
#define SEARCH_RESULT_LIST_H

#include <JuceHeader.h>

class SearchResultListBoxModel : public juce::ListBoxModel
{
public:
    SearchResultListBoxModel(const juce::StringArray &items) : listItems(items) {}

    int getNumRows() override
    {
        return listItems.size();
    }

    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
        {
            g.fillAll(juce::Colours::lightblue);
        }
        g.setColour(juce::Colours::black);
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


private:
    juce::StringArray listItems;
};

#endif SEARCH_RESULT_LIST_H
