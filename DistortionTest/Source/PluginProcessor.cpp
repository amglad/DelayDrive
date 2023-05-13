/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionTestAudioProcessor::DistortionTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )//, state(*this, nullptr, "DriveDelayParams", createParameterLayout())
#endif
{
}

DistortionTestAudioProcessor::~DistortionTestAudioProcessor()
{
}

//juce::AudioProcessorValueTreeState::ParameterLayout DistortionTestAudioProcessor::createParameterLayout()
//{
//    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
//
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { "InputGain", 1}, // parameter ID
//                                                                  "Input Gain", // parameter name in automation lane
//                                                                  juce::NormalisableRange<float>(-12.f,12.f,0.1), // normalizable range
//                                                                  0.f) // default value
//                                                                  );
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { "OutputGain", 1}, // parameter ID
//                                                                  "Output Gain", // parameter name in automation lane
//                                                                  juce::NormalisableRange<float>(-12.f,12.f,0.1), // normalizable range
//                                                                  0.f) // default value
//                                                                  );
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { "Drive", 1}, // parameter ID
//                                                                  "Drive", // parameter name in automation lane
//                                                                  juce::NormalisableRange<float>(0.f,10.f,0.1), // normalizable range
//                                                                  3.f) // default value
//                                                                  );
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { "DelayTime", 1}, // parameter ID
//                                                                  "Delay Time", // parameter name in automation lane
//                                                                  juce::NormalisableRange<float>(30.f,500.f,1.0), // normalizable range
//                                                                  120.f) // default value
//                                                                  );
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { "Feedback", 1}, // parameter ID
//                                                                  "Feedback", // parameter name in automation lane
//                                                                  juce::NormalisableRange<float>(0.f,100.f,1.0), // normalizable range
//                                                                  30.f) // default value
//                                                                  );
//    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { "Mix", 1}, // parameter ID
//                                                                  "Mix", // parameter name in automation lane
//                                                                  juce::NormalisableRange<float>(0.f,100.f,1.0), // normalizable range
//                                                                  25.f) // default value
//                                                                  );
//
//    return { params.begin(), params.end() };
//}

//==============================================================================
const juce::String DistortionTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionTestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistortionTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionTestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistortionTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    distortion.prepareToPlay(sampleRate, samplesPerBlock);
}

void DistortionTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortionTestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    double inputGain_Lin = std::pow(10.0,inputGain_dB/20.0);
    distortion.setInputGain(inputGain_Lin);

    double outputGain_Lin = std::pow(10.0,outputGain_dB/20.0);
    distortion.setOutputGain(outputGain_Lin);

    float newDrive = drive;
    distortion.setDrive(newDrive);
    
    echo.setDelayMS(delay);
    echo.setFeedback(feedback);
    echo.setWet(wet);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples(); ++n)
        {
            float x = buffer.getWritePointer(channel) [n];
            x = distortion.processSample(x);
            float xDelayed = echo.processSample(x, channel);
            buffer.getWritePointer(channel) [n] = xDelayed;
        }
    }
}

//==============================================================================
bool DistortionTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistortionTestAudioProcessor::createEditor()
{
    return new DistortionTestAudioProcessorEditor (*this);
}

//==============================================================================
void DistortionTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    std::unique_ptr<juce::XmlElement> xml (new juce::XmlElement ("Params"));
    xml->setAttribute("Input Gain", (double) inputGain_dB);
    xml->setAttribute("Output Gain", (double) outputGain_dB);
    xml->setAttribute("Drive", (double) drive);
    xml->setAttribute("Delay Time", (double) delay);
    xml->setAttribute("Feeback", (double) feedback);
    xml->setAttribute("Mix", (double) wet);
    
//    auto currentState = state.copyState();
//    std::unique_ptr<juce::XmlElement> xml(currentState.createXml());
//    copyXmlToBinary(*xml, destData);
}

void DistortionTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName ("Params")) {
            inputGain_dB = xmlState->getDoubleAttribute ("Input Gain", 0.0);
            outputGain_dB = xmlState->getDoubleAttribute ("Output Gain", 0.0);
            drive = xmlState->getDoubleAttribute ("Drive", 3.0);
            delay = xmlState->getDoubleAttribute("Delay Time", 120.0);
            feedback = xmlState->getDoubleAttribute("Feedback", 30.0);
            wet = xmlState->getDoubleAttribute("Mix", 25.0);
        }
    
//    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
//    if (xml && xml->hasTagName(state.state.getType()))
//    {
//        state.replaceState(juce::ValueTree::fromXml(*xml));
//    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionTestAudioProcessor();
}
