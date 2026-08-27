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

// Actually an anonymous namespace according to macOS binary
// Only XREF is cLightingManager, hence the namespace used here
namespace cLightingManager
{
    extern const DWORD RegisterEnvCubeForSkyBox;
}