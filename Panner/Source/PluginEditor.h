/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

#ifndef __JUCE_HEADER_2D04B386A627E93D__
#define __JUCE_HEADER_2D04B386A627E93D__


using namespace std;
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginLookAndFeel.h"


class JuceGainAudioProcessorEditor  : public AudioProcessorEditor,
                                    public juce::Slider::Listener,
                                    public juce::ComboBox::Listener,
                                    public juce::Button::Listener
                                    //public Timer,
{
public:
    //==============================================================================
    JuceGainAudioProcessorEditor (JuceGainAudioProcessor& p);
    ~JuceGainAudioProcessorEditor();

    //==============================================================================
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>> comboboxAttachments;

    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider * slider) override;
    void comboBoxChanged(ComboBox * comboBox) override;
    void buttonClicked(Button * button) override;

    //int convType = 1;
    enum convType { Cab1, Cab2, Cab3, None };

private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceGainAudioProcessor& audioProcessor;

    JuceGainAudioProcessor& getProcessor() const
    {
        return static_cast<JuceGainAudioProcessor&> (audioProcessor);
    }

    //PluginLookAndFeel pluginLookAndFeel;
    
    //[/UserVariables]

    //==============================================================================
    Slider gainDbSlider;
    Slider panKnob;
   
    ComboBox convSelector;
    
    Label gainLabel;
    Label panLabel;
    Label convLabel;
    
    ToggleButton muteButton;
   // ToggleButton muteOFFButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceGainAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2D04B386A627E93D__
