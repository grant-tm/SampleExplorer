#ifndef SEARCH_BAR_H
#define SEARCH_BAR_H

#include <JuceHeader.h>

#define SEARCHBAR_BACKGROUND_COLOR   juce::Colour(0xFFE3E3E3)
#define SEARCHBAR_UNFOCUSED_TEXT_COLOR  juce::Colour(0xFF828282)
#define SEARCHBAR_FOCUSED_TEXT_COLOR juce::Colour(0xFF111111)

class SearchBar : public juce::TextEditor
{
public:
	SearchBar();
	~SearchBar() override = default;
private:
};

#endif