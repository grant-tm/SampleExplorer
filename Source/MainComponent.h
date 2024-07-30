#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include <JuceHeader.h>
#include "Database.h"
#include "SearchBar.h"
#include "SearchResultList.h"

// Size Constants

#define DEFAULT_WIDTH   360
#define DEFAULT_HEIGHT  490

#define MINIMUM_WIDTH   int(DEFAULT_WIDTH * 0.75)
#define MINIMUM_HEIGHT  int(DEFAULT_HEIGHT * 0.75)

#define MAXIMUM_WIDTH   int(DEFAULT_WIDTH * 1.5)
#define MAXIMUM_HEIGHT  int(DEFAULT_HEIGHT * 1.25)

// Color Constants

#ifndef MORTCOLORS
    #define GUI_ACCENT          juce::Colour(0xFFFF0000)

    #define GUI_PRIMARY_ELEV0   juce::Colour(0xFF111111)
    #define GUI_PRIMARY_ELEV1   juce::Colour(0xFF222222)
    #define GUI_PRIMARY_ELEV2   juce::Colour(0xFF333333)
    #define GUI_PRIMARY_ELEV3   juce::Colour(0xFF444444)

    #define GUI_TEXT_WHITE      juce::Colour(0xFFE3E3E3)
    #define GUI_TEXT_GRAY       juce::Colour(0xFF959595)
#endif

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::TextEditor::Listener, public juce::Timer
{
public:
    //=========================================================================
    MainComponent();
    ~MainComponent() override;

    Database database;
    juce::StringArray listItems;

    //=========================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //=========================================================================
    // Your private member variables go here...
    SearchBar searchBar;

    SearchResultsListBoxModel searchResultsListBoxModel {listItems};
    SearchResultsListBox searchResultsListBox;

    void textEditorTextChanged(juce::TextEditor &editor) override
    {
        startTimer(100);
        /*searchResultsListBoxModel.setItems(listItems);*/
        //searchResultsListBox.updateContent();
    }

    void timerCallback() override
    {
        stopTimer();

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

    void textEditorReturnKeyPressed(juce::TextEditor &editor) override
    {
        return; // does nothing... or rescan?
    }

    void textEditorEscapeKeyPressed(juce::TextEditor &editor) override
    {
        return;
    }

    void textEditorFocusLost(juce::TextEditor &editor) override
    {
        return;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif // MAIN_COMPONENT_H
