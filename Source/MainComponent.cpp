#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : searchResultsListBox("ListBox"), searchResultsListBoxModel(database, listItems) 
{
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setWantsKeyboardFocus(true);

    juce::String directory("D:/Samples/");
    database.scanDirectory(directory);

    addAndMakeVisible(searchResultsListBox);
    searchResultsListBox.setModel(&searchResultsListBoxModel);

    searchBar.addListener(this);
    addAndMakeVisible(searchBar);
}

MainComponent::~MainComponent()
{
    searchResultsListBox.setModel(nullptr);
    searchResultsListBox.setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(GUI_PRIMARY_ELEV0);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    
    auto searchBarBounds = bounds;
    searchBarBounds.removeFromTop(7);
    searchBarBounds.removeFromLeft(7);
    searchBarBounds.removeFromRight(7);
    searchBarBounds = searchBarBounds.removeFromTop(28);
    searchBar.setBounds(searchBarBounds);

    auto searchResultsBounds = bounds;
    searchResultsBounds.removeFromTop(28 + 7 + 7);
    searchResultsBounds.removeFromLeft(7);
    searchResultsBounds.removeFromRight(7);
    searchResultsBounds.removeFromBottom(7);
    searchResultsListBox.setBounds(searchResultsBounds);
}


//==============================================================================
void MainComponent::searchBarTextChanged()
{
    const juce::String query = searchBar.getText();
    juce::Array<DatabaseRecord> searchResultRecords = database.searchByName(query);

    // add files not contained
    listItems.clear();
    for (const auto &record : searchResultRecords)
    {
        listItems.add(record.fileName);
    }

    searchResultsListBoxModel.setItems(listItems);
    searchResultsListBox.updateContent();
}

void MainComponent::dragOperationStarted(const juce::DragAndDropTarget::SourceDetails &source)
{
    auto fileName = source.description.toString();
    juce::StringArray filesToDrag;
    filesToDrag.add(database.getPathFromName(fileName));
    performExternalDragDropOfFiles(filesToDrag, true);
}