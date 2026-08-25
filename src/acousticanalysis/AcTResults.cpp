//
//  AcTResults.cpp
//  mod-aurora
//
//  Created by Matthew Hamilton on 13/10/2023.
//

#include <Aurora/AcTResults.h>


//----------------------------------------------------------------------------
// Aurora::AcousticalParameters::TResults implementation
//----------------------------------------------------------------------------
Aurora::TResults::TParameter::TParameter(const double v,
                                                               const bool   valid)
    : value(v), isValid(valid)
{
    if (std::isnan(value) || std::isinf(value))
    {
        // nan and infinite values are always unacceptable.
        isValid = false;
    }
}

const std::vector<std::string> Aurora::TResults::m_parameterNames =
{
    "T30",
    "EDT",
    "D50",
    "C50",
    "C80",
    "Signal",
    "Noise",
    "strenGth",
    "Ts",
    "Tuser",
    "T20",
    "Peakiness",
    "Millisecondness",
    "Impulsiveness",
    // StageParameters (14..)
    "St1",
    "St2",
    "StLate",
    // BinauralParameters (17..)
    "IACC",
    "tauIACC",
    "widthIACC",
    // SpatialParameters  (20..)
    "Jlf",
    "Jlfc",
    "Lj",
};

void Aurora::TResults::Set(const std::string& parameterName,
                                                 const float fcb,
                                                 const double value,
                                                 const bool   valid)
{
    m_table.at(parameterName).SetValue(fcb, TParameter(value, valid));
}

void Aurora::TResults::SetSpectrumType(const Aurora::SpectrumType type)
{
    m_table.clear();
    
    for(auto& np : m_parameterNames)
    {
        m_table[np] = Aurora::Spectrum<TParameter>(type);
    }
}

Aurora::TResults::TResults()
{
    SetSpectrumType(Aurora::SpectrumType::Octave);
}

