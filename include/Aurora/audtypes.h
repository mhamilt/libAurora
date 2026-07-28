/**********************************************************************
 
 Aurora for Audacity: A Powerful multiplatform Acoustic calculations
 plugin collection
 
 Common libraries
 
 audtypes.h
 
 Angelo Farina - Simone Campanini
 
 **********************************************************************/
#ifndef __AURORA_AUDTYPES_H__
#define __AURORA_AUDTYPES_H__

#include <cstddef>
// This files works as wrap between Audacity types definitions
// and Aurora classes

#define _AF_USE_FLOAT_

namespace Aurora
{
    typedef  float         Sample;
    typedef  size_t        SampleCount;
    typedef  float*        SamplePtr;
    typedef  SamplePtr     samplePtr;
//    typedef  sampleFormat  SampleFormat;

    enum MessageType
    {
        Info,
        Warning,
        Error,
        YesNo
    };
}

#endif // __AURORA_AUDTYPES_H__
