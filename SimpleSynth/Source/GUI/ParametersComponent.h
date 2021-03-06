/*
  ==============================================================================

    ParametersComponent.h
    Created: 4 Jan 2021 3:06:03pm
    Author:  宮田亮

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../DSP/SimpleSynthParameters.h"

class OscillatorParametersComponent : public juce::Component, juce::Slider::Listener, private juce::Timer
{
public:
    OscillatorParametersComponent(OscillatorParameters* oscParams);
    virtual ~OscillatorParametersComponent();
    
    virtual void paint(juce::Graphics& g) override;
    
    virtual void resized() override;
    
private:
    OscillatorParametersComponent();
    
    virtual void sliderValueChanged(juce::Slider* slider) override;
    
    virtual void timerCallback() override;
    
    OscillatorParameters* _oscParamsPtr;
    
    juce::Slider sineWaveLevelSlider;
    juce::Slider sawWaveLevelSlider;
    juce::Slider triWaveLevelSlider;
    juce::Slider squareWaveLevelSlider;
    juce::Slider noiseLevelSlider;
    
    juce::Label sineWaveLevelLabel;
    juce::Label sawWaveLevelLabel;
    juce::Label triWaveLevelLabel;
    juce::Label squareWaveLevelLabel;
    juce::Label noiseLevelLabel;
};

class AmpEnvelopeParametersComponent : public juce::Component, juce::Slider::Listener, private juce::Timer
{
public:
    AmpEnvelopeParametersComponent(AmpEnvelopeParameters* ampEnvParams);
    virtual ~AmpEnvelopeParametersComponent();

    virtual void paint(juce::Graphics& g) override;
    virtual void resized() override;

private:
    AmpEnvelopeParametersComponent();

    virtual void timerCallback() override;
    virtual void sliderValueChanged(juce::Slider* slider) override;

    AmpEnvelopeParameters* _ampEnvParamsPtr;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
};

class LfoParametersComponent : public juce::Component, juce::Slider::Listener, juce::ComboBox::Listener, private juce::Timer
{
public:
    LfoParametersComponent(LfoParameters* lfoParams);
    virtual ~LfoParametersComponent();
    virtual void paint(juce::Graphics& g) override;
    virtual void resized() override;

private:
    LfoParametersComponent();
    virtual void timerCallback() override;
    virtual void sliderValueChanged(juce::Slider* slider) override;
    virtual void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    LfoParameters* _lfoParamsPtr;

    juce::ComboBox targetSelector;
    juce::ComboBox waveTypeSelector;

    juce::Slider amountSlider;
    juce::Slider speedSlider;

    juce::Label targetLabel;
    juce::Label waveTypeLabel;
    juce::Label amountLabel;
    juce::Label speedLabel;
};

class FilterParametersComponent : public juce::Component, juce::Slider::Listener, juce::ComboBox::Listener, private juce::Timer
{
public:
    FilterParametersComponent(FilterParameters* filterParams);
    virtual ~FilterParametersComponent();
    virtual void paint(juce::Graphics& g) override;
    virtual void resized() override;

private:
    FilterParametersComponent();
    virtual void timerCallback() override;
    virtual void sliderValueChanged(juce::Slider* slider) override;
    virtual void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    FilterParameters* _filterParamsPtr;

    juce::ComboBox typeSelector;

    juce::Slider frequencySlider;
    juce::Slider qSlider;

    juce::Label typeLabel;
    juce::Label frequencyLabel;
    juce::Label qLabel;
};

class DriveParametersComponent : public juce::Component, juce::Slider::Listener, private juce::Timer
{
public:
    DriveParametersComponent(juce::AudioParameterFloat* driveParam);
    virtual ~DriveParametersComponent();
    virtual void paint(juce::Graphics& g) override;
    virtual void resized() override;

private:
    DriveParametersComponent();
    virtual void timerCallback() override;
    virtual void sliderValueChanged(juce::Slider* slider) override;

    juce::AudioParameterFloat* _driveParamPtr;

    juce::Slider gainSlider;

    juce::Label gainLabel;
};

class ReverbParametersComponent : public juce::Component, juce::Slider::Listener, private juce::Timer
{
public:
    ReverbParametersComponent(ReverbParameters* reverbParams);
    virtual ~ReverbParametersComponent();
    virtual void paint(juce::Graphics& g) override;
    virtual void resized() override;

private:
    ReverbParametersComponent();
    virtual void timerCallback() override;
    virtual void sliderValueChanged(juce::Slider* slider) override;

    ReverbParameters* _reverbParamsPtr;
    
    juce::Slider roomSizeSlider;
    juce::Slider dampingSlider;
    juce::Slider wetLevelSlider;
    juce::Slider dryLevelSlider;
    juce::Slider widthSlider;
    juce::Slider freezeModeSlider;
    
    juce::Label roomSizeLabel;
    juce::Label dampingLabel;
    juce::Label wetLevelLabel;
    juce::Label dryLevelLabel;
    juce::Label widthLabel;
    juce::Label freezeModeLabel;
};

class MiscParametersComponent : public juce::Component, juce::Slider::Listener, juce::Button::Listener, private juce::Timer
{
public:
    MiscParametersComponent(juce::AudioParameterFloat* masterVolumeParam,
                            juce::AudioParameterInt* voiceSizeParam,
                            juce::AudioParameterBool* velocitySenseParam);
    virtual ~MiscParametersComponent();
    virtual void paint(juce::Graphics& g) override;
    virtual void resized() override;

private:
    MiscParametersComponent();
    virtual void timerCallback() override;
    virtual void sliderValueChanged(juce::Slider* slider) override;
    virtual void buttonClicked(juce::Button* button) override;

    juce::AudioParameterFloat* _masterVolumeParamPtr;
    juce::AudioParameterInt* _voiceSizeParamPtr;
    juce::AudioParameterBool* _velocitySenseParamPtr;

    juce::Slider masterVolumeSlider;
    juce::Slider voiceSizeSlider;
    
    juce::ToggleButton velocitySenseButton;
    
    juce::Label masterVolumeLabel;
    juce::Label voiceSizeLabel;
};
