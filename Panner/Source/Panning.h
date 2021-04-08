/*
  ==============================================================================
 Panning.h

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>

class Panning {
  
public:
    
    float processSample(float x, int channel);
    
    void setPanVal(float newPanVal);
    
    //void setFs(float newFs);

private:
    float panVal = 0.f;
    float Fs = 48000.f;
    
    const float THREE_DB        = 1.41254f;

    
    float x[2] = {0.f,0.f}; //initialize in and out
    float y[2] = {0.f,0.f};
    
};
