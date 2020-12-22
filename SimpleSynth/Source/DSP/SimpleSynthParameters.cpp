/*
  ==============================================================================

    SimpleSynthParameters.cpp
    Created: 21 Dec 2020 4:04:07pm
    Author:  宮田亮

  ==============================================================================
*/

#include "SimpleSynthParameters.h"

OscillatorParameters::OscillatorParameters(juce::AudioParameterFloat * sineWaveLevel, juce::AudioParameterFloat * sawWaveLevel, juce::AudioParameterFloat * triWaveLevel, juce::AudioParameterFloat * squareWaveLevel, juce::AudioParameterFloat * noiseLevel)
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
