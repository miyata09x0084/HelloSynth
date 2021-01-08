/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "GUI/ParametersComponent.h"
#include "GUI/ScopeComponent.h"

//==============================================================================
/**
*/
class SimpleSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor&);
    ~SimpleSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    SimpleSynthAudioProcessor& audioProcessor;
    
    juce::MidiKeyboardComponent keyboardComponent;
    ScopeComponent<float> scopeComponent;
    OscillatorParametersComponent oscParamsComponent;
    AmpEnvelopeParametersComponent ampEnvParamsComponent;
    LfoParametersComponent lfoParamsComponent;
    FilterParametersComponent filterParamsComponent;
    ReverbParametersComponent reverbParamsComponent;
    DriveParametersComponent driveParamsComponent;
    MiscParametersComponent miscParamsComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)
};
