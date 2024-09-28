#include "KeywordFilter.h"

KeywordFilter::KeywordFilter() : juce::Button::Listener()
{
    addAndMakeVisible(label);
    label.setJustificationType(juce::Justification::centredLeft);
    label.setColour(juce::Label::textColourId, juce::Colour(0xFFD9D9D9));
    juce::FontOptions labelFontOptions(18.f, juce::Font::plain);
    label.setFont(labelFontOptions);

    for (auto &button : buttons)
    {
        button.addListener(this);
        button.setLookAndFeel(&lnf);
    }
}

KeywordFilter::~KeywordFilter()
{
    for (auto &button : buttons)
    {
        button.removeListener(this);
        button.setLookAndFeel(nullptr);
    }
}

void KeywordFilter::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromLeft(4);
    bounds.removeFromRight(4);

    auto labelBounds = bounds.removeFromTop(30);
    label.setBounds(labelBounds);

    renderButtons();
    for (auto &button : buttons)
    {
        if (button.getButtonText() != "")
        {
            DBG(button.getButtonText().toStdString());
            addAndMakeVisible(button);
        }
    }
}

void KeywordFilter::paint(juce::Graphics &g)
{
	auto bounds = getLocalBounds();
	g.setColour(GUI_PRIMARY_ELEV1);
	g.fillRoundedRectangle(bounds.toFloat(), 2);
}

juce::StringArray KeywordFilter::splitStringByDelimiters(const juce::String &str)
{
    juce::StringArray tokens;
    tokens.addTokens(str, " -_.0123456789", "\"");
    tokens.trim();
    tokens.removeEmptyStrings();

    for (auto &token : tokens)
        token = token.toUpperCase();

    for (int i = tokens.size()-1; i >= 0; i--)
    {
        if (tokens[i].length() < 3 ||
            tokens[i] == "BPM" ||
            tokens[i] == "WAV" ||
            tokens[i] == "MP3" ||
            tokens[i] == "FLAC" ||
            tokens[i] == "AIFF")
        {
            tokens.remove(i);
        }
    }

    return tokens;
}

void KeywordFilter::getMostCommonKeywords(const juce::StringArray &filenames)
{
    // pair keywords to frequency
    std::unordered_map<juce::String, int> tokenFrequency;
    for (const auto &filename : filenames)
    {
        juce::StringArray tokens = splitStringByDelimiters(filename);
        for (const auto &token : tokens)
            tokenFrequency[token]++;
    }

    // sort keywords by frequency
    std::vector<std::pair<juce::String, int>> frequencyList(tokenFrequency.begin(), tokenFrequency.end());
    std::sort(frequencyList.begin(), frequencyList.end(),
        [](const std::pair<juce::String, int> &a, const std::pair<juce::String, int> &b) {
            return b.second < a.second;
        });

    keywords = frequencyList;
}

void KeywordFilter::renderButtons()
{
    // reset buttons
    for (auto &button : buttons)
    {
        if (button.getToggleState() == false)
            button.setButtonText("");
    }

    // font setup
    juce::FontOptions options(7);
    juce::Font newFont(options);
    newFont.setTypefaceName(juce::Font::getDefaultMonospacedFontName());

    // constants and trackers
    int maxWidth = getLocalBounds().getWidth() - 8;
    int maxRows = (getLocalBounds().getHeight() - 47) / (newFont.getHeight() * 1.1);
    int curRow = 0;
    int curWidth = 0;
    int curButton = 0;
        
    auto bounds = getLocalBounds();
    bounds.removeFromTop(34);
    bounds.removeFromBottom(7);
    bounds.removeFromLeft(4);
    bounds.removeFromRight(4);


    juce::StringArray savedKeywords;
    for (auto &button : buttons)
    {
        if (button.getToggleState() == false)
            continue;

        // calculate button position to pack rows
        auto text = button.getButtonText();
        savedKeywords.add(text);
        
        auto textWidth = (newFont.getStringWidth(text) * 2.5) + 12;
        auto textHeight = newFont.getHeight();

        if (curWidth + textWidth > maxWidth)
        {
            curRow++;
            if (curRow >= maxRows)
                return;
            curWidth = 0;
        }

        auto x = bounds.getX() + curWidth;
        auto y = bounds.getY() + ((4 * textHeight) * curRow);
        auto w = textWidth;
        auto h = textHeight * 3.f;
        button.setBounds(x, y, w, h);

        // advance "cursor" along horizontal line of buttons
        curWidth += textWidth + 5;
    }

    for (const auto &wordFreqPair : keywords)
    {
        // unpack pair into keyword and frequency
        auto text = wordFreqPair.first;
        if (savedKeywords.contains(text))
            continue;
        auto frequency = wordFreqPair.second;

        // check if there is an untoggled button available
        if (curButton >= KEYWORD_FILTER_MAX_BUTTONS)
            return;
        while(buttons[curButton].getToggleState() == true)
        {
            if (++curButton >= KEYWORD_FILTER_MAX_BUTTONS)
                return;
        }

        // set keyword as button text if keyword appears in search results at least 3 times
        if (frequency < 3)
            continue;
        buttons[curButton].setButtonText(text);

        // calculate button position to pack rows
        auto textWidth = (newFont.getStringWidth(text) * 2.5) + 12;
        auto textHeight = newFont.getHeight();

        if (curWidth + textWidth > maxWidth)
        {
            curRow++;
            if (curRow >= maxRows)
                return;
            curWidth = 0;
        }

        auto x = bounds.getX() + curWidth;
        auto y = bounds.getY() + ((4 * textHeight) * curRow);
        auto w = textWidth;
        auto h = textHeight * 3.f;
        buttons[curButton].setBounds(x, y, w, h);
        
        // advance "cursor" along horizontal line of buttons
        curWidth += textWidth + 5;
        curButton++;
    }
}

void KeywordFilter::buttonStateChanged(juce::Button *button)
{
    resized();
}