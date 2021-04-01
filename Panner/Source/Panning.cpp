
/*
  ==============================================================================

    Panning.cpp
    Author:  Emily Pikul

  =============================================================================
*/
#include "Panning.h"

//Constructor
Panning::Panning(){
    uGain               = DEFAULT_U_GAIN;
    aGain               = DEFAULT_A_GAIN;
    aPan    = uPan      = DEFAULT_PAN;

    
}

void Panning::processSignal(float *signal, const int numSamples, const int channel){
    for (int n = 0; n < numSamples; n++){
            float x = signal[n]; // get value at memory location
            x = processSample(x, c);
            signal[n] = x;
        }
}

float Panning::processSample(float x, int c){
    
    // Do not use decibels in multiplier! Only uV (unit voltage)
    leftPanGain     = aGain * cosf(aPan * M_PI_2) * THREE_DB;
    rightPanGain    = aGain * sinf(aPan * M_PI_2) * THREE_DB;
    
    float d = filter.processSample(w[c][delayIndex], c);
    
    float y = x + 0.7f * d;
    
    // Feed-forward
    //w[c][index[c]] = x;
    
    // Feed-back
    w[c][writeIndex[c]] = y;
    
    writeIndex[c]++;
    if (writeIndex[c] >= BUFFERSIZE){
        writeIndex[c] = 0;
    }
    
    return y;
    
}


int Panning::getNumParameters()
{
    // Return total number of parameters
    return totalNumParams;
}

float Panning::getParameter (int index)
{
    switch (index) {
        case gainParam:       return uGain;
        case panParam:          return uPan;
        default:                return 0.f;
    }
}

void Panning::setParameter (int index, float newValue)
{
    // newValue must always be from 0.f - 1.f
    
    switch (index) {
        case gainParam:     // GUI Range: [-96, +10], in decibels
            uGain = newValue;
            aGain = powf(10.f, (106.f * uGain - 96.f) / 20.f);
            break;
        
        case panParam:      // GUI Range: [-50, +50]
            uPan = newValue;
            aPan = uPan;    // L = 0., R = 1.
            break;
            
        default:
            break;
    }
    
    leftPanGain     = aGain * cosf(aPan * M_PI_2) * THREE_DB;
    rightPanGain    = aGain * sinf(aPan * M_PI_2) * THREE_DB;
}

float Panning::getParameterDefaultValue(int index) {
    switch (index) {
        case gainParam:     return DEFAULT_U_GAIN;
        case panParam:      return DEFAULT_PAN;
        default:            return 0.f;
    }
}

const String Panning::getParameterName (int index)
{
    switch (index) {
        case gainParam:     return "Gain";
        case panParam:      return "Pan";
        default:            return std::string();
    }
}

const String Panning::getParameterText (int index)
{
    // Reconvert 0.-1.f values to UI ranges for host to recognize
    switch (index) {
        case gainParam:     return String(106.f * uGain - 96.f, 2);
        case panParam:      return String((int)(100.f * uPan - 50.f));
        default:            return String(getParameter(index), 2);
    }
}


