#include "TS2.h"

// Base addresses of various TS2 methods
namespace cRZString
{
    const DWORD ToChar = 0x40FE7B;
}

namespace nTSWorld
{
    const DWORD TSSGSystem = 0x42CF1B;
}

namespace cTSGlobals
{
    const DWORD GetSimulator = 0x72A999;
}

namespace TS
{
    const DWORD Globals = 0x799A0D;
}

namespace cLightingManager
{
    const DWORD RegisterEnvCubeForSkyBox = 0xA96480;
}

namespace cFloor
{
    const DWORD SetReflectionState = 0xAE4C50;
    const DWORD ConfigureReflectionCamera = 0xB62520;
}

namespace cWaterGeometryBuilder
{
    const DWORD SetWaterElevation = 0xB7C130;
}

namespace Unknown
{
    const DWORD FloatToInt = 0xE5C948;
}