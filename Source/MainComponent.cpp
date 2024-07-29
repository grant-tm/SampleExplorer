#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setWantsKeyboardFocus(true);
    addAndMakeVisible(searchBar);
}

MainComponent::~MainComponent()
{
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
}
