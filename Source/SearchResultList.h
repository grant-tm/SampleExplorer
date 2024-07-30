#ifndef SEARCH_RESULT_LIST_H
#define SEARCH_RESULT_LIST_H

#include <JuceHeader.h>
#include "Database.h"
#include "ColorPalette.h"

//=============================================================================
// LOOK AND FEEL

class SearchResultsLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawScrollbar(juce::Graphics &g, juce::ScrollBar &scrollbar,
        int x, int y, int width, int height,
        bool isScrollbarVertical, int thumbStartPosition, int thumbSize,
        bool isMouseOver, bool isMouseDown) override;
};

//=============================================================================
// LIST BOX

class SearchResultsListBox : public juce::ListBox
{
public:
    SearchResultsListBox() = delete;
    SearchResultsListBox(juce::String name);
    ~SearchResultsListBox() override = default;

    juce::String getDraggedItem();

private:
    SearchResultsLookAndFeel lookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SearchResultsListBox)
};

//=============================================================================
// LIST BOX MODEL

class SearchResultsListBoxModel : public juce::ListBoxModel
{
public:
    SearchResultsListBoxModel(Database &db, const juce::StringArray &items);
    
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;

    juce::var getDragSourceDescription(const juce::SparseSet<int> &rowsToDescribe) override;

    void listBoxItemClicked(int row, const juce::MouseEvent &) override;
    void setItems(juce::StringArray stringArray);
    const juce::String getLastItemClicked() const;

private:
    Database &database;
    juce::StringArray listItems;
    juce::String lastItemClicked;
};

#endif SEARCH_RESULT_LIST_H
