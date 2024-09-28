#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include <JuceHeader.h>

#include "Database/Database.h"

#include "GUI Components/ColorPalette.h"
#include "GUI Components/SearchBar.h"
#include "GUI Components/SearchBarListener.h"
#include "GUI Components/SearchResultList.h"

#include "GUI Components/KeyFilter/KeyFilter.h"
#include "GUI Components/BpmFilter/BpmFilter.h"
#include "GUI Components/KeywordFilter/KeywordFilter.h"

#define DEFAULT_WIDTH   360
#define DEFAULT_HEIGHT  490

#define MINIMUM_WIDTH   int(DEFAULT_WIDTH * 0.75)
#define MINIMUM_HEIGHT  int(DEFAULT_HEIGHT * 0.75)

#define MAXIMUM_WIDTH   int(DEFAULT_WIDTH * 1.5)
#define MAXIMUM_HEIGHT  int(DEFAULT_HEIGHT * 1.25)

#define FILTER_PANE_WIDTH int(MINIMUM_WIDTH * 0.75)

//==============================================================================

class MainComponent  : 
    public juce::Component, 
    public SearchBarListener,
    public juce::DragAndDropContainer,
    public juce::Button::Listener
{
public:

    MainComponent();
    ~MainComponent() override;

    Database database;
    juce::StringArray listItems;

    void paint (juce::Graphics&) override;
    void resized() override;

    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void updateWindowResizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight) = 0;
    };
    void setListener(Listener *);

private:

    Listener *listener = nullptr;

    // Search bar
    SearchBar searchBar;
    void searchBarTextChanged() override;

    // Item List
    SearchResultsListBoxModel searchResultsListBoxModel;
    SearchResultsListBox searchResultsListBox;

    // Filter Pane Toggle
    juce::ToggleButton filterPaneToggleButton = juce::ToggleButton("Filter Pane Toggle");
    void buttonClicked(juce::Button *button) override;

    KeyFilter keyFilter;
    BpmFilter bpmFilter;
    KeywordFilter keywordFilter;

    // Tag Filter
    juce::Rectangle<int> tagFilterPane;

    void dragOperationStarted (const juce::DragAndDropTarget::SourceDetails &) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif // MAIN_COMPONENT_H
