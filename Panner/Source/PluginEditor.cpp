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
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (800, 400);
    
    //Gain
    gainDbSlider.addListener (this);
    gainDbSlider.setTooltip (TRANS("Adjusts output volume"));
    gainDbSlider.setBounds(20,100,200,200);
    gainDbSlider.setRange (-96, 10, 0.01);
    gainDbSlider.setSliderStyle (Slider::LinearVertical);
    gainDbSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    gainDbSlider.setColour (Slider::backgroundColourId, Colour (0x00000000));
    gainDbSlider.setColour (Slider::thumbColourId, Colours::grey);
    gainDbSlider.setColour (Slider::trackColourId, Colour (0x7fffffff));
    gainDbSlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x00000000));
    gainDbSlider.setColour (Slider::textBoxTextColourId, Colours::white);
    gainDbSlider.setColour (Slider::textBoxBackgroundColourId, Colour (0xff181818));
    gainDbSlider.setColour (Slider::textBoxHighlightColourId, Colours::white);
    gainDbSlider.setColour (Slider::textBoxOutlineColourId, Colour (0x10808080));
    addAndMakeVisible(gainDbSlider);
    gainLabel.setText("GAIN", dontSendNotification);
    gainLabel.attachToComponent(&gainDbSlider, false);

    //Panning knobs
    panSlider.addListener (this);
    panSlider.setTooltip (TRANS("Adjusts signal panning"));
    panSlider.setBounds(550,100,200,200);
    panSlider.setRange (-50, 50, 1);
    panSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    panSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 60, 20);
    panSlider.setColour (Slider::rotarySliderFillColourId, Colours::grey);
    panSlider.setColour (Slider::rotarySliderOutlineColourId, Colour (0x00000000));
    panSlider.setColour (Slider::textBoxTextColourId, Colours::white);
    panSlider.setColour (Slider::textBoxBackgroundColourId, Colour (0xff181818));
    panSlider.setColour (Slider::textBoxHighlightColourId, Colours::white);
    panSlider.setColour (Slider::textBoxOutlineColourId, Colour (0x10808080));
    addAndMakeVisible(panSlider);
    panLabel.setText("PAN", dontSendNotification);
    panLabel.attachToComponent(&panSlider, false);
    
    //ComboBox
    convSelector.addListener(this);
    convSelector.setTooltip (TRANS("Convolution"));
    convSelector.setBounds(450,10,50,50);
    //convSelector->setTextBoxStyle (ComboBox::TextBoxBelow, false, 60, 20);
    convSelector.addItem("Type1",1);
    convSelector.addItem("Type2",2);
    convSelector.addItem("Type3", 3);
    convSelector.addItem("Type4", 4);
    convSelector.setSelectedId(2);
    convSelector.setBounds(275, 100, 120, 40);
    addAndMakeVisible(convSelector);
    convLabel.setText("CONVOLUTION", dontSendNotification);
    convLabel.attachToComponent(&convSelector, false);
    


//    
    
//    muteONButton.addListener(this);
//    muteONButton.setBounds(275, 175, 100, 40);
//    muteONButton.setButtonText("Sync'd");
//    muteONButton.setToggleState(audioProcessor.tempoSyncd, dontSendNotification);
//    muteONButton.setRadioGroupId(1); // links with "notTempoSyncButton"
//    addAndMakeVisible(tempoSyncButton);
//    
//    muteOFFButton.addListener(this);
//    muteOFFButton.setBounds(100, 175, 100, 40);
//    muteOFFButton.setButtonText("Sync Off");
//    muteOFFButton.setToggleState(!audioProcessor.tempoSyncd, dontSendNotification);
//    muteOFFButton.setRadioGroupId(1);
//    addAndMakeVisible(notTempoSyncButton);
//    

    //[UserPreSize]
    gainDbSlider.setTextValueSuffix("db");

    gainDbSlider.setDoubleClickReturnValue(true, 0);
    panSlider.setDoubleClickReturnValue(true, 0);
    
    //LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel); // Custom Styling
    //[/UserPreSize]


    //[Constructor] You can add your own custom stuff here..
    startTimer(50);
    //[/Constructor]
}

JuceGainAudioProcessorEditor::~JuceGainAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

   // gainDbSlider = nullptr;
   // panSlider = nullptr;
    //gainLabel = nullptr;
   // panLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    deleteAllChildren();
    //[/Destructor]
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
    //panSlider.setBounds (144, 40, 60, 90);
    //gainLabel.setBounds (40, 16, 60, 20);
    //panLabel.setBounds (144, 16, 60, 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JuceGainAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == &gainDbSlider)
    {
        //[UserSliderCode_gainDbSlider] -- add your slider handling code here..
        processor.setParameterNotifyingHost(
            JuceGainAudioProcessor::Parameters::gainParam,
            (float) (sliderThatWasMoved->getValue() + 96.f) / 106.f // map to 0.-1.f (uGain)
        );
        //[/UserSliderCode_gainDbSlider]
    }
    else if (sliderThatWasMoved == &panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
        processor.setParameterNotifyingHost(
            JuceGainAudioProcessor::Parameters::panParam,
            (float) (sliderThatWasMoved->getValue() + 50.f) / 100.f // map to 0.-1.f
        );
        //[/UserSliderCode_panSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void JuceGainAudioProcessorEditor::comboBoxChanged(ComboBox* comboBox){
    
    if (comboBox == &convSelector){
        if (convSelector.getSelectedId() == 1){
            // Convolution IR 1
            processor.convType = 2.f; //insert strings as values instead? 
        }
        if (convSelector.getSelectedId() == 2){
            // Convolution IR 2
            processor.convType = 1.f;
        }
        if (convSelector.getSelectedId() == 3){
            // Convolution IR 3
            processor.convType = 0.5f;
        }
        if (convSelector.getSelectedId() == 4){
            // Convolution IR 4
            processor.convType = 0.25f;
        }
    }
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void JuceGainAudioProcessorEditor::timerCallback() {
    // Timer conflicts cause UI stuttering, this is due to the values not being mapped back
    JuceGainAudioProcessor& ourProcessor = getProcessor();

    gainDbSlider.setValue(
        (106.f * ourProcessor.uGain - 96.f),
        dontSendNotification
    );

    panSlider.setValue(
        (100.f * ourProcessor.uPan - 50.f),
        dontSendNotification
    );
}
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
