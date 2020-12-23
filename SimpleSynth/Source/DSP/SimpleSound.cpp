/*
  ==============================================================================

    SimpleSound.cpp
    Created: 21 Dec 2020 4:00:06pm
    Author:  宮田亮

  ==============================================================================
*/

#include "SimpleSound.h"

SimpleSound::SimpleSound(const juce::BigInteger& notes, const juce::BigInteger& channels)
    : midiNotes(notes), midiChannels(channels)
{
}

