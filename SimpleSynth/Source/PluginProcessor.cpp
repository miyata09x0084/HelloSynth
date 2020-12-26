/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "DSP/SimpleSound.h"
#include "DSP/SimpleVoice.h"

//==============================================================================
SimpleSynthAudioProcessor::SimpleSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    , oscParameters{
        new juce::AudioParameterFloat("SINEWAVE_LEVEL",   "SineWave-Level", 0.0f, 1.0f, 1.0f),
        new juce::AudioParameterFloat("SAWWAVE_LEVEL",    "SawWave-Level", 0.0f, 1.0f, 1.0f),
        new juce::AudioParameterFloat("TRIWAVE_LEVEL",    "TriWave-Level", 0.0f, 1.0f, 1.0f),
        new juce::AudioParameterFloat("SQUAREWAVE_LEVEL", "SquareWave-Level", 0.0f, 1.0f, 1.0f),
        new juce::AudioParameterFloat("NOISE_LEVEL", "Noise-Level",  0.0f, 1.0f, 0.0f)
    }
    , lfoParameters{
        new juce::AudioParameterChoice("LFO_TARGET", "Lfo-Target", LFO_TARGETS, 0),
        new juce::AudioParameterChoice("LFO_WAVE_TYPE", "Lfo-WaveType", LFO_WAVE_TYPES, 0),
        new juce::AudioParameterFloat("LFO_LEVEL", "Lfo-Level",  0.0f, 1.0f, 0.5f),
        new juce::AudioParameterFloat("LFO_SPEED", "Lfo-Speed",  0.0f, 20.0f, 0.2f)
    }
    , ampEnvParameters{
        new juce::AudioParameterFloat("AMPENV_ATTACK", "Attack", 0.01f, 3.0f, 0.1f),
        new juce::AudioParameterFloat("AMPENV_DECAY", "Decay",  0.01f, 3.0f, 0.1f),
        new juce::AudioParameterFloat("AMPENV_SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f),
        new juce::AudioParameterFloat("AMPENV_RELEASE", "Release", 0.01f, 3.0f, 0.1f)
    }
    , filterParameters{
        new juce::AudioParameterChoice("FILTER_TYPE", "FilterType", FILTER_TYPES, 0),
        new juce::AudioParameterFloat("FILTER_FREQUENCY", "Frequency", 20.f, 20000.0f, 20000.0f),
        new juce::AudioParameterFloat("FILTER_Q", "Q", 0.3f, 20.0f, 1.0f),
    }
    , reverbParameters{
        new juce::AudioParameterFloat("REVERB_ROOM_SIZE", "Room-Size",    0.0f, 1.0f, 0.0f),
        new juce::AudioParameterFloat("REVERB_DAMPING",   "Damping",      0.0f, 1.0f, 0.0f),
        new juce::AudioParameterFloat("REVERB_WET_LEVEL", "Wet-Level",    0.0f, 1.0f, 0.0f),
        new juce::AudioParameterFloat("REVERB_DRY_LEVEL", "Dry-Level",    0.0f, 1.0f, 1.0f),
        new juce::AudioParameterFloat("REVERB_WIDTH",     "Width",        0.0f, 1.0f, 0.0f),
        new juce::AudioParameterFloat("REVERB_FREEZE_MODE",  "Freeze-Mode",   0.0f, 1.0f, 0.0f)
    }
, driveParameter(new juce::AudioParameterFloat("DRIVE", "Drive", -24.f, 12.f, 0.0f))
, masterVolumePrameter(new juce::AudioParameterFloat("MASTER_VOLUME", "Volume", -36.f, 6.f, -3.0f))
, voiceSizeParameter(new juce::AudioParameterInt("VOICE_SIZE", "Voice-Size", 1, 128, 8))
, velocitySenseParameter(new juce::AudioParameterBool("VELOCITY_SENSE", "Velocity-Sense", true))
{
    oscParameters.addAllParameters(*this);
    lfoParameters.addAllParameters(*this);
    ampEnvParameters.addAllParameters(*this);
    addParameter(driveParameter);
    filterParameters.addAllParameters(*this);
    reverbParameters.addAllParameters(*this);
    addParameter(masterVolumePrameter);
    addParameter(voiceSizeParameter);
    addParameter(velocitySenseParameter);
}

SimpleSynthAudioProcessor::~SimpleSynthAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.clearSounds();
    synth.clearVoices();

    synth.setCurrentPlaybackSampleRate(sampleRate);

    juce::BigInteger canPlayNotes;
    canPlayNotes.setRange(0, 127, true);

    juce::BigInteger canPlayChannels;
    canPlayChannels.setRange(1, 16, true);

    synth.addSound(new SimpleSound(canPlayNotes, canPlayChannels));

    int numVoices = voiceSizeParameter->get();
    for (int i = 0; i < numVoices; ++i)
    {
        synth.addVoice(new SimpleVoice(&oscParameters, &lfoParameters,
            &ampEnvParameters, velocitySenseParameter));
    }
    
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    spec.maximumBlockSize = samplesPerBlock;

    iirFilter.prepare(spec);

    drive.prepare(spec);

    clipper.prepare(spec);
    clipper.functionToUse = clippingFunction;

    reverb.prepare(spec);

    limiter.prepare(spec);
    limiter.functionToUse = clippingFunction;

    masterVolume.prepare(spec);
}

void SimpleSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if ((int)voiceSizeParameter->get() != synth.getNumVoices()) {
        changeVoiceSize();
    }
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        buffer.clear(channel, 0, buffer.getNumSamples());
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());


    juce::dsp::AudioBlock<float> audioBlock(buffer);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    if (filterParameters.Type->getCurrentChoiceName() == "Low-Pass")
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(spec.sampleRate
            , filterParameters.Frequency->get()
            , filterParameters.Q->get()
        );
    }
    else if (filterParameters.Type->getCurrentChoiceName() == "High-Pass")
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate
            , filterParameters.Frequency->get()
            , filterParameters.Q->get()
        );
    }
    else if (filterParameters.Type->getCurrentChoiceName() == "Band-Pass")
    {
        *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeBandPass(spec.sampleRate
            , filterParameters.Frequency->get()
            , filterParameters.Q->get()
        );
    }
    iirFilter.process(context);

    drive.setGainDecibels(driveParameter->get());
    drive.process(context);

    clipper.process(context);

    juce::dsp::Reverb::Parameters reverbParam;
    reverbParam.roomSize = reverbParameters.RoomSize->get();
    reverbParam.damping = reverbParameters.Damping->get();
    reverbParam.wetLevel = reverbParameters.WetLevel->get();
    reverbParam.dryLevel = reverbParameters.DryLevel->get();
    reverbParam.width = reverbParameters.Width->get();
    reverbParam.freezeMode = reverbParameters.FreezeMode->get();
    reverb.setParameters(reverbParam);
    reverb.process(context);

    limiter.process(context);

    masterVolume.setGainDecibels(masterVolumePrameter->get());
    masterVolume.process(context);
}

//==============================================================================
bool SimpleSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleSynthAudioProcessor::createEditor()
{
    return new SimpleSynthAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement("SimpleSynthParameters"));

    oscParameters.saveParameters(*xml);
    lfoParameters.saveParameters(*xml);
    ampEnvParameters.saveParameters(*xml);
    filterParameters.saveParameters(*xml);
    reverbParameters.saveParameters(*xml);

    xml->setAttribute(driveParameter->paramID, (double)driveParameter->get());
    xml->setAttribute(masterVolumePrameter->paramID, (double)masterVolumePrameter->get());
    xml->setAttribute(voiceSizeParameter->paramID, voiceSizeParameter->get());
    xml->setAttribute(velocitySenseParameter->paramID, velocitySenseParameter->get());

    copyXmlToBinary(*xml, destData);
}

void SimpleSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void SimpleSynthAudioProcessor::changeVoiceSize()
{
    while (synth.getNumVoices() != voiceSizeParameter->get())
    {
        if (synth.getNumVoices() > voiceSizeParameter->get())
        {
            synth.removeVoice(synth.getNumVoices() - 1);
        }
        else
        {
            synth.addVoice(new SimpleVoice(&oscParameters, &lfoParameters, &ampEnvParameters, velocitySenseParameter));
        }
    }
}

float SimpleSynthAudioProcessor::clippingFunction(float inputValue)
{
    float threshold = tanhf(inputValue);
    float outputValue = inputValue;

    if (abs(inputValue) >= abs(threshold)) outputValue = threshold;

    return outputValue;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSynthAudioProcessor();
}
