/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations
                       plugin collection
                       
  Common libraries

  aurora.h

  Angelo Farina - Simone Campanini

**********************************************************************/
#ifndef __AURORA_H__
#define __AURORA_H__

#define  AURORA_VERSION_String   "5.3" //"4.3"
#define  AURORA_VERSION_MAJOR   5
#define  AURORA_VERSION_MINOR   3

inline constexpr unsigned int AuroraBuildNumber = 130;

/**
 *  \mainpage
 *  This is Aurora, a powerful set of plugin for advanced
 *  audio elaborations and analysis written originally by Angelo Farina
 *  as plug-ins for Cool Edit/Audition, and then converted as Audacity
 *  modules by Simone Campanini.
 */

/// Aurora Source
///

#include <SineSweepGenerator.h>
#include <AuroraConvolver.h>

#endif // __AURORA_VERSION_H__
