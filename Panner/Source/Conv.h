/*
==============================================================================

Convolution.h

==============================================================================
*/

#pragma once

#include <JuceHeader.h>


    //==============================================================================
    /**
     * Derives from JUCE's Convolution base class. Computes the convolution
     * algorithm between the audio signal and the IR buffer.
     */
    class Conv{
    public:
        
        Conv();
        enum ConvSelection { Cab1, Cab2, Cab3, None };
        void setConvType(ConvSelection newConvSelection);
        
    private:
        
        ConvSelection convSelect = Cab1;
        float convType = Cab1; 
//        //==============================================================================
//        Convolution(juce::AudioProcessor* processor);
//
//        //==============================================================================
//        using Ptr = std::shared_ptr<Convolution>;
//
//        //==============================================================================
//        virtual void updateParams(const juce::AudioProcessorValueTreeState& params,
//                                  const juce::String& = "") override;
//
//        virtual AudioBlock exec(AudioBlock audio) override;
//
//        //==============================================================================
//        void loadIR(AudioBlock ir);
    };

//
