#pragma once

#include "PluginProcessor.h"

class VocalHarmonizerEditor final : public juce::AudioProcessorEditor
{
public:
    explicit VocalHarmonizerEditor (VocalHarmonizerProcessor&);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider outputGainSlider { juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
    juce::Label outputGainLabel { {}, "Output" };
    juce::AudioProcessorValueTreeState::SliderAttachment outputGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocalHarmonizerEditor)
};
