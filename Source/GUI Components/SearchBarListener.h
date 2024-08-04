#ifndef SEARCH_BAR_LISTENER_H
#define SEARCH_BAR_LISTENER_H

#include <JuceHeader.h>
#include "SearchBar.h"

class SearchBarListener : public juce::TextEditor::Listener, public juce::Timer
{
public:
	virtual void searchBarTextChanged() = 0;

	void timerCallback() override;

	void textEditorTextChanged(juce::TextEditor &editor) override;
	void textEditorReturnKeyPressed(juce::TextEditor &editor) override;
	void textEditorEscapeKeyPressed(juce::TextEditor &editor) override;
	void textEditorFocusLost(juce::TextEditor &editor) override;
};

#endif // SEARCH_BAR_LISTENER_H