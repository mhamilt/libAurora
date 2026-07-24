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
    auto filter = std::make_unique<float[]>(blockSize);
    auto data   = std::make_unique<float[]>(blockSize);
    size_t i = 0;
    
    ssweep.Generate();
    
//    while (i < numSamples)
//    {
//        const size_t currentBlock = std::min(blockSize, numSamples - i);
//        
//        ssweep.FillBlock(data.get() + i,   currentBlock, i,   0);
//        
//        i += currentBlock;
//    }
//    i=0;
//    while (i < numSamples)
//    {
//        const size_t currentBlock = std::min(blockSize, numSamples - i);
//        
//        ssweep.FillBlock(filter.get() + i, currentBlock, i, 1);
//        
//        i += currentBlock;
//    }
    //    memcpy(data.get(), ssweep.GetBuffer(0).CSamples(), numSamples);
    //    memcpy(filter.get(), ssweep.GetBuffer(1).CSamples(), numSamples);
    
    i=0;
    ssweep.FillBlock(data.get() + i,   numSamples, 0, 0);
    ssweep.FillBlock(filter.get() + i, numSamples, 0, 1);
    writeToWav(data.get(),   numSamples, "sweep-audio.wav");
    writeToWav(filter.get(), numSamples, "sweep-inver.wav");
    
    writeToWav(const_cast<float*>(ssweep.GetBuffer(0).CSamples()), numSamples, "sweep-normal.wav");
    writeToWav(const_cast<float*>(ssweep.GetBuffer(1).CSamples()), numSamples, "sweep-invers.wav");
    
    Aurora::ConvolverController convolver{};
    // Init()
    convolver.Reset();
    convolver.SetSamplerate(ssweep.GetSamplerate()); // ???
    convolver.CheckSamplerate(ssweep.GetSamplerate());
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
