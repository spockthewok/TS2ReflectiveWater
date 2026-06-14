#pragma once
#include "headers.h"
#include "hooking.h"

const DWORD SetSubsetRenderStates_Exit = 0xAE1A66;

const char poolJump[] = {0xEB, 0x36};

namespace Terrain
{
    void EnablePoolTerrainReflections();
    extern "C" void EnableLotTerrainReflections();
}