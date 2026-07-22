#include <iostream>
#include <memory>
#include <aurora.h>
#include "audio.h"

int main()
{
    Aurora::SineSweepGenerator ssweep{};
    
    const size_t blockSize = 1024;
    size_t numSamples = ssweep.GetSamplerate() * 10;
    auto data = std::make_unique<float[]>(blockSize);
    decltype(numSamples) i = 0;
    
    ssweep.Generate();
    
    while ((i < numSamples))
    {
        ssweep.FillBlock(data.get() + i, blockSize, i, 0);
        i += (i+blockSize < numSamples) ? blockSize : numSamples - i;
    }
    
    writeToWav(data.get(), numSamples, "test.wav");
    
    return 0;
}
