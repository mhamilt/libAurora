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
//    Aurora::ConvolverController::Reset();
//    Aurora::ConvolverController::SetSamplerate(mProjectRate); // ???
//    SetFilterMatrixDimensions
//    DoConvolution OR DoMatrixConvolution
    
//    bool Aurora::ConvolverEffect::LoadTrackData(WaveTrack *wt, int idx, bool is_ir)
//    {
//        Aurora::SampleCount start;
//        Aurora::SampleCount end;
//
//        //Get start and end times from track
//        double trackStart = wt->GetStartTime();
//        double trackEnd   = wt->GetEndTime();
//
//        //Set the current bounds to whichever left marker is
//        //greater and whichever right marker is less:
//        double t0 = mT0 < trackStart? trackStart: mT0;
//        double t1 = mT1 > trackEnd  ? trackEnd  : mT1;
//
//        // Process only if the right marker is to the right of the left marker
//        if (t1 > t0)
//        {
//            //Checks the track rate, samples, minimum, maximum and name
//            if (! CheckSamplerate(wt->GetRate()))
//            {
//                return false;
//            }
//
//            //Transform the marker timepoints to samples
//            start = wt->TimeToLongSamples(t0).as_size_t();
//            end   = wt->TimeToLongSamples(t1).as_size_t();
//
//            if(is_ir)
//            {
//                if (ResizeFilterTrack(idx, end - start))
//                {
//                    Aurora::Vector<Aurora::Sample>& f = GetFilters()[idx];
//                    
//                    wt->Get((samplePtr)f.Samples(),
//                            floatSample,
//                            sampleCount(start),
//                            f.Length());
//                }
//            }
//            else
//            {
//                if (ResizeInputTrack(idx, end - start))
//                {
//                    Aurora::Vector<Aurora::Sample>& in = GetInputTrack(idx);
//                    wt->Get((samplePtr)in.Samples(),
//                            floatSample,
//                            sampleCount(start),
//                            in.Length());
//                }
//            }
//        }
//        return true;
//    }
//    
    
    
    std::cout << "convolver.GetGain():" << convolver.GetGain() << '\n';
    
    return 0;
}
