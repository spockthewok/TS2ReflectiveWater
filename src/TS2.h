#pragma once
#include "headers.h"

namespace cRZString
{
    extern const DWORD ToChar;
}

namespace nTSWorld
{
    extern const DWORD TSSGSystem;
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

namespace cFloor
{
    extern const DWORD SetReflectionState;
    // This also belongs to an anonymous namespace, but it's only used by floors
    extern const DWORD ConfigureReflectionCamera;
}

namespace cWaterGeometryBuilder
{
    extern const DWORD SetWaterElevation;
}

namespace Unknown
{
    // No idea if this is the name of this method
    // macOS does its operations inline, or just performs a cast
    extern const DWORD FloatToInt;
}