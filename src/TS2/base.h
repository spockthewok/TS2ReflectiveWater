#pragma once
#include "headers.h"
#include "TS2/cTSGlobals.h"

namespace cRZString
{
    extern const DWORD ToChar;
}

namespace TS
{
    using GetGlobals = cTSGlobals *(__cdecl *)();
    extern GetGlobals Globals;
}

using DoRegisterEnvCubeForSkyBox = void(__cdecl *)(const char *, const char *);
extern DoRegisterEnvCubeForSkyBox RegisterEnvCubeForSkyBox;

namespace cFloor
{
    extern const DWORD ConfigureReflectionCamera;
}

namespace cWaterGeometryBuilder
{
    extern const DWORD SetWaterElevation;
}