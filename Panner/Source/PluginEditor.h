/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

#ifndef __JUCE_HEADER_2D04B386A627E93D__
#define __JUCE_HEADER_2D04B386A627E93D__

//[Headers]     -- You can add your own extra header files here --
using namespace std;
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginLookAndFeel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class JuceGainAudioProcessorEditor  : public AudioProcessorEditor,
public Timer,
public juce::Slider::Listener,
                                public juce::ComboBox::Listener
                               //public juce::Button::Listener

{
public:
    //==============================================================================
    JuceGainAudioProcessorEditor (JuceGainAudioProcessor& p);
    ~JuceGainAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    //[/UserMethods]

    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider * sliderThatWasMoved) override;
    void comboBoxChanged(ComboBox * comboBox) override;
    //void buttonClicked(Button * button) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceGainAudioProcessor& processor;

    JuceGainAudioProcessor& getProcessor() const
    {
        return static_cast<JuceGainAudioProcessor&> (processor);
    }

    //PluginLookAndFeel pluginLookAndFeel;
    
    //[/UserVariables]

    //==============================================================================
    Slider gainDbSlider;
    Slider panSlider;
   
    ComboBox convSelector;
    
    Label gainLabel;
    Label panLabel;
    Label convLabel;
    
    //ScopedPointer<ToggleButton> muteONButton;
   //ScopedPointer<ToggleButton> muteOFFButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceGainAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2D04B386A627E93D__
