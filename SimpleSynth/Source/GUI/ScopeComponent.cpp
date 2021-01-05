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


template<typename SampleType>
class ScopeDataCollector
{
public:
    ScopeDataCollector(AudioBufferQueue<SampleType>& queueToUse)
        : audioBufferQueue(queueToUse)
    {}

    void process(const SampleType* data, size_t numSamples)
    {
        size_t index = 0;

        if (currentState == State::WaitingForTrigger)
        {
            while (index++ < numSamples)
            {
                auto currentSample = *data++;
                if (currentSample >= triggerLevel && prevSample < triggerLevel)
                {
                    numCollected = 0;
                    currentState = State::Collecting;
                    break;
                }
                prevSample = currentSample;

            }
        }

        if (currentState == State::Collecting)
        {
            while (index++ < numSamples)
            {
                buffer[numCollected++] = *data++;

                if (numCollected == buffer.size())
                {
                    audioBufferQueue.push(buffer.data(), buffer.size());
                    currentState = State::WaitingForTrigger;
                    prevSample = SampleType(100);
                    break;
                }
            }
        }

    }

private:
    enum class State
    {
        WaitingForTrigger,
        Collecting
    };

    static constexpr auto triggerLevel = SampleType(0.001);

    std::array<SampleType, AudioBufferQueue<SampleType>::bufferSize> buffer;
    State currentState{ State::WaitingForTrigger };
    AudioBufferQueue<SampleType>& audioBufferQueue;
    size_t numCollected;
    SampleType prevSample = SampleType(100);
};



template<typename SampleType>
class ScopeComponent : public juce::Component, private juce::Timer
{
public:

    using Queue = AudioBufferQueue<SampleType>;

    ScopeComponent(Queue& queueuToUse)
        : audioBufferQueue(queueuToUse)
    {
        sampleData.fill(SampleType(0));
        setFramePerSecond(30);
    }
    
    void setFramePerSecond(int framePerSecond)
    {
        jassert(framePerSecond > 0 && framePerSecond < 1000);
        startTimerHz(framePerSecond);
    }
    
    // ④SCOPEパネルの状態を描画する関数。パネルの領域を塗りつぶす処理と波形をプロットする処理を実行する。
    void paint(Graphics& g) override
    {
        // ④-A. パネルの名前表示に使用する文字のフォント設定を生成する。
        int panelNameHeight = 42;
        int localMargin = 2;
        Font panelNameFont = Font(24.0f, Font::plain).withTypefaceStyle("Italic");

        // ④-A. パネルの背景を描画する処理。当コンポーネントの領域を角丸の四角形で塗りつぶす描画命令を実行する。
        {
            float x = 0.0f, y = 0.0f, width = (float)getWidth(), height = (float)getHeight();
            Colour panelColour = juce::Colour(36, 36, 36);
            g.setColour(panelColour);
            g.fillRoundedRectangle(x, y, width, height, 10.0f);
        }

        // ④-A. パネル上部にパネルの名前を表示する。文字列を表示する領域を決定した後、コンテキストに描画命令を実行する。
        {
            Rectangle<int> bounds = getLocalBounds();
            String text("SCOPE");
            Colour fillColour = Colours::white;
            g.setColour(fillColour);
            g.setFont(panelNameFont);
            g.drawText(text, bounds.removeFromTop(panelNameHeight).reduced(localMargin), Justification::centred, true);
        }
};
