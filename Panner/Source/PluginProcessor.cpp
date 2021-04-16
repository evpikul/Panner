/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>


//==============================================================================
JuceGainAudioProcessor::JuceGainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "context",
                                createParameterLayout())
#endif
{
}

AudioProcessorValueTreeState::ParameterLayout JuceGainAudioProcessor::createParameterLayout(){
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back( std::make_unique<AudioParameterFloat> ("ConvParams","Conv",0.f,2.f,1.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("panValue","Pan",0.f,2.f,1.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("gainValue","Gain",0.f,2.f,1.f) );
    
    return {params.begin() , params.end() };
}


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
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    myConvolution.reset();
    myConvolution.prepare(spec);
    
//    //convType = newConvType; 
//    switch (convType) {
//        case Cab1:
//            myConvolution.loadImpulseResponse(BinaryData::KustomShanuteKansasB5LeftA230200320_wav, BinaryData::KustomShanuteKansasB5LeftA230200320_wavSize,  dsp::Convolution::Stereo::yes, dsp::Convolution::Trim::yes, 0, dsp::Convolution::Normalise::yes);
//            break;
//
//        case Conv::Cab2:
//            myConvolution.loadImpulseResponse(BinaryData::iR_cathedral_wav, BinaryData::KustomShanuteKansasB5LeftA230200320_wavSize,  dsp::Convolution::Stereo::yes, dsp::Convolution::Trim::yes, 0, dsp::Convolution::Normalise::yes);
//            break;
//
//        case Conv::Cab3:
//            myConvolution.loadImpulseResponse(BinaryData::Direct_Cabinet_N1_wav, BinaryData::KustomShanuteKansasB5LeftA230200320_wavSize,  dsp::Convolution::Stereo::yes, dsp::Convolution::Trim::yes, 0, dsp::Convolution::Normalise::yes);
//            break;
//
//        case Conv::None:
//            myConvolution.loadImpulseResponse(BinaryData::KustomShanuteKansasB5LeftA230200320_wav, BinaryData::KustomShanuteKansasB5LeftA230200320_wavSize,  dsp::Convolution::Stereo::yes, dsp::Convolution::Trim::yes, 0, dsp::Convolution::Normalise::yes);
//            break;
//
//        default:
//            myConvolution.loadImpulseResponse(BinaryData::KustomShanuteKansasB5LeftA230200320_wav, BinaryData::KustomShanuteKansasB5LeftA230200320_wavSize,  dsp::Convolution::Stereo::yes, dsp::Convolution::Trim::yes, 0, dsp::Convolution::Normalise::yes);
//    }
//
//    convType = *state.getRawParameterValue("convType");
}

void JuceGainAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceGainAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (muteOn){
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            for (int n = 0; n < buffer.getNumSamples() ; n++){
                buffer.getWritePointer(channel)[n] = 0.f;
            }
        }
    }
    else{
        
        dsp::AudioBlock<float> block (buffer);
        dsp::ProcessContextReplacing<float> context (block);
        myConvolution.process(context);
        
        myPanning.setPanVal(panVal);
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            for (int n = 0; n < buffer.getNumSamples() ; n++){
                float x = buffer.getReadPointer(channel)[n];
                float y = myPanning.processSample(x,channel);
                
                buffer.getWritePointer(channel)[n] = y;
                
            }
        }
    }
    
    
}

//==============================================================================
bool JuceGainAudioProcessor::hasEditor() const
{
    // Temporarily false until work on GUI begins
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JuceGainAudioProcessor::createEditor()
{
   return new JuceGainAudioProcessorEditor (*this);
}

//==============================================================================
void JuceGainAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto currentState = state.copyState();
    std::unique_ptr<XmlElement> xml (currentState.createXml());
    copyXmlToBinary(*xml, destData);
}

void JuceGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xml ( getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName(state.state.getType())){
        state.replaceState(ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceGainAudioProcessor();
}
