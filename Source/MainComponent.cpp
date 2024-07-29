#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
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
}
