/*
  ==============================================================================

    Waveforms.cpp
    Created: 21 Dec 2020 4:03:18pm
    Author:  宮田亮

  ==============================================================================
*/

#include "Waveforms.h"

namespace {
    const float HALF_PI = juce::MathConstants<float>::halfPi;
    const float ONE_PI = juce::MathConstants<float>::pi;
    const float TWO_PI = juce::MathConstants<float>::twoPi;
}

float Waveforms::sine(float angle)
{
    if(angle > TWO_PI)
    {
        angle = fmodf(angle, TWO_PI);
    }
    return sinf(angle);
}
