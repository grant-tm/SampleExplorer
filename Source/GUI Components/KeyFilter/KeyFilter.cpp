#include "KeyFilter.h"

KeyFilter::KeyFilter()
{
	juce::FontOptions labelFontOptions(18.f, juce::Font::plain);
	label.setFont(labelFontOptions);
	label.setJustificationType(juce::Justification::centredLeft);
	label.setColour(juce::Label::textColourId, juce::Colour(0xFFD9D9D9));
	addAndMakeVisible(label);
	addAndMakeVisible(keyboard);
	addAndMakeVisible(keyModeSelector);
}

KeyFilter::~KeyFilter(){}

void KeyFilter::resized()
{
	auto bounds = getLocalBounds();

	auto labelBounds = bounds.removeFromTop(30);
	labelBounds.removeFromLeft(4);
	label.setBounds(labelBounds);
	
	auto modeSelectorBounds = bounds.removeFromBottom(30);
	modeSelectorBounds.removeFromLeft(12);
	modeSelectorBounds.removeFromRight(12);
	modeSelectorBounds.removeFromBottom(7);
	keyModeSelector.setBounds(modeSelectorBounds);

	auto keyboardBounds = bounds;
	keyboardBounds.removeFromLeft(14);
	keyboardBounds.removeFromRight(12);
	keyboardBounds.removeFromBottom(7);
	keyboard.setBounds(keyboardBounds);
}

void KeyFilter::paint(juce::Graphics &g)
{
	auto bounds = getLocalBounds();
	g.setColour(GUI_PRIMARY_ELEV1);
	g.fillRoundedRectangle(bounds.toFloat(), 2);
}