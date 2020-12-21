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

class OscillatorParameters : public SynthParametersBase
{
public:
    juce::AudioParameterFloat* SineWaveLevel;
    juce::AudioParameterFloat* SawWaveLevel;
    juce::AudioParameterFloat* TriWaveLevel;
    juce::AudioParameterFloat* SquareWaveLevel;
    juce::AudioParameterFloat* NoiseLevel;
    
    OscillatorParameters(juce::AudioParameterFloat* sineWaveLevel, juce::AudioParameterFloat* sawWaveLevel, juce::AudioParameterFloat* triWaveLevel, juce::AudioParameterFloat* squareWaveLevel, juce::AudioParameterFloat* noiseLevel);
    
    virtual void addAllParameters(juce::AudioProcessor& processor) override;
    virtual void saveParameters(juce::XmlElement& xml) override;
    virtual void loadParameters(juce::XmlElement& xml) override;
    
private:
    OscillatorParameters() {};
};

class AmpEnvelopeParameters : public SynthParametersBase
{
public:
    juce::AudioParameterFloat* Attack;
    juce::AudioParameterFloat* Decay;
    juce::AudioParameterFloat* Sustain;
    juce::AudioParameterFloat* Release;

    AmpEnvelopeParameters(juce::AudioParameterFloat* attack,
                          juce::AudioParameterFloat* decay,
                          juce::AudioParameterFloat* sustain,
                          juce::AudioParameterFloat* release);

    virtual void addAllParameters(juce::AudioProcessor& processor) override;
    virtual void saveParameters(juce::XmlElement& xml) override;
    virtual void loadParameters(juce::XmlElement& xml) override;

private:
    AmpEnvelopeParameters() {};
};

class LfoParameters : public SynthParametersBase
{
public:
    juce::AudioParameterChoice* LfoTarget;
    juce::AudioParameterChoice* LfoWaveType;
    juce::AudioParameterFloat*  LfoAmount;
    juce::AudioParameterFloat*  LfoSpeed;

    LfoParameters(juce::AudioParameterChoice* lfoTarget,
                  juce::AudioParameterChoice* lfoWaveType,
                  juce::AudioParameterFloat*  LfoAmount,
                  juce::AudioParameterFloat*  lfoSpeed);

    virtual void addAllParameters(juce::AudioProcessor& processor) override;
    virtual void saveParameters(juce::XmlElement& xml) override;
    virtual void loadParameters(juce::XmlElement& xml) override;

private:
    LfoParameters() {};
};

class FilterParameters : public SynthParametersBase
{
public:
    juce::AudioParameterChoice* Type;
    juce::AudioParameterFloat*  Frequency;
    juce::AudioParameterFloat*  Q;

    FilterParameters(juce::AudioParameterChoice* type,
                     juce::AudioParameterFloat*  frequency,
                     juce::AudioParameterFloat*  q);

    virtual void addAllParameters(juce::AudioProcessor& processor) override;
    virtual void saveParameters(juce::XmlElement& xml) override;
    virtual void loadParameters(juce::XmlElement& xml) override;

private:
    FilterParameters() {};
};

class ReverbParameters : public SynthParametersBase
{
public:
    juce::AudioParameterFloat*  RoomSize;
    juce::AudioParameterFloat*  Damping;
    juce::AudioParameterFloat*  WetLevel;
    juce::AudioParameterFloat*  DryLevel;
    juce::AudioParameterFloat*  Width;
    juce::AudioParameterFloat*  FreezeMode;

    ReverbParameters(juce::AudioParameterFloat*  roomSize,
                     juce::AudioParameterFloat*  damping,
                     juce::AudioParameterFloat*  wetLevel,
                     juce::AudioParameterFloat*  dryLevel,
                     juce::AudioParameterFloat*  width,
                     juce::AudioParameterFloat*  freezeMode);

    virtual void addAllParameters(juce::AudioProcessor& processor) override;
    virtual void saveParameters(juce::XmlElement& xml) override;
    virtual void loadParameters(juce::XmlElement& xml) override;

private:
    ReverbParameters() {};
};
