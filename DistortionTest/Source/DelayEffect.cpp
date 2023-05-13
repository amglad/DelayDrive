/*
  ==============================================================================

    DelayEffect.cpp
    Created: 29 Mar 2023 12:07:22pm
    Author:  Mitch Glad

  ==============================================================================
*/

#include "DelayEffect.h"

//float RevDelayEffect::processSample(float x, const int c){
//
//    // one sample of delay
//    int currentIndex = i[c];
//    float y = delayBuffer[currentIndex][c];
//
//    delayBuffer[currentIndex][c] = x;
//
//    // Increment Index
//    i[c] += increment;
//    if (i[c] >= delaySamples){
//        increment = -1;
//        i[c] += increment; // circular indexing
//    }
//    if (i[c] <= 0){
//        increment = 1;
//        i[c] += increment;
//    }
//
//    return y;
//
//}


//void RevDelayEffect::setDelayMS(float delayMS){
//
//    float delaySec = delayMS / 1000.f;
//    delaySamples = delaySec * Fs;
//    delaySamples = juce::jmin(delaySamples,23999);
//}




float EchoEffect::processSample(float x, const int c){
    
    //int currentIndex = i[c];
    float v = delayBuffer[r[c]][c];
    
    delayBuffer[w[c]][c] = .707 * x + (v * feedback);
    // DBG(feedback);
    // delayBuffer[w[c]][c];
    
    // Increment Index
    w[c]++;
    if (w[c] >= SIZE){
        w[c] = 0; // circular indexing
    }
    
    // Increment Index
    r[c]++;
    if (r[c] >= SIZE){
        r[c] = 0; // circular indexing
    }
    float y = (1.f - wet) * x + wet * v;
    return y;
    
}

void EchoEffect::setDelayMS(float delayMS){
    
    float delaySec = delayMS / 1000.f;
    delaySamples = delaySec * Fs;
    delaySamples = juce::jmin(delaySamples,23999);
    r[0] = w[0] - delaySamples;
    if (r[0] < 0){
        r[0] += SIZE;
    }
    r[1] = w[1] - delaySamples;
    if (r[1] < 0){
        r[1] += SIZE;
    }
}


//float EchoEffect::processSample(float x, const int c){
//
//    float v = delay.processSample(x, c);
//
//    float y = (1.f - wet) * x + wet * v;
//
//    return y;
//
//}


void EchoEffect::processBlock(juce::AudioBuffer<float> &buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    
    for (int c = 0; c < numChannels ; ++c){
        
        for (int n = 0; n < numSamples ; ++n){
            
            float x = buffer.getWritePointer(c) [n];
            
            x = processSample(x,c);
            
            buffer.getWritePointer(c) [n] = x;
        }
        
    }
}

void EchoEffect::processInPlace(float * buffer, const int numSamples, const int c){
    
    for (int n = 0 ; n < numSamples; ++n){
        float x = (*buffer); // de-reference current value
        
        x = processSample(x,c);
        
        *buffer = x; // over-write current value
        
        ++buffer; // move pointer to the next sample
    }
    
}
