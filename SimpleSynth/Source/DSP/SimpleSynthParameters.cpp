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

void OscillatorParameters::saveParameters(juce::XmlElement& xml)
{
    xml.setAttribute(SineWaveLevel->paramID, (double)SineWaveLevel->get());
    xml.setAttribute(SawWaveLevel->paramID, (double)SawWaveLevel->get());
    xml.setAttribute(TriWaveLevel->paramID, (double)TriWaveLevel->get());
    xml.setAttribute(SquareWaveLevel->paramID, (double)SquareWaveLevel->get());
    xml.setAttribute(NoiseLevel->paramID, (double)NoiseLevel->get());
}

void OscillatorParameters::loadParameters(juce::XmlElement& xml)
{
    *SineWaveLevel = (float)xml.getDoubleAttribute(SineWaveLevel->paramID, 1.0);
    *SawWaveLevel = (float)xml.getDoubleAttribute(SawWaveLevel->paramID, 1.0);
    *TriWaveLevel = (float)xml.getDoubleAttribute(TriWaveLevel->paramID, 1.0);
    *SquareWaveLevel = (float)xml.getDoubleAttribute(SquareWaveLevel->paramID, 1.0);
    *NoiseLevel = (float)xml.getDoubleAttribute(NoiseLevel->paramID, 0.0);
}

AmpEnvelopeParameters::AmpEnvelopeParameters(juce::AudioParameterFloat* attack,
                                             juce::AudioParameterFloat* decay,
                                             juce::AudioParameterFloat* sustain,
                                             juce::AudioParameterFloat* release)
    : Attack(attack)
    , Decay(decay)
    , Sustain(sustain)
    , Release(release)
{}

void AmpEnvelopeParameters::addAllParameters(juce::AudioProcessor& processor)
{
    processor.addParameter(Attack);
    processor.addParameter(Decay);
    processor.addParameter(Sustain);
    processor.addParameter(Release);
}

void AmpEnvelopeParameters::saveParameters(juce::XmlElement & xml)
{
    xml.setAttribute(Attack->paramID, (double)Attack->get());
    xml.setAttribute(Decay->paramID, (double)Decay->get());
    xml.setAttribute(Sustain->paramID, (double)Sustain->get());
    xml.setAttribute(Release->paramID, (double)Release->get());
}

void AmpEnvelopeParameters::loadParameters(juce::XmlElement & xml)
{
    *Attack = (float)xml.getDoubleAttribute(Attack->paramID, 0.01);
    *Decay = (float)xml.getDoubleAttribute(Decay->paramID, 0.01);
    *Sustain = (float)xml.getDoubleAttribute(Sustain->paramID, 1.0);
    *Release = (float)xml.getDoubleAttribute(Release->paramID, 0.01);
}

LfoParameters::LfoParameters(juce::AudioParameterChoice* lfoTarget,
                             juce::AudioParameterChoice* lfoWaveType,
                             juce::AudioParameterFloat* lfoAmount,
                             juce::AudioParameterFloat* lfoSpeed)
    : LfoTarget(lfoTarget)
    , LfoWaveType(lfoWaveType)
    , LfoAmount(lfoAmount)
    , LfoSpeed(lfoSpeed)
{
    LfoSpeed->range.symmetricSkew = false;
    LfoSpeed->range.skew = 0.5;

}

void LfoParameters::addAllParameters(juce::AudioProcessor& processor)
{
    processor.addParameter(LfoTarget);
    processor.addParameter(LfoWaveType);
    processor.addParameter(LfoAmount);
    processor.addParameter(LfoSpeed);
}

