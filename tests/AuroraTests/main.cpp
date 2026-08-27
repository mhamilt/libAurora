#include <iostream>
#include <memory>
#include <algorithm>
#include <Aurora/aurora.h>
#include <kiss_fft.h>
#include "matts_audio.h"

int main()
{
    //------------------------------------------------------------------------
    // SineSweep Generator
    Aurora::SineSweepGenerator ssweep{};
    ssweep.SetSweepDuration(1.0);
    ssweep.SetSilenceDuration(1.0);
    ssweep.Generate();
    
    size_t numSamples  = ssweep.GetBuffersLength();
    auto filter  = std::make_unique<float[]>(numSamples);
    auto audio   = std::make_unique<float[]>(numSamples);
    
    
    ssweep.FillBlock(audio.get() ,  numSamples, 0, 0); // Sweep  == Channel_1
    ssweep.FillBlock(filter.get(),  numSamples, 0, 1); // Filter == Channel_2
    
    const auto sampleRate =  ssweep.GetSamplerate();
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
    
           writeToWav(audio.get(),  (uint32_t)numSamples, "sweep-audio.wav");
           writeToWav(filter.get(), (uint32_t)numSamples, "sweep-inver.wav");
           writeToWav(conv.Samples(),  (uint32_t)numSamples, "sweep-convo.wav");
    
    //------------------------------------------------------------------------
    // Acoustical Parameters
    
    //    Aurora::AcousticalParameters acParams{};
    //
    //    auto& parameterTracks = acParams.Tracks();
    //    parameterTracks.emplace_back(Aurora::AcParametersAudioTrack(numSamples, ssweep.GetSamplerate()));
    //    auto& audioAnalysisTrack = parameterTracks.back();
    //    std::copy_n(conv.Samples(), numSamples, audioAnalysisTrack.Samples());
    //
    //    acParams.Init();
    //
    //    auto& auroraTrack = acParams.Track(0);
    //
    //    // Then process parameterTracks
    //    acParams.CalculateAcousticParameters();
    //    const auto& result = acParams.Results(0);
    //    const auto& fcbs = result.Frequencies();
    //    result.Parameters();
    //
    //    for (const auto& paramater : result.Parameters())
    //    {
    //        for (const auto& fcb : fcbs)
    //        {
    //            std::cout << paramater << " (" << fcb << "): " << result.Get(paramater, fcb).value <<'\n';
    //        }
    //    }
    
    //------------------------------------------------------------------------
    // Kirkeby
    
    // const int nTracks = 2; // filter and sweep
    // Aurora::Kirkeby kirkeby{nTracks};
    // kirkeby.SetSamplerate(sampleRate);
    //    kirkeby.SetInputTrackLength();
    //    SetInverseFilterLength((Aurora::SampleCount)filterLength);
///
    // kirkeby.Init();
// Aurora::Kirkeby::SetInputTracks(std::vector<std::vector<float*>>)
//    LoadTracks()
    // Use GetInputTrackItem to copy tracks in the right order
//    while(col < nColsNo)
//            {
//                auto& input = GetInputTrackItem(nRow, nCol);
//
//                if(input.IsNull())
//                {
//                    printf("Error in memory allocation\n");
//                    return false;
//                }
//                wt->Get((samplePtr)input.Samples(),
//                        floatSample,
//                        m_start + col * nColumnWidth,
//                        nColumnWidth);
//                col++;
//            }
//    kirkeby.Process();
    //    while(nRow < GetRows())
    //    {
    //        name.Printf("Inverse Filter %d", nRow + 1);
    //        auto wt = mFactory->NewWaveTrack(floatSample, mProjectRate);
    //        nCol = 0;
    //
    //        while(nCol < GetCols())
    //        {
    //            samplePtr data = (samplePtr)GetOutputTrackItem(nRow, nCol).Samples();
    //            auto length = GetInverseFilterLength();
    //
    //            wt->Append(data, floatSample, length );
    //            nCol++;
    //        }
    //        wt->Flush();
    //        wt->SetName(name);
    //        AddToOutputTracks(wt);
    //        nRow++;
    //    }

    
    //------------------------------------------------------------------------
    // Speech Transmission Index
    
    Aurora::STI sti;
    
//    DoFullscaleCalibration(const bool bIsStereo)
//    {
//        const int nChnls = bIsStereo ? 2 : 1;
//        std::array<Aurora::STIAudioTrack, 2> calibrationSignal;
//        
//        for(int nCh = 0; nCh < nChnls; nCh++)
//        {
//            calibrationSignal[nCh].SetRate(mProjectRate);
//            
//            if( ! LoadTrackData(calibrationSignal[nCh], nCh, m_anCalibrationTracksIdx[nCh]-1))
//            {
//                return false;
//            }
//            CalibrateFullscale(calibrationSignal[nCh], nCh);
//        }

    //    std::array<Aurora::STIAudioTrack, 2> calibrationSignal;
    //    calibrationSignal[nCh].SetRate(mProjectRate);
    //     sti.CalibrateFullscale
    //    DoSNRatioCalculation(const bool bIsStereo)
    {
        //        const int nChnls = bIsStereo ? 2 : 1;
        
        //        std::array<Aurora::STIAudioTrack, 2> signal;
        //        std::array<Aurora::STIAudioTrack, 2> noise;
        
        //        std::vector<int> ranges = { nChnls, 12 };
        
        //        for(int nCh = 0; nCh < nChnls; nCh++)
        //        {
        //            signal[nCh].SetRate(mProjectRate);
        //            noise [nCh].SetRate(mProjectRate);
        
        //            LoadTrackData(signal[nCh], nCh, m_anSignalTracksIdx[nCh]-1);
        //            LoadTrackData(noise [nCh], nCh, m_anNoiseTracksIdx [nCh]-1);
        //            sti.StoreSpectrums(signal[nCh], noise[nCh], nCh) );
        
        //        }
        
        //        DoSTICalculation()
        {
            //            int nChnls = m_bIsStereo ? 2 : 1;
            //            std::array<Aurora::STIAudioTrack, 2> tracks;
            //            std::vector<int> ranges = { nChnls, 7 };
            //
            //            for(int nCh = 0; nCh < nChnls; nCh++)
            //            {
            //                tracks[nCh].SetRate(mProjectRate);
            //                LoadTrackData(tracks[nCh], nCh, m_anIrTracksIdx[nCh]-1))
            //                sti.CalculateMatrix(tracks[nCh], nCh);
            //            };
//            sti.DoSTI(<#const int nChnl#>, <#const int nSex#>)
//            sti.DoSNR(<#const int nChnl#>)
//            sti.DoRaSTI(<#const int nChnl#>)
//            sti.DoSTIPa(<#const int nChnl#>)
//            sti.DoSTItel(<#const int nChnl#>)
        }
    }
    //------------------------------------------------------------------------
    // Cross Functions
    
    // Aurora::Correlator corr;
    // corr.SetSamplerate(sampleRate);
    // XFunctions works with two (2) tracks. No less, no more.
    //    corr.CopyInputTracks(); // Set up mOutputTracks.
    //    corr.SetXFunctionType(index);
    //    m_pXf->GetAutocorrelationSpectrum(CH_LEFT)
    //    m_pXf->GetFunctionSpectrum();
    //    m_pXf->GetAlphaSpectrum(),
    //    m_pXf->GetCoherenceSpectrum(),
    
    //------------------------------------------------------------------------
    // Time History Analyzer
    
    // Aurora::TimeHistoryAnalyzer tha;
//    tha.SetChannelsNumber
//    tha.LoadTracks()
    {
        //    DoAnalysis()
        //        for(size_t nCh = 0; nCh < m_aSignalTracks.size(); nCh++)
        //        {
        //            auto dest = dynamic_cast<Aurora::AudioTrack*>(&m_aSignalTracks[nCh]);
        //          LoadTrackData(m_aSignalTracks[nCh].GetIndex(), dest)
        //        }
        // tha.Analyze()
        // Append Tracks
        //    if(m_aSignalTracks[0].GetSelectedFilter() != Aurora::AudioTrack::FLT_NONE)  // TODO what's mean this????
        //    {
        //        // If prompt user return true, add to workspace filtered tracks.
        //        for(size_t nCh = 0; nCh < m_aSignalTracks.size(); nCh++)
        //        {
        //            name = m_aSignalTracks[nCh].GetName();
        //            //         name.Printf(wxT("Ch %d"), nCh);
        //
        //            switch(m_aSignalTracks[nCh].GetSelectedFilter())
        //            {
        //                case Aurora::AudioTrack::FLT_ITU: name << " ITU filtered"; break;
        //                case Aurora::AudioTrack::FLT_IEC: name << " IEC filtered"; break;
        //                case Aurora::AudioTrack::FLT_ISO: name << " ISO filtered"; break;
        //                case Aurora::AudioTrack::FLT_UNI: name << " UNI filtered"; break;
        //                default: // shouldn't arrive here...
        //                    name << " not really filtered";
        //                    break;
        //            }
        //            name << " [" << int(nCh+1) << "]";
        //
        //            auto wt = mFactory->NewWaveTrack(floatSample, mProjectRate);
        //            wt->Append((samplePtr)m_aSignalTracks[nCh].Filtered().Samples(),
        //                       floatSample,
        //                       m_aSignalTracks[nCh].GetLength() );
        //            wt->Flush();
        //            wt->SetName(name);
        //            AddToOutputTracks(wt);
        //        }
        //        this->ReplaceProcessedTracks(true);
        //    }
        
//        auto& results = tha.GetResults();
    }
}
