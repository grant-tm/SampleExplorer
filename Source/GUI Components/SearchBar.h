#ifndef SEARCH_BAR_H
#define SEARCH_BAR_H

#include <JuceHeader.h>

class SearchBar : public juce::TextEditor
{
public:
	SearchBar();
	~SearchBar() override = default;
};

#endif