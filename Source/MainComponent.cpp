#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 400);
    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50, 5000.0);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.addListener(this);
    
    addAndMakeVisible (frequencyLabel);
    frequencyLabel.setText ("Frequency", dontSendNotification);
    frequencyLabel.attachToComponent (&frequencySlider, true);
    
    addAndMakeVisible (durationSlider);
    durationSlider.setRange (1.0 / frequencySlider.getMaximum(),
                             1.0 / frequencySlider.getMinimum());
    durationSlider.setTextValueSuffix (" s");
    durationSlider.addListener (this);
    
    addAndMakeVisible (durationLabel);
    durationLabel.setText ("Duration", dontSendNotification);
    durationLabel.attachToComponent (&durationSlider, true);
    
    frequencySlider.setValue(500.0);
    AudioSourceChannelInfo buff;
    
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    const int sliderLeft = 120;
    frequencySlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    durationSlider.setBounds (sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
}

