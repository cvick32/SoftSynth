#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainContentComponent   : public Component,
                               public Slider::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    
    ~MainContentComponent();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &frequencySlider) {
            if (currentSampleRate > 0.0)
                updateAngleDelta();
            durationSlider.setValue (1.0 / frequencySlider.getValue(), dontSendNotification);
        }
        else if (slider == &durationSlider)
            frequencySlider.setValue (1.0 / durationSlider.getValue(), dontSendNotification);
    }
    
    void updateAngleDelta()
    {
        const double cyclesPerSample = frequencySlider.getValue() / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
    }
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) 
    {
        currentSampleRate = sampleRate;
        updateAngleDelta();
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
    {
        const float level = 0.125f;
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            const float currentSample = (float) std::sin (currentAngle);
            currentAngle += angleDelta;
            buffer[sample] = currentSample * level;
        }
    }

    
private:
    
    Slider frequencySlider;
    Label frequencyLabel;
    Slider durationSlider;
    Label durationLabel;
    
    double currentSampleRate, currentAngle, angleDelta;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

