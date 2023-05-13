/*
  ==============================================================================

    DistortionEffect.h
    Created: 21 Feb 2023 3:24:22pm
    Author:  Mitch Glad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DistortionEffect
{
    
public:
    
    float processSample(float x);
    
    void processBlock(juce::AudioBuffer<float> &buffer);
    
    void processInPlace(float *buffer, const int numSamples, const int channel);
    
    void prepareToPlay(float sampleRate, float samplesPerBlock);
    
    void setDrive(float newDrive);
    
    void setInputGain(float inputGain_Lin) {inputGain = inputGain_Lin;}
    
    void setOutputGain(float outputGain_Lin) {outputGain = outputGain_Lin;}
    
    
private:
    
    float Fs;
    int bufferSize;
    
    float inputGain;
    float outputGain;
    
    float drive;
};
