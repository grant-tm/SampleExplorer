#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (auto& key : keys)
		addAndMakeVisible(key);
	
	for (int i = 0; i < 7; i++)
		keys[i].setLookAndFeel(&whiteKeyLNF);

	for (int i = 7; i < 12; i++)
		keys[i].setLookAndFeel(&blackKeyLNF);
}

Keyboard::~Keyboard() {}

void Keyboard::resized()
{
	auto bounds = getLocalBounds();

	auto whiteKeyWidth = (bounds.getWidth() / 7);
	for (int i=0; i<7; i++)
	{
		auto startX = bounds.getX() + (i * whiteKeyWidth);
		juce::Rectangle<int> keyBounds(startX, bounds.getY(), whiteKeyWidth, bounds.getHeight());
		keys[i].setBounds(keyBounds);
	}

	auto blackKeyWidth = (int) (whiteKeyWidth * 0.66);
	for (int i = 7; i < 12; i++)
	{
		auto whiteKeyOffset = (i > 9) ? i - 5 : i - 6;
		auto startX = bounds.getX() + (whiteKeyOffset * whiteKeyWidth) - (blackKeyWidth / 2);
		juce::Rectangle<int> keyBounds(startX, bounds.getY() - 30, blackKeyWidth, bounds.getHeight());
		keys[i].setBounds(keyBounds);
	}
}