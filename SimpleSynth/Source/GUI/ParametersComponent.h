/*
  ==============================================================================

    ParametersComponent.h
    Created: 4 Jan 2021 3:06:03pm
    Author:  宮田亮

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/SimpleSynthParameters.h"

class OscillatorParametersComponent : public juce::Component, juce::Slider::Listener, private juce::Timer
{
public:
    OscillatorParametersComponent(OscillatorParameters* oscParams);
    virtual ~OscillatorParametersComponent();
    
    virtual void paint(juce::Graphics& g) override;
};
