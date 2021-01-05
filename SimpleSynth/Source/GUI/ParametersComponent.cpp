/*
  ==============================================================================

    ParametersComponent.cpp
    Created: 4 Jan 2021 3:06:03pm
    Author:  宮田亮

  ==============================================================================
*/

#include "ParametersComponent.h"

namespace {
    const juce::Colour PANEL_COLOUR = juce::Colour(36, 36, 36);
    const float PANEL_NAME_FONT_SIZE = 24.0f;
    const float PARAM_LABEL_FONT_SIZE = 16.0f;
    const int PANEL_NAME_HEIGHT = 42;
    const int LOCAL_MARGIN = 2;
}

OscillatorParametersComponent::OscillatorParametersComponent(OscillatorParameters* oscParams)
    : _oscParamsPtr(oscParams)
    , sineWaveLevelSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , sawWaveLevelSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , triWaveLevelSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , squareWaveLevelSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , noiseLevelSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    sineWaveLevelSlider.setRange(_oscParamsPtr->SineWaveLevel->range.start,_oscParamsPtr->SineWaveLevel->range.end, 0.01);
    sineWaveLevelSlider.setValue(_oscParamsPtr->SineWaveLevel->get(), juce::dontSendNotification);
    sineWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    sineWaveLevelSlider.setPopupMenuEnabled(true);
    sineWaveLevelSlider.addListener(this);
    addAndMakeVisible(sineWaveLevelSlider);

    sawWaveLevelSlider.setRange(_oscParamsPtr->SawWaveLevel->range.start, _oscParamsPtr->SawWaveLevel->range.end, 0.01);
    sawWaveLevelSlider.setValue(_oscParamsPtr->SawWaveLevel->get(), juce::dontSendNotification);
    sawWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    sawWaveLevelSlider.setPopupMenuEnabled(true);
    sawWaveLevelSlider.addListener(this);
    addAndMakeVisible(sawWaveLevelSlider);

    triWaveLevelSlider.setRange(_oscParamsPtr->TriWaveLevel->range.start, _oscParamsPtr->TriWaveLevel->range.end, 0.01);
    triWaveLevelSlider.setValue(_oscParamsPtr->TriWaveLevel->get(), juce::dontSendNotification);
    triWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    triWaveLevelSlider.setPopupMenuEnabled(true);
    triWaveLevelSlider.addListener(this);
    addAndMakeVisible(triWaveLevelSlider);

    squareWaveLevelSlider.setRange(_oscParamsPtr->SquareWaveLevel->range.start, _oscParamsPtr->SquareWaveLevel->range.end, 0.01);
    squareWaveLevelSlider.setValue(_oscParamsPtr->SquareWaveLevel->get(), juce::dontSendNotification);
    squareWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    squareWaveLevelSlider.setPopupMenuEnabled(true);
    squareWaveLevelSlider.addListener(this);
    addAndMakeVisible(squareWaveLevelSlider);

    noiseLevelSlider.setRange(_oscParamsPtr->NoiseLevel->range.start, _oscParamsPtr->NoiseLevel->range.end, 0.01);
    noiseLevelSlider.setValue(_oscParamsPtr->NoiseLevel->get(), juce::dontSendNotification);
    noiseLevelSlider.setPopupDisplayEnabled(true, true, this);
    noiseLevelSlider.setPopupMenuEnabled(true);
    noiseLevelSlider.addListener(this);
    addAndMakeVisible(noiseLevelSlider);
    
    juce::Font paramLabelFont = juce::Font(PARAM_LABEL_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Regular");
    
    sineWaveLevelLabel.setFont(paramLabelFont);
    sineWaveLevelLabel.setText("Sine", juce::dontSendNotification);
    sineWaveLevelLabel.setJustificationType(juce::Justification::centred);
    sineWaveLevelLabel.setEditable(false, false, false);
    
    addAndMakeVisible(sineWaveLevelLabel);

    sawWaveLevelLabel.setFont(paramLabelFont);
    sawWaveLevelLabel.setText("Saw", juce::dontSendNotification);
    sawWaveLevelLabel.setJustificationType(juce::Justification::centred);
    sawWaveLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(sawWaveLevelLabel);

    squareWaveLevelLabel.setFont(paramLabelFont);
    squareWaveLevelLabel.setText("Square", juce::dontSendNotification);
    squareWaveLevelLabel.setJustificationType(juce::Justification::centred);
    squareWaveLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(squareWaveLevelLabel);

    triWaveLevelLabel.setFont(paramLabelFont);
    triWaveLevelLabel.setText("Tri", juce::dontSendNotification);
    triWaveLevelLabel.setJustificationType(juce::Justification::centred);
    triWaveLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(triWaveLevelLabel);

    noiseLevelLabel.setFont(paramLabelFont);
    noiseLevelLabel.setText("Noise", juce::dontSendNotification);
    noiseLevelLabel.setJustificationType(juce::Justification::centred);
    noiseLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(noiseLevelLabel);
    
    startTimerHz(30.0f);
}

OscillatorParametersComponent::~OscillatorParametersComponent()
{}

void OscillatorParametersComponent::paint(juce::Graphics& g)
{
    juce::Font panelNameFont = juce::Font(PANEL_NAME_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Italic");
}
