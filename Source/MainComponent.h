#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include <JuceHeader.h>
#include "ColorPalette.h"
#include "Database.h"
#include "SearchBar.h"
#include "SearchBarListener.h"
#include "SearchResultList.h"

#define DEFAULT_WIDTH   360
#define DEFAULT_HEIGHT  490

#define MINIMUM_WIDTH   int(DEFAULT_WIDTH * 0.75)
#define MINIMUM_HEIGHT  int(DEFAULT_HEIGHT * 0.75)

#define MAXIMUM_WIDTH   int(DEFAULT_WIDTH * 1.5)
#define MAXIMUM_HEIGHT  int(DEFAULT_HEIGHT * 1.25)

//==============================================================================

class MainComponent  : 
    public juce::Component, 
    public SearchBarListener,
    public juce::DragAndDropContainer
{
public:

    MainComponent();
    ~MainComponent() override;

    Database database;
    juce::StringArray listItems;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    SearchBar searchBar;
    void searchBarTextChanged() override;

    SearchResultsListBoxModel searchResultsListBoxModel;
    SearchResultsListBox searchResultsListBox;

    void dragOperationStarted (const juce::DragAndDropTarget::SourceDetails &) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif // MAIN_COMPONENT_H
