#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : 
    searchResultsListBox("ListBox"), 
    searchResultsListBoxModel(database, listItems) 
{
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setWantsKeyboardFocus(true);

    juce::String directory("D:/Samples/");
    database.scanDirectory(directory);

    addAndMakeVisible(searchResultsListBox);
    searchResultsListBox.setModel(&searchResultsListBoxModel);

    searchBar.addListener(this);
    searchBarTextChanged();
    addAndMakeVisible(searchBar);

    filterPaneToggleButton.addListener(this);
    addAndMakeVisible(filterPaneToggleButton);

    addAndMakeVisible(bpmFilter);
}

MainComponent::~MainComponent()
{
    searchResultsListBox.setModel(nullptr);
    searchResultsListBox.setLookAndFeel(nullptr);

    searchBar.removeListener(this);

    filterPaneToggleButton.removeListener(this);
}

void MainComponent::setListener(MainComponent::Listener *lstner)
{
    this->listener = lstner;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(GUI_PRIMARY_ELEV0);

    if (filterPaneToggleButton.getToggleState() == true)
    {
        g.setColour(GUI_PRIMARY_ELEV1);
        g.fillRect(keyFilterPane);
        g.fillRect(tagFilterPane);
    }
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    
    if (filterPaneToggleButton.getToggleState() == true)
    {
        auto filterSettingsBounds = bounds.removeFromRight(FILTER_PANE_WIDTH);
        filterSettingsBounds.removeFromTop(7);
        filterSettingsBounds.removeFromRight(7);

        auto keyFilterPaneBounds = filterSettingsBounds.removeFromTop(100);
        keyFilterPane = keyFilterPaneBounds;

        filterSettingsBounds.removeFromTop(7);

        auto bpmFilterBounds = filterSettingsBounds.removeFromTop(100);
        bpmFilter.setBounds(bpmFilterBounds);

        filterSettingsBounds.removeFromTop(7);
        
        auto tagFilterPaneBounds = filterSettingsBounds;
        tagFilterPane = tagFilterPaneBounds;
    }

    auto searchBarBounds = bounds;
    searchBarBounds.removeFromTop(7);
    searchBarBounds.removeFromLeft(7);
    searchBarBounds.removeFromRight(7);
    searchBarBounds = searchBarBounds.removeFromTop(28);

    filterPaneToggleButton.setBounds(searchBarBounds.removeFromRight(21));
    searchBarBounds.removeFromRight(4);
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
        listItems.add(record.fileName);

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

void MainComponent::buttonClicked(juce::Button *button)
{
    auto buttonID = button->getButtonText();
    
    if (buttonID == "Filter Pane Toggle")
    {
        auto bounds = getLocalBounds();
        if (button->getToggleState() == true)
        {
            if (listener)
            {
                listener->updateWindowResizeLimits(
                    MINIMUM_WIDTH + FILTER_PANE_WIDTH,
                    MINIMUM_HEIGHT,
                    MAXIMUM_WIDTH + FILTER_PANE_WIDTH,
                    MAXIMUM_HEIGHT
                );
            }
            auto newWidth = bounds.getWidth() + FILTER_PANE_WIDTH;
            setSize(newWidth, bounds.getHeight()); 
        }
        else
        {
            if (listener)
            {
                listener->updateWindowResizeLimits(
                    MINIMUM_WIDTH,
                    MINIMUM_HEIGHT,
                    MAXIMUM_WIDTH,
                    MAXIMUM_HEIGHT
                );
            }
            auto newWidth = bounds.getWidth() - FILTER_PANE_WIDTH;
            setSize(newWidth, bounds.getHeight());
        }
    }
}