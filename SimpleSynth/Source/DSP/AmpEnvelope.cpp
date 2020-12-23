/*
  ==============================================================================

    AmpEnvelope.cpp
    Created: 21 Dec 2020 4:02:55pm
    Author:  宮田亮

  ==============================================================================
*/

#include "AmpEnvelope.h"

namespace
{
    const float AMP_MAX = 1.0f;
    const float AMP_MIN = 0.0f;
    const float ATTACK_MIN = 0.01f;
    const float DECAY_MIN = 0.01f;
    const float RELEASE_MIN = 0.01f;
}

AmpEnvelope::AmpEnvelope(float attackTime, float decayTime, float sustain, float releaseTime)
    : _attackTime(attackTime), _decayTime(decayTime), _sustainValue(sustain), _releaseTime(releaseTime)
    , _sampleRate(0.0f), _value(0.0f), _valueOnReleaseStart(0.0f), _ampState(AMPENV_STATE::WAIT)
{
    // 各パラメータの値を定数で記述した最大値・最小値の範囲に収める。
    if (_attackTime <= ATTACK_MIN) {
        _attackTime = ATTACK_MIN;
    }

    if (_decayTime <= DECAY_MIN) {
        _decayTime = DECAY_MIN;
    }

    if (_releaseTime <= RELEASE_MIN) {
        _releaseTime = RELEASE_MIN;
    }

    if (_sustainValue > AMP_MAX) {
        _sustainValue = AMP_MAX;
    }

    if (_sustainValue < AMP_MIN) {
        _sustainValue = AMP_MIN;
    }
}
