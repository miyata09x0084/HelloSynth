/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DSP/SimpleSynthParameters.h"

//==============================================================================
/**
*/
class SimpleSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleSynthAudioProcessor();
    ~SimpleSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void changeVoiceSize();
    
    const juce::StringArray LFO_TARGETS{ "None", "WaveLevel", "WaveAngle" };
    const juce::StringArray LFO_WAVE_TYPES{ "Sine", "Saw", "Tri", "Square", "Noise" };
    const juce::StringArray FILTER_TYPES{ "Low-Pass", "High-Pass", "Band-Pass" };
    
    OscillatorParameters oscParameters;
    LfoParameters lfoParameters;
    AmpEnvelopeParameters ampEnvParameters;
    FilterParameters filterParameters;
    ReverbParameters reverbParameters;
    juce::AudioParameterFloat* driveParameter;
    juce::AudioParameterFloat* masterVolumePrameter;
    juce::AudioParameterInt* voiceSizeParameter;
    juce::AudioParameterBool* velocitySenseParameter;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessor)
};
