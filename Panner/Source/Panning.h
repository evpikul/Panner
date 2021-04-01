/*
  ==============================================================================
 Panning.h

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class Panning{
    
public:
   
    Panning();
    ~Panning();
    
   

  
    
    // Parameter indices
    enum Parameters
    {
        gainParam,
        panParam,
        totalNumParams
    };

    // User parameters
    float uGain, uPan;          // Must be 0.-1.
    
private:
    // Default values
    const float DEFAULT_U_GAIN  = 96.f/106.f;
    const float DEFAULT_A_GAIN  = 1.f;
    const float THREE_DB        = 1.41254f;
    const float DEFAULT_PAN     = 0.5f;

    // Algorithm parameters
    float aGain, aPan;

    // In-loop values
    float leftPanGain, rightPanGain;
    
};
