/*
  ==============================================================================

    SimpleSound.h
    Created: 21 Dec 2020 4:00:06pm
    Author:  宮田亮

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleSound : public juce::SynthesiserSound
{
public:
    SimpleSound(const juce::BigInteger& notes, const juce::BigInteger& channels);

    virtual ~SimpleSound();

    virtual bool appliesToNote(int midiNoteNumber) override;
    virtual bool appliesToChannel(int midiChannel) override;

private:
    juce::BigInteger midiNotes;
    juce::BigInteger midiChannels;

};
