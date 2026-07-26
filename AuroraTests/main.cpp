#include <iostream>
#include <memory>
#include <aurora.h>
#include <kiss_fft.h>
#include "audio.h"

int main()
{
    //------------------------------------------------------------------------
    // SineSweep Generator
    Aurora::SineSweepGenerator ssweep{};
    ssweep.SetSweepDuration(1.0);
    ssweep.Generate();
    
    size_t numSamples  = ssweep.GetBuffersLength();
    auto filter  = std::make_unique<float[]>(numSamples);
    auto audio   = std::make_unique<float[]>(numSamples);
    
    
    ssweep.FillBlock(audio.get() ,  numSamples, 0, 0); // Sweep  == Channel_1
    ssweep.FillBlock(filter.get(),  numSamples, 0, 1); // Filter == Channel_2
    
    //------------------------------------------------------------------------
    // Convolution
    
    Aurora::ConvolverController convolver{};
    convolver.Reset();
    convolver.SetSamplerate(ssweep.GetSamplerate()); // ???
    convolver.CheckSamplerate(ssweep.GetSamplerate());
    convolver.SetFilterMatrixDimensions(1,1);
    convolver.ResizeFilterTrack(0,numSamples);
    convolver.ResizeInputTrack(0, numSamples);
    
    auto& convolutionFilters = convolver.GetFilters();
    auto& input = convolver.GetInputTrack(0);
    
    std::copy_n(filter.get(), numSamples, convolutionFilters[0].Samples());
    std::copy_n(audio.get(),  numSamples, input.Samples());
    
    convolver.DoConvolution();
    
    auto& conv = convolver.GetOutputTrack(0);
    
    for (auto i = conv.Length()-10; i < conv.Length(); i++) {
        std::cout << conv.Samples()[i] << '\n';
    }
        
//  conv.Reverse();
    
    for (auto i = 0; i < 10; i++) {
        std::cout << conv.Samples()[i] << '\n';
    }
    
//        writeToWav(audio.get(),  (uint32_t)numSamples, "sweep-audio.wav");
//        writeToWav(filter.get(), (uint32_t)numSamples, "sweep-inver.wav");
//        writeToWav(conv.Samples(),  (uint32_t)numSamples, "sweep-convo.wav");
    
    //------------------------------------------------------------------------
    // Acoustical Parameters
    
    Aurora::AcousticalParameters acParams{};
    
    auto& parameterTracks = acParams.Tracks();
    parameterTracks.emplace_back(Aurora::AcParametersAudioTrack(numSamples, ssweep.GetSamplerate()));
    auto& audioAnalysisTrack = parameterTracks.back();
    std::copy_n(conv.Samples(), numSamples, audioAnalysisTrack.Samples());
    
    acParams.Init();
    
    // Then process parameterTracks
    acParams.CalculateAcousticParameters();
    const auto& result = acParams.Results(0);
    const auto& fcbs = result.Frequencies();
    result.Parameters();
    
    for (const auto& paramater : result.Parameters())
    {
        for (const auto& fcb : fcbs)
        {
            std::cout << paramater << " (" << fcb << "): " << result.Get(paramater, fcb).value <<'\n';
        }
    }
    
    return 0;
}
