/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>


//==============================================================================
JuceGainAudioProcessor::JuceGainAudioProcessor(){}


JuceGainAudioProcessor::~JuceGainAudioProcessor()
{
}

//==============================================================================
const String JuceGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}



const String JuceGainAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String JuceGainAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool JuceGainAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool JuceGainAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool JuceGainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceGainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceGainAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double JuceGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceGainAudioProcessor::getNumPrograms()
{
    return 0;
}

int JuceGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceGainAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceGainAudioProcessor::getProgramName (int index)
{
    return std::string();
}

void JuceGainAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceGainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JuceGainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceGainAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
  
        float* leftChannel  = buffer.getWritePointer(0);
        float* rightChannel = buffer.getWritePointer(1);
        
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            
            leftChannel[i]  = Panning.setParameter(x,channel);
            rightChannel[i] = Panning.setParameter(x,channel);
        }
        
      
        for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        {
           
            
            buffer.clear (i, 0, buffer.getNumSamples());
        }
}

//==============================================================================
bool JuceGainAudioProcessor::hasEditor() const
{
    // Temporarily false until work on GUI begins
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceGainAudioProcessor::createEditor()
{
   return new JuceGainAudioProcessorEditor (*this);
}

//==============================================================================
void JuceGainAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceGainAudioProcessor();
}
