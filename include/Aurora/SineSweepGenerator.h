/**********************************************************************
 
 Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 plugin collection
 
 Sine Sweep Signal Generator
 
 sswgen.h
 
 Angelo Farina - Simone Campanini
 
 **********************************************************************/
#ifndef __AURORA_SSWGEN_H__
#define __AURORA_SSWGEN_H__

#include <Aurora/commdefs.h>
#include <Aurora/Vector.h>

namespace Aurora
{
class SineSweepGenerator
{
public:
    /// <#Description#>
    enum Channels
    {
        //CH_LEFT, CH_RIGHT,
        CH_INV_FILT = 2,
        CH_PULSES,
        _N_TRACKS_
    };
    
    /// <#Description#>
    enum SweepTypes
    {
        ST_LINEAR,
        ST_LOG,
        ST_PINK
    };
    
    /// <#Description#>
    enum FadeTypes
    {
        FT_RECT,
        FT_HAMMING,
        FT_HANN,
        FT_QUARTER_SINE,
        FT_LINEAR,
        FT_GAUSSIAN,
        FT_BLACKMANN,
        FT_BLACK_HARRIS,
        FT_LOG
    };
    
    /// <#Description#>
    enum ErrorCodes
    {
        ERR_OK = 0,
        ERR_SWEEP_LIMITS = 5000,
        ERR_DURATION,
        ERR_AMPLITUDE,
        ERR_CHANNELS_N,
        ERR_FADE_IN,
        ERR_FADE_OUT,
        ERR_SILENCE,
        ERR_CYCLES_N
    };
    
public:
    
    // --- ctors
    SineSweepGenerator();
    ~SineSweepGenerator();
    // ---------------------------------------------------------------------------
    /// <#Description#>
    void Destroy();
    
    /// Check for input errors
    int ErrorCheck();
    
    /// Generates the normal and inverse sine sweep, allocating memory to the internal buffers.
    /// Call this after setting all desired parameters
    bool Generate();
        
    /// Fill data block (module interface)
    /// Used for environments where audio buffers are passed.
    /// Defaults:
    /// - track / channel 0: sweep data
    /// - track / channel 1: filter / inverse sine sweeap data
    ///
    /// @param pData  pointer to the audio buffer
    /// @param len  number of samples to write
    /// @param written  the offset within the internal sweep buffer
    /// @param nTrack  track / channel number: given the value of GetNeededTracks, the last track is always the filter track
    void FillBlock(Sample* pData,
                   SampleCount len,
                   SampleCount written,
                   int nTrack);
    // ---------------------------------------------------------------------------
    // Checkers
    
    /// <#Description#>
    bool IsControlPulsesSet()    const { return m_bControlPulses; }
    
    // ---------------------------------------------------------------------------
    //    //Getters
    /// <#Description#>
    /// @param wxszMsg  <#wxszMsg description#>
    void      GetErrorMessage(std::string& wxszMsg);
    /// <#Description#>
    int          GetErrorCode() const { return m_nErrNo; }
    /// <#Description#>
    double      GetSamplerate() const { return m_dbRate; }
    /// <#Description#>
    double  GetStartFrequency() const { return m_dbLowFrq; }
    /// <#Description#>
    double    GetEndFrequency() const { return m_dbHighFrq; }
    /// <#Description#>
    double   GetSweepDuration() const { return m_dbSweepDuration; }
    /// <#Description#>
    double GetSilenceDuration() const { return m_dbSilenceDuration; }
    /// <#Description#>
    double       GetAmplitude() const { return m_dbAmplitude; }
    /// <#Description#>
    int  GetRepetitionsNumber() const { return m_nCycles; }
    /// <#Description#>
    int          GetSweepType() const { return m_nSweepType; }
    /// <#Description#>
    int       GetNeededTracks() const { return m_nChnlsCount; }
    /// <#Description#>
    double  GetFadeInDuration() const { return m_dbFadeInDuration; }
    /// <#Description#>
    double GetFadeOutDuration() const { return m_dbFadeOutDuration; }
    /// <#Description#>
    int         GetFadeInType() const { return m_nFadeInType; }
    /// <#Description#>
    int        GetFadeOutType() const { return m_nFadeOutType; }
    /// <#Description#>
    double          GetDeltaL() const { return m_dbDeltaL; }
    /// <#Description#>
    int     GetChannelsNumber() const { return m_nChnlsCount; }
    /// <#Description#>
    int   GetSweepChnlsNumber() const { return m_nSweepChnlsCount; }
    /// <#Description#>
    int GetFilterChannel() const { return m_nFilterChnlIdx; }
    int      GetPulsesChannel() const { return m_nPulsesChnlIdx; }
    /// Get current duration of sweep buffer in seconds given the current silence and sweep duration
    double   GetTotalDuration() const { return m_buffersLength/m_dbRate; }
    
    /// <#Description#>
    /// @param nCh  <#nCh description#>
    const TSampleVector&  GetBuffer(int nCh) const { return m_buffers[nCh]; }
    /// <#Description#>
    /// @param nCh  <#nCh description#>
    const TSampleVector&  GetFilter(int nCh) const { return m_buffers[m_nFilterChnlIdx]; }
    
    /// Get the length of the sweep buffer in samples given the current sweep duration, silenceduration and number of channels
    SampleCount GetBuffersLength() const { return m_buffersLength; }
    /// Get the length of the filter buffer in samples given the current sweep duration, silenceduration and number of channels
    SampleCount  GetFilterLength() const { return m_filterLength; }
    // ---------------------------------------------------------------------------
    // Setters
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void      SetSamplerate(double dbValue)  { m_dbRate    = dbValue; }
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void  SetStartFrequency(double dbValue)  { m_dbLowFrq  = dbValue; }
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void    SetEndFrequency(double dbValue)  { m_dbHighFrq = dbValue; }
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void   SetHighFrequency(double dbValue)  { m_dbHighFrq = dbValue; }
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void    SetLowFrequency(double dbValue)  { m_dbLowFrq  = dbValue; }
    /// Set sweep duration
    ///
    /// @param dbValue sweep duration in seconds
    void   SetSweepDuration(double dbValue)  { m_dbSweepDuration   = dbValue; }
    /// Sets the duration of silence.
    /// @param dbValue silence duration in seconds
    void SetSilenceDuration(double dbValue)  { m_dbSilenceDuration = dbValue; }
    
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void         SetAmplitude(double dbValue)  { m_dbAmplitude = dbValue; }
    /// <#Description#>
    /// @param nValue  <#nValue description#>
    void SetRepetitionsNumber(int nValue)    { m_nCycles = nValue; }
    /// <#Description#>
    /// @param nValue  <#nValue description#>
    void         SetSweepType(int nValue)    { m_nSweepType = nValue; }
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void    SetFadeInDuration(double dbValue) { m_dbFadeInDuration  = (dbValue < 100) ? dbValue : dbValue*m_dbRate; }
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void   SetFadeOutDuration(double dbValue) { m_dbFadeOutDuration = (dbValue < 100) ? dbValue : dbValue*m_dbRate; }
    
    /// <#Description#>
    /// @param nValue  <#nValue description#>
    void        SetFadeInType(int nValue)     { m_nFadeInType = nValue; }
    /// <#Description#>
    /// @param nValue  <#nValue description#>
    void       SetFadeOutType(int nValue)     { m_nFadeOutType = nValue; }
    /// <#Description#>
    /// @param dbValue  <#dbValue description#>
    void            SetDeltaL(double dbValue) { m_dbDeltaL = dbValue; }

    /// <#Description#>
    /// @param bValue  <#bValue description#>
    /// @note Required
    void     SetControlPulses(bool bValue);
    
    /// <#Description#>
    /// @param nValue  <#nValue description#>
    void  SetSweepChnlsNumber(int nValue);
    ///
    /// @param len  <#len description#>
    /// @param bInitBuffer <#bInitBuffer#>
    /// @param nCh <#nCh#>
    /// @warning Not yet implemented
    void SetBuffersLength(SampleCount len,
                          const bool bInitBuffer = false,
                          const int nCh = 0);
    // ---------------------------------------------------------------------------
private:
    
    ///
    void InitDataBuffers();
    ///
    void DeleteDataBuffers();
    
private:
    ///
    int    m_nErrNo = ERR_OK;
    ///
    double m_dbRate            = 48000.0; // Hz
    ///
    double m_dbHighFrq         = 22000.0; // Hz
    ///
    double m_dbLowFrq          = 22.0;    // Hz
    ///
    double m_dbSweepDuration   = 10.0; // s
    ///
    double m_dbAmplitude       =  1.0;
    ///
    double m_dbSilenceDuration =  8.0; // s
    ///
    int    m_nCycles           = 1;
    ///
    double m_dbFadeInDuration  = 0.1;  // s
    ///
    double m_dbFadeOutDuration = 0.1;  // s
    ///
    int    m_nFadeInType       = FT_HANN;
    ///
    int    m_nFadeOutType      = FT_HANN;
    ///
    double m_dbDeltaL          =  0.0;
    ///
    int    m_nChnlsCount       =  2; // Sweep Mono + Inverse filter
    ///
    int    m_nSweepChnlsCount  =  1; // default mono
    ///
    int    m_nFilterChnlIdx    =  1; // sweep on channel 0, filter on channel 1
    ///
    int    m_nPulsesChnlIdx    = -1; // by default no control pulses
    ///
    std::vector<TSampleVector> m_buffers;
    
    ///
    SampleCount m_buffersLength = 0; // samples
    ///
    SampleCount m_sweepLength   = 0; // samples
    ///
    SampleCount m_filterLength  = 0; // samples
    ///
    int m_nSweepType = ST_LOG;
    ///
    bool m_bControlPulses = false;
    
};
} // namespace Aurora

#endif // __AURORA_SSWGEN_H__
