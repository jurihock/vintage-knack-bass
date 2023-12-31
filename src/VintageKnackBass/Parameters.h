#pragma once

#include <JuceHeader.h>

#include <VintageKnackBass/Parameters/GenericParameterContainer.h>

#include <bit>

class Parameters final : public GenericParameterContainer
{

public:

  Parameters(juce::AudioProcessor& process);
  ~Parameters();

  void onbypass(std::function<void()> callback);

  bool bypass() const;

  void load(const void* data, const int size);
  void save(juce::MemoryBlock& data);

private:

  const int schema = 1;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)

};
