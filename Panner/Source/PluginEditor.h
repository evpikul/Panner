/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PannerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                    public juce::Slider::Listener,
                                    public juce::Button::Listener
{
public:
    PannerAudioProcessorEditor (PannerAudioProcessor&);
    ~PannerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider * slider) override;//declare function for slider....speciaal input variable...go to .cpp for actions of function
    void buttonClicked(Button *button) override; 

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PannerAudioProcessor& audioProcessor;
    
    Slider widthSlider; //creating an instance of the thing that is a slider and named widthSlider
    
    ToggleButton staticButton; //type of button that toggles between on and off

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PannerAudioProcessorEditor)
};
