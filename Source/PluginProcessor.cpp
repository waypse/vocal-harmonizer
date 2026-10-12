#include "PluginProcessor.h"
#include "PluginEditor.h"

VocalHarmonizerProcessor::VocalHarmonizerProcessor()
    : AudioProcessor (BusesProperties()
                          .withInput ("Input", juce::AudioChannelSet::stereo(), true)
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      parameters (*this, nullptr, "PARAMETERS", createParameterLayout())
{
    outputGainDb = parameters.getRawParameterValue ("outputGain");
}

juce::AudioProcessorValueTreeState::ParameterLayout VocalHarmonizerProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { "outputGain", 1 },
        "Output Gain",
        juce::NormalisableRange<float> (-24.0f, 12.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel ("dB")));
    return layout;
}

void VocalHarmonizerProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec { sampleRate,
                                  static_cast<juce::uint32> (samplesPerBlock),
                                  static_cast<juce::uint32> (getTotalNumOutputChannels()) };
    outputGain.prepare (spec);
    outputGain.setRampDurationSeconds (0.05);
}

bool VocalHarmonizerProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& out = layouts.getMainOutputChannelSet();
    if (out != juce::AudioChannelSet::mono() && out != juce::AudioChannelSet::stereo())
        return false;

    // A mono vocal can come in while the harmonies go out in stereo.
    const auto& in = layouts.getMainInputChannelSet();
    return in == juce::AudioChannelSet::mono() || in == out;
}

void VocalHarmonizerProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const auto numIn = getTotalNumInputChannels();
    const auto numOut = getTotalNumOutputChannels();

    // Mono in, stereo out: copy the vocal to both sides.
    if (numIn == 1)
        for (int ch = 1; ch < numOut; ++ch)
            buffer.copyFrom (ch, 0, buffer, 0, 0, buffer.getNumSamples());

    // Starter version: pass the lead vocal through. Harmony voices come next.
    outputGain.setGainDecibels (outputGainDb->load());
    juce::dsp::AudioBlock<float> block (buffer);
    outputGain.process (juce::dsp::ProcessContextReplacing<float> (block));
}

juce::AudioProcessorEditor* VocalHarmonizerProcessor::createEditor()
{
    return new VocalHarmonizerEditor (*this);
}

void VocalHarmonizerProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = parameters.copyState().createXml())
        copyXmlToBinary (*xml, destData);
}

void VocalHarmonizerProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VocalHarmonizerProcessor();
}
