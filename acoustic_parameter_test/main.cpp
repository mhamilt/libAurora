#include <iostream>
#include <string>
#include <assert.h>
#include <matts_audio.h>
#include <aurora.h>
#include <iomanip>

int main(int argc, const char * argv[]) {
    std::string filepath = "/Users/admin/Documents/GitHub/libAurora/tests/irs/1st-baptist-nashville/ir_mono.wav";
    
    double sampleRate = 48e3;
    int channels   = 2;
    double durSeconds = 3.0;
    uint32_t numFrames;
    auto ir = loadWav(numFrames, filepath);
//    writeToWav(ir, numFrames, "ir.wav");
    
    //------------------------------------------------------------------------
    // Acoustical Parameters
    
    Aurora::AcousticalParameters acParams{};
    
    auto& parameterTracks = acParams.Tracks();
    parameterTracks.emplace_back(Aurora::AcParametersAudioTrack(numFrames, sampleRate));
    auto& audioAnalysisTrack = parameterTracks.back();
    std::copy_n(ir, numFrames, audioAnalysisTrack.Samples());
    
    acParams.Init();
    
    // Then process parameterTracks
    acParams.CalculateAcousticParameters();
    const auto& result = acParams.Results(0);
    const auto& fcbs = result.Frequencies();
    result.Parameters();
    
//    for (const auto& paramater : result.Parameters())
//    {
//        for (const auto& fcb : fcbs)
//        {
//            std::cout << paramater << " (" << fcb << "): " << result.Get(paramater, fcb).value <<'\n';
//        }
//    }
    
    // Header
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(12) << "";
    for (const auto& fcb : fcbs)
    {
        std::cout << std::setw(10) << fcb;
    }
    std::cout << '\n';
    
    // Rows
    for (const auto& parameter : result.Parameters())
    {
        std::cout << std::setw(12) << parameter;

        for (const auto& fcb : fcbs)
        {
            std::cout << std::setw(10)
                      << result.Get(parameter, fcb).value;
        }

        std::cout << '\n';
    }
    
    return 0;
}
