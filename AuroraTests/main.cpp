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
    auto data = std::make_unique<float[]>(blockSize);
    size_t i = 0;
    
    ssweep.Generate();
    
    while (i < numSamples)
    {
        const size_t currentBlock = std::min(blockSize, numSamples - i);

        ssweep.FillBlock(data.get() + i, currentBlock, i, 0);

        i += currentBlock;
    }
    
    writeToWav(data.get(), numSamples, "test.wav");
    
    Aurora::ConvolverController convolver{};
    
    std::cout << "convolver.GetGain():" << convolver.GetGain() << '\n';
    
    return 0;
}
