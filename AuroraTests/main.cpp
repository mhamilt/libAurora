#include <iostream>
#include <memory>
#include <aurora.h>
#include <kiss_fft.h>
#include "audio.h"

int main()
{
    Aurora::SineSweepGenerator ssweep{};
    
    const size_t blockSize = 1024;
    size_t numSamples = ssweep.GetSamplerate() * 10;
    auto filter  = std::make_unique<float[]> (numSamples);
    auto audio   = std::make_unique<float[]>(numSamples);
    size_t i = 0;
    ssweep.Generate();
    
    ssweep.FillBlock(audio.get()  + i,   numSamples, 0, 0);
    ssweep.FillBlock(filter.get() + i,  numSamples, 0, 1);
    
    writeToWav(audio.get(),  (uint32_t)numSamples, "sweep-audio.wav");
    writeToWav(filter.get(), (uint32_t)numSamples, "sweep-inver.wav");
    
    Aurora::ConvolverController convolver{};
    // Init()
    //    convolver.Reset();
    //    convolver.SetSamplerate(ssweep.GetSamplerate()); // ???
    //    convolver.CheckSamplerate(ssweep.GetSamplerate());
    //    convolver.ResizeFilterTrack(0,numSamples);
    //    convolver.ResizeInputTrack(0, numSamples);
    
    //    auto& filters = convolver.GetFilters();
    
    // put data in filters
    //    filters[0].Samples();
    
    // put data in input
    //    auto& input = convolver.GetInputTrack(0);
    
    std::cout << "convolver.GetGain():" << convolver.GetGain() << '\n';
    
    return 0;
}
