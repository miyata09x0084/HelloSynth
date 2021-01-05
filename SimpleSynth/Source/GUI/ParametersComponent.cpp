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
    
    {
        float x = 0.0f, y = 0.0f, width = (float)getWidth(), height = (float)getHeight();
        g.setColour(PANEL_COLOUR);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }
    
    {
        juce::Rectangle<int> bounds = getLocalBounds();

        juce::Rectangle<int> textArea = bounds.removeFromTop(PANEL_NAME_HEIGHT).reduced(LOCAL_MARGIN);

        juce::String text("OSC MIX");
        juce::Colour textColour = juce::Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);

        g.drawText(text, textArea, juce::Justification::centred, true);
    }
}

void OscillatorParametersComponent::resized()
{
    float rowSize = 5.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;
    
    juce::Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);
    
    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);

        sineWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));

        sineWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    
    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        sawWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        sawWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }

    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        triWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        triWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }

    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        squareWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        squareWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }

    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        noiseLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        noiseLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void OscillatorParametersComponent::timerCallback()
{
    sineWaveLevelSlider.setValue(_oscParamsPtr->SineWaveLevel->get(), juce::dontSendNotification);
    sawWaveLevelSlider.setValue(_oscParamsPtr->SawWaveLevel->get(), juce::dontSendNotification);
    triWaveLevelSlider.setValue(_oscParamsPtr->TriWaveLevel->get(), juce::dontSendNotification);
    squareWaveLevelSlider.setValue(_oscParamsPtr->SquareWaveLevel->get(), juce::dontSendNotification);
    noiseLevelSlider.setValue(_oscParamsPtr->NoiseLevel->get(), juce::dontSendNotification);
}

void OscillatorParametersComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &sineWaveLevelSlider)
    {
        *_oscParamsPtr->SineWaveLevel = (float)sineWaveLevelSlider.getValue();
    }
    else if (slider == &sawWaveLevelSlider)
    {
        *_oscParamsPtr->SawWaveLevel = (float)sawWaveLevelSlider.getValue();
    }
    else if (slider == &triWaveLevelSlider)
    {
        *_oscParamsPtr->TriWaveLevel = (float)triWaveLevelSlider.getValue();
    }
    else if (slider == &squareWaveLevelSlider)
    {
        *_oscParamsPtr->SquareWaveLevel = (float)squareWaveLevelSlider.getValue();
    }
    else if (slider == &noiseLevelSlider)
    {
        *_oscParamsPtr->NoiseLevel = (float)noiseLevelSlider.getValue();
    }
}
