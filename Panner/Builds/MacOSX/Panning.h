//
//  Panning.h
//  Panner
//
//  Created by Emily Pikul on 3/1/21.
//

#pragma once

class Panning {
    
public:
    float processSample(float x);
    void setWidth(float newWidth);
    
    
private:
    float width =1.f;
    
    
    
};
