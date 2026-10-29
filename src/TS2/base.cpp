#include "TS2/base.h"

// Base addresses of various TS2 methods
namespace cRZString
{
    const DWORD ToChar = 0x40FE7B;
}

namespace TS
{
    GetGlobals Globals = reinterpret_cast<GetGlobals>(0x799A0D);
}

DoRegisterEnvCubeForSkyBox RegisterEnvCubeForSkyBox = reinterpret_cast<DoRegisterEnvCubeForSkyBox>(0xA96480);

namespace cFloor
{
    const DWORD ConfigureReflectionCamera = 0xB62520;
}

namespace cWaterGeometryBuilder
{
    const DWORD SetWaterElevation = 0xB7C130;
}