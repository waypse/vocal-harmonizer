#include "PluginEditor.h"

VocalHarmonizerEditor::VocalHarmonizerEditor (VocalHarmonizerProcessor& p)
    : AudioProcessorEditor (&p),
      outputGainAttachment (p.parameters, "outputGain", outputGainSlider)
{
    outputGainLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (outputGainSlider);
    addAndMakeVisible (outputGainLabel);
    setSize (420, 260);
}

void VocalHarmonizerEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff1e1f26));
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (22.0f, juce::Font::bold));
    g.drawText ("Vocal Harmonizer", getLocalBounds().removeFromTop (60), juce::Justification::centred);
}

void VocalHarmonizerEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    area.removeFromTop (50);
    auto knob = area.withSizeKeepingCentre (120, 150);
    outputGainLabel.setBounds (knob.removeFromTop (20));
    outputGainSlider.setBounds (knob);
}
