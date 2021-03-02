/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PannerAudioProcessorEditor::PannerAudioProcessorEditor (PannerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    //Constructor.....gainSlider=object
    widthSlider.addListener(this);  //gain slider located on interface that pays attention/listening to mouse clicks...pays attention to this specific GUI window (MyTestPluginAudioProcessorEditor)
    widthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag); //circular knob
    widthSlider.setBounds(10,150,120,120); //position of slider on GUI
    widthSlider.setRange(0.f, 10.f,.1f); //min and max knob values and increments
    //gainSlider.setSkewFactorFromMidPoint(1.f); //sets midpoint value?
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30); //read out happens below knob, allow for editable number value aka false for readonly, text box size
    widthSlider.setValue(audioProcessor.width); //set slider to the gain variable initial value
    addAndMakeVisible(widthSlider); //makes gainSlider visible....but what happens when we move the slider? edit the editor.h
    
    staticButton.addListener(this);
    staticButton.setBounds(200,90,120,20);
    staticButton.setButtonText("mute");
    staticButton.setToggleState(audioProcessor.staticOn, dontSendNotification);
    addAndMakeVisible(staticButton);
    
}

PannerAudioProcessorEditor::~PannerAudioProcessorEditor()
{
}

//==============================================================================
void PannerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("My Panner Plugin", ,20,5,400,100, juce::Justification::centred, 1);
}

void PannerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void PannerAudioProcessorEditor::sliderValueChanged(Slider *slider){
    
    if(slider == &gainSlider){
        audioProcessor.width = widthSlider.getValue();  //find gain that belongs to audio processor, but only change when the slider moves...get value and send to processor and assign to the gain variable
    }
}

void PannerAudioProcessorEditor:: buttonClicked(Button *button){
    if( button == &staticButton){
        audioProcessor.staticOn =! audioProcessor.staticOn;
    }
}
