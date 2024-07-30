#include <JuceHeader.h>
#include "MainComponent.h"
#include "Database.h"

class SampleExplorerApplication  : public juce::JUCEApplication
{
public:

    SampleExplorerApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return false; }

    void initialise (const juce::String& commandLine) override
    {
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        mainWindow = nullptr; // (deletes our window)
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override {}

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow, public juce::KeyListener
    {
    public:
        MainWindow (juce::String name) : 
            DocumentWindow (name,
            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
            DocumentWindow::closeButton | DocumentWindow::minimiseButton)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

            #if JUCE_IOS || JUCE_ANDROID
                setFullScreen (true);
            #else
                setResizable (true, true);
                setResizeLimits(MINIMUM_WIDTH, MINIMUM_HEIGHT, MAXIMUM_WIDTH, MAXIMUM_HEIGHT);
                centreWithSize (getWidth(), getHeight());
            #endif

            setVisible (true);
            getTopLevelComponent()->addKeyListener(this);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        bool keyPressed (const juce::KeyPress &key, Component *originatingComponent) override
        {
            if (key == juce::KeyPress::escapeKey)
            {
                quit();
            }
            return true;
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (SampleExplorerApplication)
