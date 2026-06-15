#include "shared.h"

// Base addresses of various TS2 methods
namespace cRZString
{
    const DWORD ToChar = 0x40FE7B;
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

namespace Shared
{
    // General purpose bytecode for "MOV AL,0x1"
    const char enableReflections[2] = {0xB0, 0x01};
}