/*
  ==============================================================================

    ScopeComponent.cpp
    Created: 5 Jan 2021 3:21:13pm
    Author:  宮田亮

  ==============================================================================
*/

#include "ScopeComponent.h"

#include <JuceHeader.h>

template <typename SampleType>
class AudioBufferQueue
{
public:
    static constexpr size_t order = 9;
    static constexpr size_t bufferSize = 1U << order;
    static constexpr size_t numBuffers = 5;
    
    void push(const SampleType* dataToPush, size_t numSamples)
    {

        jassert(numSamples <= bufferSize);

        int start1, size1, start2, size2;

        abstractFifo.prepareToWrite(1, start1, size1, start2, size2);

        jassert(size1 <= 1);
        jassert(size2 == 0);

        if (size1 > 0) {
            juce::FloatVectorOperations::copy(buffers[(size_t)start1].data(), dataToPush, (int)juce::jmin(bufferSize, numSamples));
        }

        abstractFifo.finishedWrite(size1);
    }

    void pop(SampleType* outputBuffer)
    {
        int start1, size1, start2, size2;

        abstractFifo.prepareToRead(1, start1, size1, start2, size2);

        jassert(size1 <= 1);
        jassert(size2 == 0);

        if (size1 > 0) {
            juce::FloatVectorOperations::copy(outputBuffer, buffers[(size_t)start1].data(), (int)bufferSize);
        }

        abstractFifo.finishedRead(size1);
    }

private:
    std::array <std::array<SampleType, bufferSize>, numBuffers> buffers;

    juce::AbstractFifo abstractFifo{ numBuffers };
};
