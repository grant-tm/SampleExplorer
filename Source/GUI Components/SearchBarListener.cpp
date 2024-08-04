#include "SearchBarListener.h"

void SearchBarListener::textEditorTextChanged(juce::TextEditor &editor)
{
	startTimer(80); // default debouncee time
	juce::ignoreUnused(editor);
}

void SearchBarListener::timerCallback()
{
	stopTimer();
	searchBarTextChanged();
}

void SearchBarListener::textEditorReturnKeyPressed(juce::TextEditor &editor)
{
	juce::ignoreUnused(editor);
	return; // does nothing... or rescan?
}

void SearchBarListener::textEditorEscapeKeyPressed(juce::TextEditor &editor)
{
	juce::ignoreUnused(editor);
	return;
}

void SearchBarListener::textEditorFocusLost(juce::TextEditor &editor)
{
	juce::ignoreUnused(editor);
	return;
}