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

AmpEnvelopeParametersComponent::AmpEnvelopeParametersComponent(AmpEnvelopeParameters * ampEnvParams)
    :_ampEnvParamsPtr(ampEnvParams)
    , attackSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , decaySlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , sustainSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , releaseSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    juce::Font paramLabelFont = juce::Font(PARAM_LABEL_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Regular");

    attackSlider.setRange(_ampEnvParamsPtr->Attack->range.start, _ampEnvParamsPtr->Attack->range.end, 0.01);
    attackSlider.setValue(_ampEnvParamsPtr->Attack->get(), juce::dontSendNotification);
    attackSlider.setPopupDisplayEnabled(true, true, this);
    attackSlider.setPopupMenuEnabled(true);
    attackSlider.setTextValueSuffix(" seconds");
    attackSlider.addListener(this);
    addAndMakeVisible(attackSlider);

    decaySlider.setRange(_ampEnvParamsPtr->Decay->range.start, _ampEnvParamsPtr->Decay->range.end, 0.01);
    decaySlider.setValue(_ampEnvParamsPtr->Decay->get(), juce::dontSendNotification);
    decaySlider.setPopupDisplayEnabled(true, true, this);
    decaySlider.setPopupMenuEnabled(true);
    decaySlider.setTextValueSuffix(" seconds");
    decaySlider.addListener(this);
    addAndMakeVisible(decaySlider);

    sustainSlider.setRange(_ampEnvParamsPtr->Sustain->range.start, _ampEnvParamsPtr->Sustain->range.end, 0.01);
    sustainSlider.setValue(_ampEnvParamsPtr->Sustain->get(), juce::dontSendNotification);
    sustainSlider.setPopupDisplayEnabled(true, true, this);
    sustainSlider.setPopupMenuEnabled(true);
    sustainSlider.addListener(this);
    addAndMakeVisible(sustainSlider);

    releaseSlider.setRange(_ampEnvParamsPtr->Release->range.start, _ampEnvParamsPtr->Release->range.end, 0.01);
    releaseSlider.setValue(_ampEnvParamsPtr->Release->get(), juce::dontSendNotification);
    releaseSlider.setPopupDisplayEnabled(true, true, this);
    releaseSlider.setPopupMenuEnabled(true);
    releaseSlider.setTextValueSuffix(" seconds");
    releaseSlider.addListener(this);
    addAndMakeVisible(releaseSlider);

    attackLabel.setFont(paramLabelFont);
    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);
    attackLabel.setEditable(false, false, false);
    addAndMakeVisible(attackLabel);

    decayLabel.setFont(paramLabelFont);
    decayLabel.setText("Decay", juce::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centred);
    decayLabel.setEditable(false, false, false);
    addAndMakeVisible(decayLabel);

    sustainLabel.setFont(paramLabelFont);
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    sustainLabel.setJustificationType(juce::Justification::centred);
    sustainLabel.setEditable(false, false, false);
    addAndMakeVisible(sustainLabel);

    releaseLabel.setFont(paramLabelFont);
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setEditable(false, false, false);
    addAndMakeVisible(releaseLabel);

    startTimerHz(30.0f);
}

AmpEnvelopeParametersComponent::~AmpEnvelopeParametersComponent()
{}

void AmpEnvelopeParametersComponent::paint(juce::Graphics & g)
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

        juce::String text("AMP EG");
        juce::Colour textColour = juce::Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, juce::Justification::centred, false);
    }
}

void AmpEnvelopeParametersComponent::resized()
{
    float rowSize = 4.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    juce::Rectangle<int> bounds = getLocalBounds(); // コンポーネント基準の値
    bounds.removeFromTop(PANEL_NAME_HEIGHT);
    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        attackLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        attackSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        decayLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        decaySlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        sustainLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        sustainSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        releaseLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        releaseSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void AmpEnvelopeParametersComponent::timerCallback()
{
    attackSlider.setValue(_ampEnvParamsPtr->Attack->get(), juce::dontSendNotification);
    decaySlider.setValue(_ampEnvParamsPtr->Decay->get(), juce::dontSendNotification);
    sustainSlider.setValue(_ampEnvParamsPtr->Sustain->get(), juce::dontSendNotification);
    releaseSlider.setValue(_ampEnvParamsPtr->Release->get(), juce::dontSendNotification);
}

void AmpEnvelopeParametersComponent::sliderValueChanged(juce::Slider * slider)
{
    if (slider == &attackSlider)
    {
        *_ampEnvParamsPtr->Attack = (float)attackSlider.getValue();
    }
    else if (slider == &decaySlider)
    {
        *_ampEnvParamsPtr->Decay = (float)decaySlider.getValue();
    }
    else if (slider == &sustainSlider)
    {
        *_ampEnvParamsPtr->Sustain = (float)sustainSlider.getValue();
    }
    else if (slider == &releaseSlider)
    {
        *_ampEnvParamsPtr->Release = (float)releaseSlider.getValue();
    }
}

LfoParametersComponent::LfoParametersComponent(LfoParameters * lfoParams)
    :_lfoParamsPtr(lfoParams)
    , targetSelector("LFO-Target")
    , waveTypeSelector("LFO-WaveType")
    , amountSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , speedSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    juce::Font paramLabelFont = juce::Font(PARAM_LABEL_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Regular");

    targetSelector.addItemList(_lfoParamsPtr->LfoTarget->getAllValueStrings(), 1);
    targetSelector.setSelectedItemIndex(_lfoParamsPtr->LfoTarget->getIndex(), juce::dontSendNotification);
    targetSelector.setJustificationType(juce::Justification::centred);
    targetSelector.addListener(this);
    addAndMakeVisible(targetSelector);

    waveTypeSelector.addItemList(_lfoParamsPtr->LfoWaveType->getAllValueStrings(), 1);
    waveTypeSelector.setSelectedItemIndex(_lfoParamsPtr->LfoWaveType->getIndex(), juce::dontSendNotification);
    waveTypeSelector.setJustificationType(juce::Justification::centred);
    waveTypeSelector.addListener(this);
    addAndMakeVisible(waveTypeSelector);

    amountSlider.setRange(_lfoParamsPtr->LfoAmount->range.start, _lfoParamsPtr->LfoAmount->range.end, 0.01);
    amountSlider.setValue(_lfoParamsPtr->LfoAmount->get(), juce::dontSendNotification);
    amountSlider.setDoubleClickReturnValue(true, _lfoParamsPtr->LfoAmount->range.end);
    amountSlider.setPopupDisplayEnabled(true, true, this);
    amountSlider.setPopupMenuEnabled(true);
    amountSlider.addListener(this);
    addAndMakeVisible(amountSlider);

    speedSlider.setRange(_lfoParamsPtr->LfoSpeed->range.start, _lfoParamsPtr->LfoSpeed->range.end, 0.01);
    speedSlider.setValue(_lfoParamsPtr->LfoSpeed->get(), juce::dontSendNotification);
    speedSlider.setSkewFactor(0.5, false);
    speedSlider.setPopupDisplayEnabled(true, true, this);
    speedSlider.setPopupMenuEnabled(true);
    speedSlider.setTextValueSuffix(" hz");
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);

    targetLabel.setFont(paramLabelFont);
    targetLabel.setText("Target", juce::dontSendNotification);
    targetLabel.setJustificationType(juce::Justification::centred);
    targetLabel.setEditable(false, false, false);
    addAndMakeVisible(targetLabel);

    waveTypeLabel.setFont(paramLabelFont);
    waveTypeLabel.setText("WaveType", juce::dontSendNotification);
    waveTypeLabel.setJustificationType(juce::Justification::centred);
    waveTypeLabel.setEditable(false, false, false);
    addAndMakeVisible(waveTypeLabel);

    amountLabel.setFont(paramLabelFont);
    amountLabel.setText("Amount", juce::dontSendNotification);
    amountLabel.setJustificationType(juce::Justification::centred);
    amountLabel.setEditable(false, false, false);
    addAndMakeVisible(amountLabel);

    speedLabel.setFont(paramLabelFont);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.setJustificationType(juce::Justification::centred);
    speedLabel.setEditable(false, false, false);
    addAndMakeVisible(speedLabel);

    startTimerHz(30.0f);
}

LfoParametersComponent::~LfoParametersComponent()
{}

void LfoParametersComponent::paint(juce::Graphics & g)
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

        juce::String text("LFO");
        juce::Colour textColour = juce::Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, juce::Justification::centred, false);
    }
}

void LfoParametersComponent::resized()
{
    float rowSize = 2.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    juce::Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);

    juce::Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    {
        juce::Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        targetLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        targetSelector.setBounds(area.removeFromTop(labelHeight * 2).reduced(LOCAL_MARGIN * 2));
    }
    {
        juce::Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        amountLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        amountSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }

    juce::Rectangle<int> lowerArea = bounds;
    {
        juce::Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        waveTypeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        waveTypeSelector.setBounds(area.removeFromTop(labelHeight * 2).reduced(LOCAL_MARGIN * 2));
    }
    {
        juce::Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        speedLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        speedSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void LfoParametersComponent::timerCallback()
{
    targetSelector.setSelectedItemIndex(_lfoParamsPtr->LfoTarget->getIndex(), juce::dontSendNotification);
    waveTypeSelector.setSelectedItemIndex(_lfoParamsPtr->LfoWaveType->getIndex(), juce::dontSendNotification);
    amountSlider.setValue(_lfoParamsPtr->LfoAmount->get(), juce::dontSendNotification);
    speedSlider.setValue(_lfoParamsPtr->LfoSpeed->get(), juce::dontSendNotification);
}

void LfoParametersComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &amountSlider)
    {
        *_lfoParamsPtr->LfoAmount = (float)amountSlider.getValue();
    }
    else if (slider == &speedSlider)
    {
        *_lfoParamsPtr->LfoSpeed = (float)speedSlider.getValue();
    }
}

void LfoParametersComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &targetSelector)
    {
        *_lfoParamsPtr->LfoTarget = targetSelector.getSelectedItemIndex();
    }
    else if (comboBoxThatHasChanged == &waveTypeSelector)
    {
        *_lfoParamsPtr->LfoWaveType = waveTypeSelector.getSelectedItemIndex();
    }
}

FilterParametersComponent::FilterParametersComponent(FilterParameters * filterParams)
    :_filterParamsPtr(filterParams)
    , typeSelector("Filter-Type")
, frequencySlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , qSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    juce::Font paramLabelFont = juce::Font(PARAM_LABEL_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Regular");

    typeSelector.addItemList(_filterParamsPtr->Type->getAllValueStrings(), 1);
    typeSelector.setSelectedItemIndex(_filterParamsPtr->Type->getIndex(), juce::dontSendNotification);
    typeSelector.setJustificationType(juce::Justification::centred);
    typeSelector.addListener(this);
    addAndMakeVisible(typeSelector);

    frequencySlider.setRange(_filterParamsPtr->Frequency->range.start,
                             _filterParamsPtr->Frequency->range.end, 0.01);
    frequencySlider.setValue(_filterParamsPtr->Frequency->get(), juce::dontSendNotification);
    frequencySlider.setSkewFactor(0.3, false);
    frequencySlider.setPopupDisplayEnabled(true, true, this);
    frequencySlider.setPopupMenuEnabled(true);
    frequencySlider.setTextValueSuffix(" hz");
    frequencySlider.addListener(this);
    addAndMakeVisible(frequencySlider);

    qSlider.setRange(_filterParamsPtr->Q->range.start, _filterParamsPtr->Q->range.end, 0.01);
    qSlider.setValue(_filterParamsPtr->Q->get(), juce::dontSendNotification);
    qSlider.setPopupDisplayEnabled(true, true, this);
    qSlider.setPopupMenuEnabled(true);
    qSlider.addListener(this);
    addAndMakeVisible(qSlider);

    typeLabel.setFont(paramLabelFont);
    typeLabel.setText("Type", juce::dontSendNotification);
    typeLabel.setJustificationType(juce::Justification::centred);
    typeLabel.setEditable(false, false, false);
    addAndMakeVisible(typeLabel);

    frequencyLabel.setFont(paramLabelFont);
    frequencyLabel.setText("Frequency", juce::dontSendNotification);
    frequencyLabel.setJustificationType(juce::Justification::centred);
    frequencyLabel.setEditable(false, false, false);
    addAndMakeVisible(frequencyLabel);

    qLabel.setFont(paramLabelFont);
    qLabel.setText("Q", juce::dontSendNotification);
    qLabel.setJustificationType(juce::Justification::centred);
    qLabel.setEditable(false, false, false);
    addAndMakeVisible(qLabel);

    startTimerHz(30.0f);
}

FilterParametersComponent::~FilterParametersComponent()
{}

void FilterParametersComponent::paint(juce::Graphics & g)
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

        juce::String text("FILTER");
        juce::Colour textColour = juce::Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, juce::Justification::centred, false);
    }

}

void FilterParametersComponent::resized()
{
    float rowSize = 2.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    juce::Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);

    juce::Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.5f);
    {
        juce::Rectangle<int> area = upperArea;
        typeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        typeSelector.setBounds(area.removeFromTop(labelHeight * 2).reduced(LOCAL_MARGIN * 2));
    }
    juce::Rectangle<int> lowerArea = bounds;
    {
        juce::Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        frequencyLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        frequencySlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        qLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        qSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void FilterParametersComponent::timerCallback()
{
    typeSelector.setSelectedItemIndex(_filterParamsPtr->Type->getIndex(), juce::dontSendNotification);
    frequencySlider.setValue(_filterParamsPtr->Frequency->get(), juce::dontSendNotification);
    qSlider.setValue(_filterParamsPtr->Q->get(), juce::dontSendNotification);
}

void FilterParametersComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &frequencySlider)
    {
        *_filterParamsPtr->Frequency = (float)frequencySlider.getValue();
    }
    else if (slider == &qSlider)
    {
        *_filterParamsPtr->Q = (float)qSlider.getValue();
    }
}

void FilterParametersComponent::comboBoxChanged(juce::ComboBox * comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &typeSelector)
    {
        *_filterParamsPtr->Type = typeSelector.getSelectedItemIndex();
    }
}

DriveParametersComponent::DriveParametersComponent(juce::AudioParameterFloat* driveParam)
    :_driveParamPtr(driveParam)
    , gainSlider(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    gainSlider.setRange(_driveParamPtr->range.start, _driveParamPtr->range.end, 0.01);
    gainSlider.setValue(_driveParamPtr->get(), juce::dontSendNotification);
    gainSlider.setPopupDisplayEnabled(true, true, this);
    gainSlider.setDoubleClickReturnValue(true, 0.0);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);

    juce::Font paramLabelFont = juce::Font(PARAM_LABEL_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Regular");

    gainLabel.setFont(paramLabelFont);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.setEditable(false, false, false);
    addAndMakeVisible(gainLabel);

    startTimerHz(30.0f);
}

DriveParametersComponent::~DriveParametersComponent()
{}

void DriveParametersComponent::paint(juce::Graphics & g)
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
        juce::String text("DRIVE");
        juce::Colour textColour = juce::Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, juce::Justification::centred, false);
    }
}

void DriveParametersComponent::resized()
{
    float rowSize = 1.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    juce::Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);
    {
        juce::Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        gainLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        gainSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void DriveParametersComponent::timerCallback()
{
    gainSlider.setValue(_driveParamPtr->get(), juce::dontSendNotification);
}

void DriveParametersComponent::sliderValueChanged(juce::Slider * slider)
{
    if (slider == &gainSlider)
    {
        *_driveParamPtr = (float)gainSlider.getValue();
    }
}

ReverbParametersComponent::ReverbParametersComponent(ReverbParameters * reverbParams)
    : _reverbParamsPtr(reverbParams)
    , roomSizeSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , dampingSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , wetLevelSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , dryLevelSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , widthSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , freezeModeSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    juce::Font paramLabelFont = juce::Font(PARAM_LABEL_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Regular");

    roomSizeSlider.setRange(_reverbParamsPtr->RoomSize->range.start, _reverbParamsPtr->RoomSize->range.end, 0.01);
    roomSizeSlider.setValue(_reverbParamsPtr->RoomSize->get(), juce::dontSendNotification);
    roomSizeSlider.setPopupDisplayEnabled(true, true, this);
    roomSizeSlider.setPopupMenuEnabled(true);
    roomSizeSlider.addListener(this);
    addAndMakeVisible(roomSizeSlider);

    dampingSlider.setRange(_reverbParamsPtr->Damping->range.start, _reverbParamsPtr->Damping->range.end, 0.01);
    dampingSlider.setValue(_reverbParamsPtr->Damping->get(), juce::dontSendNotification);
    dampingSlider.setPopupDisplayEnabled(true, true, this);
    dampingSlider.setPopupMenuEnabled(true);
    dampingSlider.addListener(this);
    addAndMakeVisible(dampingSlider);

    wetLevelSlider.setRange(_reverbParamsPtr->WetLevel->range.start, _reverbParamsPtr->WetLevel->range.end, 0.01);
    wetLevelSlider.setValue(_reverbParamsPtr->WetLevel->get(), juce::dontSendNotification);
    wetLevelSlider.setPopupDisplayEnabled(true, true, this);
    wetLevelSlider.setPopupMenuEnabled(true);
    wetLevelSlider.addListener(this);
    addAndMakeVisible(wetLevelSlider);

    dryLevelSlider.setRange(_reverbParamsPtr->DryLevel->range.start, _reverbParamsPtr->DryLevel->range.end, 0.01);
    dryLevelSlider.setValue(_reverbParamsPtr->DryLevel->get(), juce::dontSendNotification);
    dryLevelSlider.setPopupDisplayEnabled(true, true, this);
    dryLevelSlider.setPopupMenuEnabled(true);
    dryLevelSlider.addListener(this);
    addAndMakeVisible(dryLevelSlider);

    widthSlider.setRange(_reverbParamsPtr->Width->range.start, _reverbParamsPtr->Width->range.end, 0.01);
    widthSlider.setValue(_reverbParamsPtr->Width->get(), juce::dontSendNotification);
    widthSlider.setPopupDisplayEnabled(true, true, this);
    widthSlider.setPopupMenuEnabled(true);
    widthSlider.addListener(this);
    addAndMakeVisible(widthSlider);

    freezeModeSlider.setRange(_reverbParamsPtr->FreezeMode->range.start, _reverbParamsPtr->FreezeMode->range.end, 0.01);
    freezeModeSlider.setValue(_reverbParamsPtr->FreezeMode->get(), juce::dontSendNotification);
    freezeModeSlider.setPopupDisplayEnabled(true, true, this);
    freezeModeSlider.setDoubleClickReturnValue(true, 0.0);
    freezeModeSlider.setPopupMenuEnabled(true);
    freezeModeSlider.addListener(this);
    addAndMakeVisible(freezeModeSlider);

    roomSizeLabel.setFont(paramLabelFont);
    roomSizeLabel.setText("RoomSize", juce::dontSendNotification);
    roomSizeLabel.setJustificationType(juce::Justification::centred);
    roomSizeLabel.setEditable(false, false, false);
    addAndMakeVisible(roomSizeLabel);

    dampingLabel.setFont(paramLabelFont);
    dampingLabel.setText("Damping", juce::dontSendNotification);
    dampingLabel.setJustificationType(juce::Justification::centred);
    dampingLabel.setEditable(false, false, false);
    addAndMakeVisible(dampingLabel);

    wetLevelLabel.setFont(paramLabelFont);
    wetLevelLabel.setText("WetLevel", juce::dontSendNotification);
    wetLevelLabel.setJustificationType(juce::Justification::centred);
    wetLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(wetLevelLabel);

    dryLevelLabel.setFont(paramLabelFont);
    dryLevelLabel.setText("DryLevel", juce::dontSendNotification);
    dryLevelLabel.setJustificationType(juce::Justification::centred);
    dryLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(dryLevelLabel);

    widthLabel.setFont(paramLabelFont);
    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centred);
    widthLabel.setEditable(false, false, false);
    addAndMakeVisible(widthLabel);

    freezeModeLabel.setFont(paramLabelFont);
    freezeModeLabel.setText("Freeze", juce::dontSendNotification);
    freezeModeLabel.setJustificationType(juce::Justification::centred);
    freezeModeLabel.setEditable(false, false, false);
    addAndMakeVisible(freezeModeLabel);

    startTimerHz(30.0f);
}

ReverbParametersComponent::~ReverbParametersComponent()
{}

void ReverbParametersComponent::paint(juce::Graphics & g)
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
        juce::String text("REVERB");
        juce::Colour textColour = juce::Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, juce::Justification::centred, false);
    }
}

void ReverbParametersComponent::resized()
{
    float rowSize = 3.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    juce::Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);

    juce::Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    {
        juce::Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        roomSizeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        roomSizeSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        dampingLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        dampingSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        widthLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        widthSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }

    juce::Rectangle<int> lowerArea = bounds;
    {
        juce::Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        wetLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        wetLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        dryLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        dryLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        juce::Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        freezeModeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        freezeModeSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void ReverbParametersComponent::timerCallback()
{
    roomSizeSlider.setValue(_reverbParamsPtr->RoomSize->get(), juce::dontSendNotification);
    dampingSlider.setValue(_reverbParamsPtr->Damping->get(), juce::dontSendNotification);
    wetLevelSlider.setValue(_reverbParamsPtr->WetLevel->get(), juce::dontSendNotification);
    dryLevelSlider.setValue(_reverbParamsPtr->DryLevel->get(), juce::dontSendNotification);
    widthSlider.setValue(_reverbParamsPtr->Width->get(), juce::dontSendNotification);
    freezeModeSlider.setValue(_reverbParamsPtr->FreezeMode->get(), juce::dontSendNotification);
}

void ReverbParametersComponent::sliderValueChanged(juce::Slider * slider)
{
    if (slider == &roomSizeSlider)
    {
        *_reverbParamsPtr->RoomSize = (float)roomSizeSlider.getValue();
    }
    else if (slider == &dampingSlider)
    {
        *_reverbParamsPtr->Damping = (float)dampingSlider.getValue();
    }
    else if (slider == &wetLevelSlider)
    {
        *_reverbParamsPtr->WetLevel = (float)wetLevelSlider.getValue();
    }
    else if (slider == &dryLevelSlider)
    {
        *_reverbParamsPtr->DryLevel = (float)dryLevelSlider.getValue();
    }
    else if (slider == &widthSlider)
    {
        *_reverbParamsPtr->Width = (float)widthSlider.getValue();
    }
    else if (slider == &freezeModeSlider)
    {
        *_reverbParamsPtr->FreezeMode = (float)freezeModeSlider.getValue();
    }
}

MiscParametersComponent::MiscParametersComponent(juce::AudioParameterFloat* masterVolumeParam,
                                                 juce::AudioParameterInt* voiceSizeParam,
                                                juce::AudioParameterBool* velocitySenseParam)
    :_masterVolumeParamPtr(masterVolumeParam)
    , _voiceSizeParamPtr(voiceSizeParam)
    , _velocitySenseParamPtr(velocitySenseParam)
    , masterVolumeSlider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , voiceSizeSlider(juce::Slider::SliderStyle::IncDecButtons, juce::Slider::TextEntryBoxPosition::TextBoxRight)
    , velocitySenseButton()
{
    juce::Font paramLabelFont = juce::Font(PARAM_LABEL_FONT_SIZE, juce::Font::plain).withTypefaceStyle("Regular");

    masterVolumeSlider.setRange(_masterVolumeParamPtr->range.start,
                                _masterVolumeParamPtr->range.end, 0.01);
    masterVolumeSlider.setValue(_masterVolumeParamPtr->get(), juce::dontSendNotification);
    masterVolumeSlider.setPopupDisplayEnabled(true, true, this);
    masterVolumeSlider.setPopupMenuEnabled(true);
    masterVolumeSlider.setDoubleClickReturnValue(true, 0.0);
    masterVolumeSlider.setTextValueSuffix(" dB");
    masterVolumeSlider.addListener(this);
    addAndMakeVisible(masterVolumeSlider);

    voiceSizeSlider.setRange(_voiceSizeParamPtr->getRange().getStart(),
                             _voiceSizeParamPtr->getRange().getEnd(), 1.0);
    voiceSizeSlider.setValue(_voiceSizeParamPtr->get(), juce::dontSendNotification);
    voiceSizeSlider.setTooltip("Size of synthesiser voice");
    voiceSizeSlider.addListener(this);
    addAndMakeVisible(voiceSizeSlider);

    velocitySenseButton.setButtonText("Key Velocity Sense");
    velocitySenseButton.addListener(this);
    addAndMakeVisible(velocitySenseButton);

    masterVolumeLabel.setFont(paramLabelFont);
    masterVolumeLabel.setText("Volume", juce::dontSendNotification);
    masterVolumeLabel.setJustificationType(juce::Justification::centred);
    masterVolumeLabel.setEditable(false, false, false);
    addAndMakeVisible(masterVolumeLabel);

    voiceSizeLabel.setFont(paramLabelFont);
    voiceSizeLabel.setText("Voice Size", juce::dontSendNotification);
    voiceSizeLabel.setJustificationType(juce::Justification::centred);
    voiceSizeLabel.setEditable(false, false, false);
    addAndMakeVisible(voiceSizeLabel);

    startTimerHz(30.0f);
}

MiscParametersComponent::~MiscParametersComponent()
{}

void MiscParametersComponent::paint(juce::Graphics & g)
{
    {
        int x = 0.0f, y = 0.0f, width = getWidth(), height = getHeight();
        g.setColour(PANEL_COLOUR);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }
}

void MiscParametersComponent::resized()
{
    float columnSize = 7.0f;
    float divide = 1.0f / columnSize;
    int labelHeight = 20;

    juce::Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(4);
    {
        juce::Rectangle<int> area = bounds.removeFromTop(getHeight() * divide * 3);
        masterVolumeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        masterVolumeSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }

    {
        juce::Rectangle<int> area = bounds.removeFromTop(getHeight() * divide * 2);
        voiceSizeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        voiceSizeSlider.setBounds(area.reduced(LOCAL_MARGIN));
        voiceSizeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false,
                                        area.getWidth() * 0.2, voiceSizeSlider.getHeight());
    }

    {
        juce::Rectangle<int> area = bounds.removeFromTop(getHeight() * divide * 2);
        velocitySenseButton.setBounds(area.reduced(LOCAL_MARGIN));
    }

}

void MiscParametersComponent::timerCallback()
{
    masterVolumeSlider.setValue(_masterVolumeParamPtr->get(), juce::dontSendNotification);
    voiceSizeSlider.setValue(_voiceSizeParamPtr->get(), juce::dontSendNotification);
    velocitySenseButton.setToggleState(_velocitySenseParamPtr->get(), juce::dontSendNotification);
}

void MiscParametersComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &masterVolumeSlider)
    {
        *_masterVolumeParamPtr = (float)masterVolumeSlider.getValue();
    }
    else if (slider == &voiceSizeSlider)
    {
        *_voiceSizeParamPtr = (int)voiceSizeSlider.getValue();
    }
}

void MiscParametersComponent::buttonClicked(juce::Button* button)
{
    if (button == &velocitySenseButton)
    {
        *_velocitySenseParamPtr = velocitySenseButton.getToggleState();
    }
}
