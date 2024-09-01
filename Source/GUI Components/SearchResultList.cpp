#include "SearchResultList.h"

//=============================================================================
// LIST BOX

SearchResultsListBox::SearchResultsListBox(juce::String name) : juce::ListBox(name)
{
    setLookAndFeel(&lookAndFeel);
    setColour(juce::ListBox::backgroundColourId, GUI_PRIMARY_ELEV0);
    setColour(juce::ListBox::outlineColourId, GUI_TEXT_GRAY);
    setColour(juce::ListBox::textColourId, GUI_TEXT_WHITE);
}

//=============================================================================
// LOOK AND FEEL]

void SearchResultsLookAndFeel::drawScrollbar(juce::Graphics &g, juce::ScrollBar &scrollbar,
    int x, int y, int width, int height,
    bool isScrollbarVertical, int thumbStartPosition, int thumbSize,
    bool isMouseOver, bool isMouseDown)
{
    juce::ignoreUnused(scrollbar);
    
    g.fillAll(GUI_PRIMARY_ELEV0);

    if (thumbSize <= 0)
        return;

    juce::Rectangle<int> thumbBounds;
    if (isScrollbarVertical)
        thumbBounds.setBounds(x, thumbStartPosition, width, thumbSize);
    else
        thumbBounds.setBounds(thumbStartPosition, y, thumbSize, height);

    juce::Path roundedRect;
    roundedRect.addRoundedRectangle(thumbBounds, 4.f);

    juce::Colour thumbColour = (isMouseOver || isMouseDown) ? GUI_PRIMARY_ELEV4 : GUI_PRIMARY_ELEV2;
    g.setColour (thumbColour);
    g.fillPath (roundedRect);
}

//=============================================================================
// LIST BOX MODEL

SearchResultsListBoxModel::SearchResultsListBoxModel(Database &db, const juce::StringArray &items)
    : database(db),
    listItems(items)
{
    listItems.clear();
}


int SearchResultsListBoxModel::getNumRows()
{
    return listItems.size();
}

void SearchResultsListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.setColour(GUI_ACCENT);
    else
        g.setColour(GUI_PRIMARY_ELEV1);

    auto rect = juce::Rectangle<float>(0.f, 0.f, (float) width - 6, (float)height * 0.9);
    g.fillRoundedRectangle(rect, 3);

    g.setColour(GUI_TEXT_WHITE);
    g.drawText(listItems[rowNumber], 7, 0, (int) width - 13, height, juce::Justification::centredLeft);
}

void SearchResultsListBoxModel::listBoxItemClicked(int row, const juce::MouseEvent &)
{
    juce::ignoreUnused(row);
}

void SearchResultsListBoxModel::setItems(juce::StringArray stringArray)
{
    listItems = stringArray;
}

juce::var SearchResultsListBoxModel::getDragSourceDescription(const juce::SparseSet<int> &rowsToDescribe)
{
    if (rowsToDescribe.size() == 1)
    {
        int row = rowsToDescribe[0];
        return listItems[row];
    }

    return {};
}

void SearchResultsListBoxModel::selectedRowsChanged(int lastRowSelected)
{
    playSampleFromRow(lastRowSelected);
}

void SearchResultsListBoxModel::playSampleFromRow(int row)
{
    juce::String filePath = database.getPathFromName(listItems[row]);
    juce::File file(filePath);

    if (file.existsAsFile())
    {
        samplePlayer.playSample(file);
    }
}