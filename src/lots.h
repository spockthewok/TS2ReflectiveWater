#pragma once
#include "headers.h"
#include "shared.h"

const DWORD InitRenderStatesForNewSubsets_Exit = 0xA771CB;
const DWORD SetSubsetRenderStates_Exit_1 = 0xAE5634;
const DWORD SetSubsetRenderStates_Exit_2 = 0xAE59A7;

namespace Lots
{
    extern "C" void EnableWallReflections();
    extern "C" void EnableFloorReflections();
    extern "C" void EnableCeilingReflections();
}