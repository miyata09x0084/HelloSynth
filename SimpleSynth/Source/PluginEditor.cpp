/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace {
    const float KEY_HEIGHT = 80.0f;
    const float KEY_WIDTH = 32.0f;
    const int PANEL_MARGIN = 2;
}

//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
//    : AudioProcessorEditor(&p), processor(p)
    , keyboardComponent(p.getKeyboardState(), juce::MidiKeyboardComponent::Orientation::horizontalKeyboard)
    , oscParamsComponent(&p.oscParameters)
    , ampEnvParamsComponent(&p.ampEnvParameters)
    , lfoParamsComponent(&p.lfoParameters)
    , filterParamsComponent(&p.filterParameters)
    , reverbParamsComponent(&p.reverbParameters)
    , driveParamsComponent(p.driveParameter)
    , miscParamsComponent(p.masterVolumePrameter, p.voiceSizeParameter, p.velocitySenseParameter)
    , scopeComponent(p.getAudioBufferQueue())
{
    keyboardComponent.setKeyWidth(KEY_WIDTH);
    
    addAndMakeVisible(keyboardComponent);
    addAndMakeVisible(oscParamsComponent);
    addAndMakeVisible(ampEnvParamsComponent);
    addAndMakeVisible(lfoParamsComponent);
    addAndMakeVisible(filterParamsComponent);
    addAndMakeVisible(driveParamsComponent);
    addAndMakeVisible(reverbParamsComponent);
    addAndMakeVisible(miscParamsComponent);
    addAndMakeVisible(scopeComponent);
    
    setSize (960, 540 + KEY_HEIGHT);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void SimpleSynthAudioProcessorEditor::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    
    keyboardComponent.setBounds(bounds.removeFromBottom(KEY_HEIGHT));

    juce::Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    {

        oscParamsComponent.setBounds(upperArea.removeFromLeft(280).reduced(PANEL_MARGIN));

        lfoParamsComponent.setBounds(upperArea.removeFromLeft(240).reduced(PANEL_MARGIN));

        ampEnvParamsComponent.setBounds(upperArea.removeFromLeft(240).reduced(PANEL_MARGIN));

        filterParamsComponent.setBounds(upperArea.reduced(PANEL_MARGIN));
    }
    
    juce::Rectangle<int> lowerArea = bounds;
    {

        scopeComponent.setBounds(lowerArea.removeFromLeft(420).reduced(PANEL_MARGIN));

        driveParamsComponent.setBounds(lowerArea.removeFromLeft(100).reduced(PANEL_MARGIN));

        reverbParamsComponent.setBounds(lowerArea.removeFromLeft(280).reduced(PANEL_MARGIN));

        miscParamsComponent.setBounds(lowerArea.reduced(PANEL_MARGIN));
    }
}
