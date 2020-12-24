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

void AmpEnvelopeParameters::saveParameters(juce::XmlElement& xml)
{
    xml.setAttribute(Attack->paramID, (double)Attack->get());
    xml.setAttribute(Decay->paramID, (double)Decay->get());
    xml.setAttribute(Sustain->paramID, (double)Sustain->get());
    xml.setAttribute(Release->paramID, (double)Release->get());
}

void AmpEnvelopeParameters::loadParameters(juce::XmlElement& xml)
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

void LfoParameters::saveParameters(juce::XmlElement& xml)
{
    xml.setAttribute(LfoTarget->paramID, LfoTarget->getIndex());
    xml.setAttribute(LfoWaveType->paramID, LfoWaveType->getIndex());
    xml.setAttribute(LfoAmount->paramID, (double)LfoAmount->get());
    xml.setAttribute(LfoSpeed->paramID, (double)LfoSpeed->get());
}

void LfoParameters::loadParameters(juce::XmlElement& xml)
{
    *LfoTarget = xml.getIntAttribute(LfoTarget->paramID, 0);
    *LfoWaveType = xml.getIntAttribute(LfoWaveType->paramID, 0);
    *LfoAmount = (float)xml.getDoubleAttribute(LfoAmount->paramID, 0.3);
    *LfoSpeed = (float)xml.getDoubleAttribute(LfoSpeed->paramID, 2.0);
}

FilterParameters::FilterParameters(juce::AudioParameterChoice* type,
                                   juce::AudioParameterFloat* frequency,
                                   juce::AudioParameterFloat* q)
    : Type(type)
    , Frequency(frequency)
    , Q(q)
{
    Frequency->range.symmetricSkew = false;
    Frequency->range.skew = 0.3;
}

void FilterParameters::addAllParameters(juce::AudioProcessor& processor)
{
    processor.addParameter(Type);
    processor.addParameter(Frequency);
    processor.addParameter(Q);
}

void FilterParameters::saveParameters(juce::XmlElement& xml)
{
    xml.setAttribute(Type->paramID, Type->getIndex());
    xml.setAttribute(Frequency->paramID, (double)Frequency->get());
    xml.setAttribute(Q->paramID, (double)Q->get());
}

void FilterParameters::loadParameters(juce::XmlElement & xml)
{
    *Type = xml.getIntAttribute(Type->paramID, 1);
    *Frequency = (float)xml.getDoubleAttribute(Frequency->paramID, 20000.0);
    *Q = (float)xml.getDoubleAttribute(Q->paramID, 1.0);
}

ReverbParameters::ReverbParameters(juce::AudioParameterFloat* roomSize,
                                   juce::AudioParameterFloat* damping,
                                   juce::AudioParameterFloat* wetLevel,
                                   juce::AudioParameterFloat* dryLevel,
                                   juce::AudioParameterFloat* width,
                                   juce::AudioParameterFloat* freezeMode)
    :RoomSize(roomSize)
    , Damping(damping)
    , WetLevel(wetLevel)
    , DryLevel(dryLevel)
    , Width(width)
    , FreezeMode(freezeMode)
{}

void ReverbParameters::addAllParameters(juce::AudioProcessor& processor)
{
    processor.addParameter(RoomSize);
    processor.addParameter(Damping);
    processor.addParameter(WetLevel);
    processor.addParameter(DryLevel);
    processor.addParameter(Width);
    processor.addParameter(FreezeMode);
}
