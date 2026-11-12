#include "TS2/base.h"

namespace Module
{
    DWORD base = 0x400000; // Default module base address
}

// Base addresses of various TS2 methods
namespace cRZString
{
    ToCharFn ToChar = reinterpret_cast<ToCharFn>(0x40FE7B);
}

namespace TS
{
    GlobalsFn Globals = reinterpret_cast<GlobalsFn>(0x799A0D);
}

RegisterEnvCubeForSkyBoxFn RegisterEnvCubeForSkyBox =
    reinterpret_cast<RegisterEnvCubeForSkyBoxFn>(0xA96480);

ConfigureReflectionCameraFn ConfigureReflectionCamera =
    reinterpret_cast<ConfigureReflectionCameraFn>(0xB62520);