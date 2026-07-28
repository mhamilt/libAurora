#include <iostream>
#include <string>
#include <assert.h>
#include <matts_audio.h>
#include <aurora.h>
#include <iomanip>

int main(int argc, const char * argv[]) {
    std::string filepath = "/Users/admin/Documents/GitHub/libAurora/tests/irs/1st-baptist-nashville/1st_baptist_nashville_balcony_24_96.wav";
    
    double sampleRate = 96e3;
    uint32_t numFrames, numChannels;
    auto ir = loadWavMultichannel(numFrames, numChannels, filepath);
//    writeToWav(ir, numFrames, "ir.wav");
    
    //------------------------------------------------------------------------
    // Acoustical Parameters
    
    Aurora::AcousticalParameters acParams{};
    
    auto& parameterTracks = acParams.Tracks();
    parameterTracks.emplace_back(Aurora::AcParametersAudioTrack(numFrames, sampleRate));
    auto& audioAnalysisTrackL = parameterTracks.back();
    std::copy_n(ir[0], numFrames, audioAnalysisTrackL.Samples());
//    auto& audioAnalysisTrackR = parameterTracks.back();
//    std::copy_n(ir[1], numFrames, audioAnalysisTrackR.Samples());
    
    acParams.Init();
    
    // Then process parameterTracks
    acParams.CalculateAcousticParameters();
    const auto& result = acParams.Results(0);
    const auto& fcbs = result.Frequencies();
    result.Parameters();
    
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
