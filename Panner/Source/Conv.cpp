/*
==============================================================================

Convolution.cpp

==============================================================================
*/
//#pragma once

#include "Conv.h"

//
void Conv::setConvType(ConvSelection newConvSelection){

    convSelect = newConvSelection;

    switch (convSelect) {
        case Cab1:
            convType=Cab1;
            break;

        case Cab2:
            convType=Cab2;
            break;

        case Cab3:
            convType=Cab3;
            break;

        case None:
            
            break;

        default:
            convType=Cab1;
            break;
    }

//void Convolution::setIRFile(impulsFile)
}
