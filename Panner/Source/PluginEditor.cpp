/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
JuceGainAudioProcessorEditor::JuceGainAudioProcessorEditor (JuceGainAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (700, 400);
    
    //Gain
    gainDbSlider.addListener (this);
    gainDbSlider.setTooltip (TRANS("Adjusts output volume"));
    gainDbSlider.setBounds(20,100,250,250);
    gainDbSlider.setRange (-96, 10, 0.01);
    gainDbSlider.setSliderStyle (Slider::LinearVertical);
    gainDbSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    gainDbSlider.setColour (Slider::backgroundColourId, Colours::cornsilk);
    gainDbSlider.setColour (Slider::thumbColourId, Colours::greenyellow);
    gainDbSlider.setColour (Slider::trackColourId, Colours::peru);
    gainDbSlider.setColour (Slider::rotarySliderOutlineColourId, Colours::peru);
    gainDbSlider.setColour (Slider::textBoxTextColourId, Colours::white);
    gainDbSlider.setColour (Slider::textBoxBackgroundColourId, Colour (0xff181818));
    gainDbSlider.setColour (Slider::textBoxHighlightColourId, Colours::white);
    gainDbSlider.setColour (Slider::textBoxOutlineColourId, Colour (0x10808080));
    addAndMakeVisible(gainDbSlider);
    gainLabel.setText("GAIN", dontSendNotification);
    gainLabel.attachToComponent(&gainDbSlider, false);
    

    //Panning knobs
    panKnob.addListener (this);
    panKnob.setTooltip (TRANS("Adjusts signal panning"));
    panKnob.setBounds(500,100,200,200);
    panKnob.setRange (-50, -50, 0);
    panKnob.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    panKnob.setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    panKnob.setColour (Slider::rotarySliderFillColourId, Colours::greenyellow);
    panKnob.setColour (Slider::thumbColourId, Colours::darkorange);
    panKnob.setColour (Slider::rotarySliderOutlineColourId, Colour (0x00000000));
    panKnob.setColour (Slider::textBoxTextColourId, Colours::white);
    panKnob.setColour (Slider::textBoxBackgroundColourId, Colour (0xff181818));
    panKnob.setColour (Slider::textBoxHighlightColourId, Colours::white);
    panKnob.setColour (Slider::textBoxOutlineColourId, Colour (0x10808080));
    addAndMakeVisible(panKnob);
    panLabel.setText("PAN", dontSendNotification);
    panLabel.attachToComponent(&panKnob, false);
    
    //ComboBox
    convSelector.addListener(this);
    convSelector.setTooltip (TRANS("Convolution"));
    convSelector.setBounds(500,5,25,25);
    //convSelector->setTextBoxStyle (ComboBox::TextBoxBelow, false, 60, 20);
    convSelector.addItem("Cabinet 1",1);
    convSelector.addItem("Cabinet 2",2);
    convSelector.addItem("Cathedral", 3);
   // convSelector.addItem("Plate", 4);
    convSelector.addItem("None", 4);
    convSelector.setSelectedId(1);
    convSelector.setBounds(275, 100, 120, 40);
    addAndMakeVisible(convSelector);
    convLabel.setText("CONVOLUTION", dontSendNotification);
    convLabel.attachToComponent(&convSelector, false);
    
    
    muteButton.addListener(this);
    muteButton.setBounds(275, 175, 100, 40);
    muteButton.setButtonText("Mute");
    muteButton.setToggleState(audioProcessor.muteOn, dontSendNotification);
    addAndMakeVisible(muteButton);



    //[UserPreSize]
    gainDbSlider.setTextValueSuffix("db");

    gainDbSlider.setDoubleClickReturnValue(true, 0);
    panKnob.setDoubleClickReturnValue(true, 0);
    
    //LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel); // Custom Styling
    //[/UserPreSize]

    //[Constructor] You can add your own custom stuff here..
    //startTimer(50);

}

JuceGainAudioProcessorEditor::~JuceGainAudioProcessorEditor()
{
    //[/Destructor_pre]

   // gainDbSlider = nullptr;
   // panKnob = nullptr;
    //gainLabel = nullptr;
   // panLabel = nullptr;

    deleteAllChildren();
}

//==============================================================================
void JuceGainAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff222222));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JuceGainAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    gainDbSlider.setBounds (40, 40, 60, 260);
    panKnob.setBounds (144, 40, 60, 90);
    //gainLabel.setBounds (40, 16, 60, 20);
    //panLabel.setBounds (144, 16, 60, 20);
}



void JuceGainAudioProcessorEditor::sliderValueChanged(Slider *slider){
    
    if (slider == &gainDbSlider){
        *audioProcessor.gain = (gainDbSlider.getValue()+ 96.f) / 106.f; //assign to value of the pointer
    }
    if (slider == &panKnob){
        *audioProcessor.pan = (panKnob.getValue()+ 50.f) / 100.f;; //assign to value of the pointer
    }
    
}

void JuceGainAudioProcessorEditor::buttonClicked(Button * button){
    
    if (button == &muteButton){
        audioProcessor.muteOn = !audioProcessor.muteOn;
    }
    
}

void JuceGainAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox){
    
    if (comboBox == &convSelector){
        if (convSelector.getSelectedId() == 1){
            // Convolution IR 1
            audioProcessor.convType = Convolution::setConvType::Cab1;; //insert strings as values instead?
        }
        if (convSelector.getSelectedId() == 2){
            // Convolution IR 2
            audioProcessor.convType = Convolution::setConvType::Cab2;
        }
        if (convSelector.getSelectedId() == 3){
            // Convolution IR 3
            audioProcessor.convType = Convolution::setConvType::Cab3;
        }
        if (convSelector.getSelectedId() == 4){
            // Convolution IR 4
            audioProcessor.convType = Convolution::setConvType::None;
        }
    }
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//void JuceGainAudioProcessorEditor::timerCallback() {
//    // Timer conflicts cause UI stuttering, this is due to the values not being mapped back
//    JuceGainAudioProcessor& ourProcessor = getProcessor();
//
//    gainDbSlider.setValue(
//        (106.f * ourProcessor.uGain - 96.f),
//        dontSendNotification
//    );
//
//    panSlider.setValue(
//        (100.f * ourProcessor.uPan - 50.f),
//        dontSendNotification
//    );
//}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JuceGainAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="JuceGainAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor (&amp;p), processor (p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="240" initialHeight="320">
  <BACKGROUND backgroundColour="ff222222"/>
  <SLIDER name="Gain Slider" id="869ad7b78e733129" memberName="gainDbSlider"
          virtualName="" explicitFocusOrder="0" pos="40 40 60 260" tooltip="Adjusts output volume"
          bkgcol="0" thumbcol="ff808080" trackcol="7fffffff" rotaryslideroutline="0"
          textboxtext="ffffffff" textboxbkgd="ff181818" textboxhighlight="ffffffff"
          textboxoutline="10808080" min="-96" max="10" int="0.010000000000000000208"
          style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Pan Rotary" id="7de69cf8fd092825" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="144 40 60 90" tooltip="Adjusts signal panning"
          rotarysliderfill="ff808080" rotaryslideroutline="0" textboxtext="ffffffff"
          textboxbkgd="ff181818" textboxhighlight="ffffffff" textboxoutline="10808080"
          min="-50" max="50" int="1" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Gain Label" id="19aa37d5dcee8b93" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="40 16 60 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Pan Label" id="1d49f726da265f5e" memberName="panLabel"
         virtualName="" explicitFocusOrder="0" pos="144 16 60 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pan" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
