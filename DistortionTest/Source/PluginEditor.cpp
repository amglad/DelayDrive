/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionTestAudioProcessorEditor::DistortionTestAudioProcessorEditor (DistortionTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
//    tree.addListener(this);
//    addMouseListener(this, false);
//    setInterceptsMouseClicks(true, false);
//
//    tree = audioProcessor.state.state;
//    valueTreeRedirected(audioProcessor.state.state);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (520, 360);
    
    
    // input gain knob
    inputGainKnob.addListener(this);
    inputGainKnob.setRange(-12.0,12.0,0.1);
    inputGainKnob.setValue(0.0);
    inputGainKnob.setTextValueSuffix(" dB");
    inputGainKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    inputGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    inputGainKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::ivory.darker(0.4));
    inputGainKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white);
    inputGainKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orangered.brighter(0.1));
    inputGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::ivory.darker(0.3));
    inputGainKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(inputGainKnob);

    inputGainLabel.setText("Input Gain", juce::dontSendNotification);
    inputGainLabel.setColour(juce::Label::textColourId, juce::Colours::ivory.darker(0.4));
    inputGainLabel.attachToComponent(&inputGainKnob, false);
    inputGainLabel.setFont(juce::Font(18.0));
    inputGainLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(inputGainLabel);
    
    // drive knob
    driveKnob.addListener(this);
    driveKnob.setRange(1.0,10.0,0.1);
    driveKnob.setValue(3.0);
    driveKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    driveKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::ivory.darker(0.4));
    driveKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white);
    driveKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orangered.brighter(0.1));
    driveKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::ivory.darker(0.3));
    driveKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(driveKnob);
    
    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.setColour(juce::Label::textColourId, juce::Colours::ivory.darker(0.4));
    driveLabel.attachToComponent(&driveKnob, false);
    driveLabel.setFont(juce::Font(18.0));
    driveLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(driveLabel);
    
    // output gain knob
    outputGainKnob.addListener(this);
    outputGainKnob.setRange(-12.0,12.0,0.1);
    outputGainKnob.setValue(0.0);
    outputGainKnob.setTextValueSuffix(" dB");
    outputGainKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    outputGainKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::ivory.darker(0.4));
    outputGainKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white);
    outputGainKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orangered.brighter(0.1));
    outputGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::ivory.darker(0.3));
    outputGainKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(outputGainKnob);
    
    outputGainLabel.setText("Output Gain", juce::dontSendNotification);
    outputGainLabel.setColour(juce::Label::textColourId, juce::Colours::ivory.darker(0.4));
    outputGainLabel.attachToComponent(&outputGainKnob, false);
    outputGainLabel.setFont(juce::Font(18.0));
    outputGainLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(outputGainLabel);
    
    
    
    // delay knob
    delayKnob.addListener(this);
    delayKnob.setRange(30.0,500.0,1.0);
    delayKnob.setValue(120.0);
    delayKnob.setTextValueSuffix(" ms");
    delayKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    delayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    delayKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::ivory.darker(0.4));
    delayKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white);
    delayKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cornflowerblue.darker(0.2));
    delayKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::ivory.darker(0.3));
    delayKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(delayKnob);
    
    delayLabel.setText("Delay Time", juce::dontSendNotification);
    delayLabel.setColour(juce::Label::textColourId, juce::Colours::ivory.darker(0.4));
    delayLabel.attachToComponent(&delayKnob, false);
    delayLabel.setFont(juce::Font(18.0));
    delayLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(delayLabel);
    
    // feedback knob
    feedbackKnob.addListener(this);
    feedbackKnob.setRange(0.0,100.0,1.0);
    feedbackKnob.setValue(30.0);
    feedbackKnob.setTextValueSuffix(" %");
    feedbackKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    feedbackKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    feedbackKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::ivory.darker(0.4));
    feedbackKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white);
    feedbackKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cornflowerblue.darker(0.2));
    feedbackKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::ivory.darker(0.3));
    feedbackKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(feedbackKnob);
    
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::ivory.darker(0.4));
    feedbackLabel.attachToComponent(&feedbackKnob, false);
    feedbackLabel.setFont(juce::Font(18.0));
    feedbackLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(feedbackLabel);
    
    // mix knob
    mixKnob.addListener(this);
    mixKnob.setRange(0.0,100.0,1.0);
    mixKnob.setValue(25.0);
    mixKnob.setTextValueSuffix(" %");
    mixKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    mixKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::ivory.darker(0.4));
    mixKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::white);
    mixKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cornflowerblue.darker(0.2));
    mixKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::ivory.darker(0.3));
    mixKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(mixKnob);
    
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setColour(juce::Label::textColourId, juce::Colours::ivory.darker(0.4));
    mixLabel.attachToComponent(&mixKnob, false);
    mixLabel.setFont(juce::Font(18.0));
    mixLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(mixLabel);
    
    // plugin title
    title.setText("delay // drive", juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    title.setBounds(135,10,250,50);
    title.setFont(juce::Font("Arial Black", 27.0, juce::Font::bold));
    title.setColour(juce::Label::ColourIds::textColourId, juce::Colours::ivory.darker(0.4));
    addAndMakeVisible(title);
    
    
//    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "InputGain", inputGainKnob));
//    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "OutputGain", outputGainKnob));
//    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "Drive", driveKnob));
//    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "DelayTime", delayKnob));
//    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "Feedback", feedbackKnob));
//    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "Mix", mixKnob));
    
}

DistortionTestAudioProcessorEditor::~DistortionTestAudioProcessorEditor()
{
}

//==============================================================================
void DistortionTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);
    
    juce::Image delayImage = juce::ImageCache::getFromMemory(BinaryData::delay_png, BinaryData::delay_pngSize);
    delayImage.rescaled(30,30, juce::Graphics::highResamplingQuality);
    g.setColour(juce::Colours::cornflowerblue.darker(0.2));
    int delayWidth = delayImage.getWidth();
    int delayHeight = delayImage.getHeight();
    g.drawImage (delayImage, 155, 75, 90, 90, 0, 0, delayWidth, delayHeight, true);
    
    juce::Image driveImage = juce::ImageCache::getFromMemory(BinaryData::drive_png, BinaryData::drive_pngSize);
    driveImage.rescaled(80, 80, juce::Graphics::highResamplingQuality);
    g.setColour(juce::Colours::orangered.brighter(0.1));
    int driveWidth = driveImage.getWidth();
    int driveHeight = driveImage.getHeight();
    g.drawImage (driveImage, 275, 75, 90, 90, 0, 0, driveWidth, driveHeight, true);

}

void DistortionTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int w = 120; int h = 120;
    
    delayKnob.setBounds(20, 220, w, h);
    feedbackKnob.setBounds(140,220,w,h);
    mixKnob.setBounds(20,60,w,h);
    
    inputGainKnob.setBounds(380,60,w,h);
    driveKnob.setBounds(260,220,w,h);
    outputGainKnob.setBounds(380,220,w,h);

}

void DistortionTestAudioProcessorEditor::sliderValueChanged(juce::Slider * slider)
{
    // check which slider was moved and get its value
    if (slider == &inputGainKnob)
    {
        audioProcessor.inputGain_dB = slider->getValue();
    }

    if (slider == &driveKnob)
    {
        audioProcessor.drive = slider->getValue();
    }

    if (slider == &outputGainKnob)
    {
        audioProcessor.outputGain_dB = slider->getValue();
    }

    if (slider == &delayKnob)
    {
        audioProcessor.delay = slider->getValue();
    }

    if (slider == &feedbackKnob)
    {
        audioProcessor.feedback = slider->getValue();
    }

    if (slider == &mixKnob)
    {
        audioProcessor.wet = slider->getValue();
    }
}

//void DistortionTestAudioProcessorEditor::valueTreePropertyChanged (juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
//{
//
//}
//
//
//void DistortionTestAudioProcessorEditor::valueTreeRedirected (juce::ValueTree &)
//{
//
//}

