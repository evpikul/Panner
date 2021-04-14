/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Panning.h"
//#include "juce_dsp"

//==============================================================================
/**
*/
class JuceGainAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceGainAudioProcessor();
    ~JuceGainAudioProcessor();

    //==============================================================================

    const String getName() const;
//    int getNumParameters();
//
//    float getParameter (int index);
//    void setParameter (int index, float newValue);
//    float getParameterDefaultValue(int index);
//
//    const String getParameterName (int index);
//    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    //const String getName() const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    int convType = 1;
    
    float panVal = 0.f;
    AudioParameterFloat * pan;
    //float gain = 1.f;
    AudioParameterFloat * gain;
    bool  muteOn = false;
    
private:
    //==============================================================================
    
//    // Default values
//    const float DEFAULT_U_GAIN  = 96.f/106.f;
//    const float DEFAULT_A_GAIN  = 1.f;
//    const float THREE_DB        = 1.41254f;
//    const float DEFAULT_PAN     = 0.5f;
//
//    // Algorithm parameters
//    float aGain, aPan;

    // In-loop values
    //float leftPanGain, rightPanGain;
    
    Panning myPanning;
    juce::dsp::Convolution myConvolution;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceGainAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
