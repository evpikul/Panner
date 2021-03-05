//
//  Panning.cpp
//  Panner
//
//  Created by Emily Pikul on 3/1/21.
//

#include "Panning.h"
#include <JuceHeader.h>

float Panning::processSample(float x){
    return x; //do stuff
}

void Panning::setWidth(float newWidth){
    if(newWidth <=10.f && newWidth >=1.f){
        width = newWidth;
    }
}
