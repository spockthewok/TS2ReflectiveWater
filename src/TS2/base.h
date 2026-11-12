#pragma once
#include "headers.h"
#include "TS2/cTSGlobals.h"
#include "TS2/cFloor.h"

namespace Module
{
    extern DWORD base;
}

namespace cRZString
{
    using ToCharFn = const char *(__fastcall *)(void *); // Actual param type is cRZString object
    extern ToCharFn ToChar;
}

namespace TS
{
    using GlobalsFn = cTSGlobals *(__cdecl *)();
    extern GlobalsFn Globals;
}

using RegisterEnvCubeForSkyBoxFn = void(__cdecl *)(const char *, const char *);
extern RegisterEnvCubeForSkyBoxFn RegisterEnvCubeForSkyBox;

using ConfigureReflectionCameraFn = void(__cdecl *)(nTSSG::cIFloor *);
extern ConfigureReflectionCameraFn ConfigureReflectionCamera;