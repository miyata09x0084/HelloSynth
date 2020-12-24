/*
  ==============================================================================

    SimpleVoice.cpp
    Created: 21 Dec 2020 4:02:17pm
    Author:  宮田亮

  ==============================================================================
*/

#include "SimpleVoice.h"

namespace {
    const float HALF_PI = juce::MathConstants<float>::halfPi;
    const float ONE_PI = juce::MathConstants<float>::pi;
    const float TWO_PI = juce::MathConstants<float>::twoPi;
}

SimpleVoice::SimpleVoice(OscillatorParameters* oscParams, LfoParameters* lfoParams, AmpEnvelopeParameters* ampEnvParams, juce::AudioParameterBool* velocitySenseParam)
    : _oscParamsPtr(oscParams)
    , _lfoParamsPtr(lfoParams)
    , _ampEnvParamsPtr(ampEnvParams)
    , _velocitySenseParamPtr(velocitySenseParam)
    , ampEnv(ampEnvParams->Attack->get(), ampEnvParams->Decay->get(), ampEnvParams->Sustain->get(), ampEnvParams->Release->get())
    , currentAngle(0.0f), lfoAngle(0.0f), angleDelta(0.0f)
    , level(0.0f), lastLevel(0.0f), levelDiff(0.0f)
    , pitchBend(0.0f)
{}

SimpleVoice::~SimpleVoice()
{}

bool SimpleVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<const SimpleSound*> (sound) != nullptr;
}

void SimpleVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    DBG("[StartNote] NoteNumber: " + juce::String(midiNoteNumber) + ", Velocity: " + juce::String(velocity));

    if (SimpleSound* soundForPlay = dynamic_cast<SimpleSound*> (sound))
    {
        if (_velocitySenseParamPtr->get())
        {
            if (velocity <= 0.01f) {
                velocity = 0.01f;
            }
            level = velocity * 0.4f;
        }
        else
        {
            level = 0.8f;
        }

        levelDiff = level - lastLevel;

        pitchBend = ((float)currentPitchWheelPosition - 8192.0f) / 8192.0f;

        float cyclesPerSecond = (float)juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        float cyclesPerSample = (float)cyclesPerSecond / (float)getSampleRate();
        angleDelta = cyclesPerSample * TWO_PI;

        ampEnv.attackStart();
    }
}

