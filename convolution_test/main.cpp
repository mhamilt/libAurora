//#define MINIAUDIO_IMPLEMENTATION

#include <iostream>
#include <miniaudio.h>
#include <algorithm>
#include <cstring>
#include <thread>
#include <chrono>
#include <aurora.h>
#include <matts_audio.h>

struct AudioData
{
    const float* playback;
    size_t playbackFrames;
    size_t playbackPos = 0;

    float* recording;
    size_t recordingFrames;
    size_t recordingPos = 0;
};

struct SweepAudioState
{
    const float* playbackBuffer;
    float* recordBuffer;

    size_t numSamples;
    size_t playbackPos = 0;
    size_t recordPos = 0;
};

void data_callback(
    ma_device* device,
    void* output,
    const void* input,
    ma_uint32 frameCount)
{
    auto* state = static_cast<SweepAudioState*>(device->pUserData);

    float* out = static_cast<float*>(output);
    const float* in = static_cast<const float*>(input);

    size_t remaining =
        state->numSamples - state->playbackPos;

    size_t framesToPlay =
        std::min<size_t>(frameCount, remaining);

    memcpy(
        out,
        state->playbackBuffer + state->playbackPos,
        framesToPlay * sizeof(float));

    if (framesToPlay < frameCount)
    {
        memset(
            out + framesToPlay,
            0,
            (frameCount - framesToPlay) * sizeof(float));
    }

    state->playbackPos += framesToPlay;


    size_t recordRemaining =
        state->numSamples - state->recordPos;

    size_t framesToRecord =
        std::min<size_t>(frameCount, recordRemaining);

    memcpy(
        state->recordBuffer + state->recordPos,
        in,
        framesToRecord * sizeof(float));

    state->recordPos += framesToRecord;
}

int main(int argc, const char * argv[]) {
    
    Aurora::SineSweepGenerator ssweep{};
    size_t numSamples = ssweep.GetSamplerate() * 10;
    auto sweepAudio   = std::make_unique<float[]>(numSamples);
    auto recordedAudio   = std::make_unique<float[]>(numSamples);
    ssweep.Generate();
    ssweep.FillBlock(sweepAudio.get(), numSamples, 0, 0); // Sweep  == Channel_1
    
    auto filter  = std::make_unique<float[]>(numSamples);
//    ssweep.FillBlock(filter.get(),     numSamples, 0, 1); // Filter == Channel_2
    
    AudioData audio;
    
    SweepAudioState state{
        sweepAudio.get(),
        recordedAudio.get(),
        numSamples
    };

    ma_device_config config =
        ma_device_config_init(ma_device_type_duplex);

    config.sampleRate = ssweep.GetSamplerate();

    config.playback.format = ma_format_f32;
    config.playback.channels = 1;

    config.capture.format = ma_format_f32;
    config.capture.channels = 1;

    config.dataCallback = data_callback;
    config.pUserData = &state;

    ma_device device;

    if (ma_device_init(nullptr, &config, &device) != MA_SUCCESS)
    {
        throw std::runtime_error("Failed to initialise audio device");
    }

    ma_device_start(&device);
    
    // Or let things record for longer
    //    size_t recordSamples = numSamples + ssweep.GetSamplerate() * 2; // +2 seconds
    //    auto recordedAudio = std::make_unique<float[]>(recordSamples);
    //    while (state.recordPos < recordSamples)
    //    {
    //        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //    }
    
    while (state.playbackPos < numSamples)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    ma_device_stop(&device);
    ma_device_uninit(&device);
    
    writeToWav(recordedAudio.get(),  (uint32_t)numSamples, "recorded-audio-test.wav");
    
    //
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
    std::copy_n(sweepAudio.get(),  numSamples, input.Samples());
    
    convolver.DoConvolution();
    
    auto& conv = convolver.GetOutputTrack(0);
    conv.Reverse();
    
    writeToWav(conv.Samples(),  (uint32_t)conv.Length(), "recorded-sweep-ir.wav");
    
    return 0;
}
