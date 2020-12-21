/*
  ==============================================================================

    SimpleSynthParameters.h
    Created: 21 Dec 2020 4:04:07pm
    Author:  宮田亮

  ==============================================================================
*/

#pragma once


#include "../JuceLibraryCode/JuceHeader.h"

class SynthParametersBase
{
public:
    virtual ~SynthParametersBase() {};
    
    virtual void addAllParameters(juce::AudioProcessor& processor) = 0;
    virtual void saveParameters(juce::XmlElement& xml) = 0;
    virtual void loadParameters(juce::XmlElement& xml) = 0;
};
