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
}
