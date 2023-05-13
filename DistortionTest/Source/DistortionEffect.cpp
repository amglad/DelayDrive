/*
  ==============================================================================

    DistortionEffect.cpp
    Created: 21 Feb 2023 3:24:22pm
    Author:  Mitch Glad

  ==============================================================================
*/

#include "DistortionEffect.h"


float DistortionEffect::processSample(float x)
{
    float y = x * inputGain;
    y = (2.f/M_PI) * atan(y * drive);
    y = y * outputGain;
    return y;
}

void DistortionEffect::processBlock(juce::AudioBuffer<float> &buffer)
{
    const int numChannels = buffer.getNumChannels();    // amount of channels in buffer
    const int numSamples = buffer.getNumSamples();      // amount of samples in buffer
    
    for (int c = 0; c < numChannels; ++c) {             // iterate through our two channels
        
        for (int n = 0; n < numSamples; ++n) {          // iterate through the number of samples
            
            float x = buffer.getWritePointer(c) [n];    // grab the value of our signal
           
            x = processSample(x);                       // process sample
            
            buffer.getWritePointer(c) [n] = x;          // write our output to the buffer
        }
    }
}


void DistortionEffect::processInPlace(float *buffer, const int numSamples, const int channel)
{
    for (int n = 0; n < numSamples; ++n)
    {
        float x = *buffer;                      // de-reference current value
        x = processSample(x);                   // same thing, just calls the function above
        *buffer = x;                            // re-reference the same spot, distorted
        ++buffer;                               // incremement the buffer location
    }
}


void DistortionEffect::prepareToPlay(float sampleRate, float samplesPerBlock)
{
    Fs = sampleRate;
    bufferSize = samplesPerBlock;
}


void DistortionEffect::setDrive(float newDrive)
{
    drive = juce::jlimit(1.f,10.f, newDrive);
}
