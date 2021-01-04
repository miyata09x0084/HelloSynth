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
    
    virtual void resized() override;
    
private:
    OscillatorParametersComponent();
    
    virtual void sliderValueChanged(juce::Slider* slider) override;
    
    virtual void timerCallback() override;
    
    OscillatorParameters* _oscParamsPtr;
    
    juce::Slider sineWaveLevelSlider;
    juce::Slider sawWaveLevelSlider;
    juce::Slider triWaveLevelSlider;
    juce::Slider squareWaveLevelSlider;
    juce::Slider noiseLevelSlider;
    
    juce::Label sineWaveLevelLabel;
    juce::Label sawWaveLevelLabel;
    juce::Label triWaveLevelLabel;
    juce::Label squareWaveLevelLabel;
    juce::Label noiseLevelLabel;
};
