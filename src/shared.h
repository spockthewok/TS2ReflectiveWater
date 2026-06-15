#pragma once
#include "headers.h"

namespace cRZString
{
    extern const DWORD ToChar;
}

namespace cTSGlobals
{
    extern const DWORD GetSimulator;
}

namespace TS
{
    extern const DWORD Globals;
}
// Actually an anonymous namespace according to the macOS binary, but it's only used by the cLightingManager object
namespace cLightingManager
{
    extern const DWORD RegisterEnvCubeForSkyBox;
}

namespace Shared
{
    extern const char enableReflections[2];
}