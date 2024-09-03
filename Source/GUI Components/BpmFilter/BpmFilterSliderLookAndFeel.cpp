#include "BpmFilterSliderLookAndFeel.h"

void BpmFilterSliderLookAndFeel::drawLinearSlider (juce::Graphics &g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle style, juce::Slider &slider)
{
    const auto trackHeight = 8;
    const auto trackY = y + (height / 2) - (trackHeight/2);

    // draw unhighlighted track
    g.setColour(GUI_PRIMARY_ELEV0);
    juce::Rectangle<float> unhighlightedTrack(x, trackY, width, trackHeight);
    g.fillRoundedRectangle(unhighlightedTrack, 4);
    
    g.setColour(GUI_ACCENT);

    // draw highlight and thumb for linear horizontal style
    if (slider.getSliderStyle() == juce::Slider::SliderStyle::LinearHorizontal)
    {
        // draw highlighted track
        auto limX = juce::jmin(sliderPos, (float) width);
        juce::Rectangle<float> highlightedTrack(x, trackY, limX, trackHeight);
        g.fillRoundedRectangle(highlightedTrack, 4);

        // draw thumb
        g.fillEllipse(limX, y + 10, 12, 12);
    }

    // draw highlight and thumbs for two value horizontal style
    if (slider.getSliderStyle() == juce::Slider::SliderStyle::TwoValueHorizontal)
    {
        // draw highlighted track
        auto limX = juce::jmin(maxSliderPos, (float) width);
        juce::Rectangle<float> highlightedTrack(minSliderPos, trackY, limX - minSliderPos + 6, trackHeight);
        g.fillRoundedRectangle(highlightedTrack, 4);

        // draw thumb
        g.fillEllipse(minSliderPos, y + 10, 12, 12);
        g.fillEllipse(limX, y + 10, 12, 12);
    }
}