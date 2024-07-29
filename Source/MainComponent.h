#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include <JuceHeader.h>

// Size Constants

#define DEFAULT_WIDTH   475
#define DEFAULT_HEIGHT  650

#define MINIMUM_WIDTH   int(DEFAULT_WIDTH * 0.5)
#define MINIMUM_HEIGHT  int(DEFAULT_HEIGHT * 0.5)

#define MAXIMUM_WIDTH   int(DEFAULT_WIDTH * 1.5)
#define MAXIMUM_HEIGHT  int(DEFAULT_HEIGHT * 1.5)

// Color Constants

#define GUI_PRIMARY_ELEV0   juce::Colour(0xFF111111)
#define GUI_PRIMARY_ELEV1   juce::Colour(0xFF222222)
#define GUI_PRIMARY_ELEV2   juce::Colour(0xFF333333)
#define GUI_PRIMARY_ELEV3   juce::Colour(0xFF444444)

#define GUI_TEXT_WHITE      juce::Colour(0xFFE3E3E3)
#define GUI_TEXT_GRAY       juce::Colour(0xFF959595)

#define GUI_SEARCH_BAR_BG   juce::Colour(0xFFE3E3E3)
#define GUI_SEARCH_BAR_TXT  juce::Colour(0xFF828282)

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif // MAIN_COMPONENT_H
