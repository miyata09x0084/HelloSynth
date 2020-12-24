/*
  ==============================================================================

    SimpleVoice.cpp
    Created: 21 Dec 2020 4:02:17pm
    Author:  宮田亮

  ==============================================================================
*/

#include "SimpleVoice.h"

OscillatorParameters::OscillatorParameters(juce::AudioParameterFloat* sineWaveLevel, juce::AudioParameterFloat* sawWaveLevel,
                                           juce::AudioParameterFloat* triWaveLevel, juce::AudioParameterFloat* squareWaveLevel,
                                           juce::AudioParameterFloat* noiseLevel)
    :SineWaveLevel(sineWaveLevel), SawWaveLevel(sawWaveLevel),
     TriWaveLevel(triWaveLevel), SquareWaveLevel(squareWaveLevel),
     NoiseLevel(noiseLevel)
{}

void OscillatorParameters::addAllParameters(juce::AudioProcessor& processor)
{
    processor.addParameter(SineWaveLevel);
    processor.addParameter(SawWaveLevel);
    processor.addParameter(TriWaveLevel);
    processor.addParameter(SquareWaveLevel);
    processor.addParameter(NoiseLevel);
}

void OscillatorParameters::saveParameters(juce::XmlElement& xml)
{
    xml.setAttribute(SineWaveLevel->paramID, (double)SineWaveLevel->get());
    xml.setAttribute(SawWaveLevel->paramID, (double)SawWaveLevel->get());
    xml.setAttribute(TriWaveLevel->paramID, (double)TriWaveLevel->get());
    xml.setAttribute(SquareWaveLevel->paramID, (double)SquareWaveLevel->get());
    xml.setAttribute(NoiseLevel->paramID, (double)NoiseLevel->get());
}
