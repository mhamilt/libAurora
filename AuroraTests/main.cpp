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
    size_t numSamples = ssweep.GetSamplerate() * 10;
    auto filter  = std::make_unique<float[]>(numSamples);
    auto audio   = std::make_unique<float[]>(numSamples);
    
    ssweep.Generate();
    
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
    
    //    writeToWav(audio.get(),  (uint32_t)numSamples, "sweep-audio.wav");
    //    writeToWav(filter.get(), (uint32_t)numSamples, "sweep-inver.wav");
    //    writeToWav(conv.Samples(),  (uint32_t)numSamples, "sweep-convo.wav");
    
    for (auto i = numSamples-10; i < numSamples; i++) {
        std::cout << conv.Samples()[i] << '\n';
    }
    
    //------------------------------------------------------------------------
    // Acoustical Parameters
    
    Aurora::AcousticalParameters acParams{};
    acParams.Init();
    
    // Fill parameterTracks
    auto& parameterTracks = acParams.Tracks();
    
    // Config
    //    acParams.SetUserMinLevel(0.0);
    //    acParams.SetUserMaxLevel(0.0);
    //    acParams.SetDirectSoundTrigValue(0.0);
    //    acParams.SetFullScale(0.0);
    //    acParams.SetProbeMicsDistance(0.0);
    //    acParams.SetSoundSpeedValue(0.0);
    //    acParams.SetSource(Aurora::AcParametersEffect::Source::TwoOmniMics); // Default stereo choice.
    
    // Then process parameterTracks
    acParams.CalculateAcousticParameters();
    const auto& results = acParams.Results(0);
    
    return 0;
}
