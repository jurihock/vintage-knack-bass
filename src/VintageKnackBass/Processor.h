#pragma once

#include <JuceHeader.h>

#include <VintageKnackBass/Editor.h>
#include <VintageKnackBass/Effect.h>
#include <VintageKnackBass/Parameters.h>

class Processor final : public juce::AudioProcessor
{

public:

  Processor();
  ~Processor();

  const juce::String getName() const override;

  bool hasEditor() const override;
  juce::AudioProcessorEditor* createEditor() override;

  bool isMidiEffect() const override;
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  int  getNumPrograms() override;
  int  getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  void changeProgramName(int index, const juce::String& name) override;
  const juce::String getProgramName (int index) override;

  double getTailLengthSeconds() const override;
  juce::AudioProcessorParameter* getBypassParameter() const override;
  bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

  void getStateInformation(juce::MemoryBlock& data) override;
  void setStateInformation(const void* data, int size) override;

  void prepareToPlay(double samplerate, int blocksize) override;
  void releaseResources() override;

  void processBlock(juce::AudioBuffer<float>& audio, juce::MidiBuffer& midi) override;

private:

  struct State
  {
    double samplerate {};
    int blocksize {};
  };

  const State nostate;

  std::mutex mutex;
  std::optional<State> state;
  std::unique_ptr<Effect> effect;
  std::unique_ptr<Parameters> parameters;

  void resetEffect(const State& state);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Processor)

};
