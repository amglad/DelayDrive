/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistortionTestAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            //public juce::ValueTree::Listener
                                            public juce::Slider::Listener
{
public:
    DistortionTestAudioProcessorEditor (DistortionTestAudioProcessor&);
    ~DistortionTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider * slider) override;
    // void valueTreePropertyChanged (juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
    // void valueTreeRedirected (juce::ValueTree &treeWhichHasBeenChanged) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionTestAudioProcessor& audioProcessor;
    
    // drive portion
    juce::Slider inputGainKnob;
    juce::Slider outputGainKnob;
    juce::Slider driveKnob;
    
    juce::Label inputGainLabel;
    juce::Label outputGainLabel;
    juce::Label driveLabel;
    
    // delay portion
    juce::Slider delayKnob;
    juce::Slider feedbackKnob;
    juce::Slider mixKnob;
    
    juce::Label delayLabel;
    juce::Label feedbackLabel;
    juce::Label mixLabel;
    
    juce::Image delayImage;
    juce::Image driveImage;
    juce::Label title;
    
    // juce::ValueTree tree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionTestAudioProcessorEditor)
    
public:
    
    // std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachment;
};
