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

float Waveforms::saw(float angle)
{
    if(angle > TWO_PI)
    {
        angle = fmodf(angle, TWO_PI);
    }

    if (angle <= ONE_PI)
    {
        return (angle / ONE_PI);
    }
    else
    {
        return -2.0f + (angle / ONE_PI) ;
    }
}

float Waveforms::square(float angle)
{

    if (angle > TWO_PI)
    {
        angle = fmodf(angle, TWO_PI);
    }

    if (angle <= ONE_PI)
    {
        return 1.0f;
    }
    else
    {
        return -1.0f;
    }
}
