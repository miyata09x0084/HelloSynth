/*
  ==============================================================================

    SimpleVoice.h
    Created: 21 Dec 2020 4:02:17pm
    Author:  宮田亮

  ==============================================================================
*/

#pragma once

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SimpleSynthParameters.h"
#include "Waveforms.h"
#include "AmpEnvelope.h"
#include "SimpleSound.h"

class SimpleVoice : public juce::SynthesiserVoice
{
public:
    SimpleVoice(OscillatorParameters* oscParams, LfoParameters* lfoParams, AmpEnvelopeParameters* ampEnvParams, juce::AudioParameterBool* velocitySenseParam);

    virtual ~SimpleVoice();

    virtual bool canPlaySound(juce::SynthesiserSound* sound) override;
    virtual void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    virtual void stopNote(float velocity, bool allowTailOff) override;
    virtual void pitchWheelMoved(int newPitchWheelValue) override;
    virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
    virtual void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    float calcModulationFactor(float angle);

    float currentAngle, lfoAngle, angleDelta;
    float level, lastLevel, levelDiff;
    float pitchBend;

    Waveforms waveForms;
    AmpEnvelope ampEnv;

    OscillatorParameters* _oscParamsPtr;
    LfoParameters* _lfoParamsPtr;
    AmpEnvelopeParameters* _ampEnvParamsPtr;
    juce::AudioParameterBool* _velocitySenseParamPtr;
};
