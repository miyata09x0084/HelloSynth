/*
  ==============================================================================

    Waveforms.h
    Created: 21 Dec 2020 4:03:18pm
    Author:  宮田亮

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Waveforms
{
public:
    float sine(float angle);
    float saw(float angle);
    float square(float angle);
    float triangle(float angle);
    float noise();
    
private:
    juce::Random whiteNoise;
};


