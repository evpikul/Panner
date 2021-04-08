
/*
  ==============================================================================

    Panning.cpp
    Author:  Emily Pikul

  =============================================================================
*/
#include "Panning.h"
#include <JuceHeader.h>

void Panning::setPanVal(float newPanVal){
    if (newPanVal <= 1.f && newPanVal >= -1.f){
        panVal = newPanVal; //L=-50, R=50
    }
}

float Panning::processSample(float x, int channel){
    if( channel ==1){
            y[channel]     = x * cosf(1.f * M_PI_2) * THREE_DB;
        }
    else {
            y[channel]    = x * sinf(1.f * M_PI_2) * THREE_DB;
        }
    
    return y[channel];
    
}



//void Panning::setFs(float newFs){
//    Fs = newFs;
//    alpha = exp(-log(9)/(Fs*smoothTime));
//}
