#pragma once
#include "headers.h"

const DWORD OceanPlaneHeight_Exit = 0xA8098F;
const DWORD ConfigureOceanReflection_Exit = 0xA80AA2;

const char enableReflections[] = {0xB0, 0x01};
const char poolJump[] = {0xEB, 0x36};
const float lotSkirtOffset = 0.55;

namespace Reflections
{
    void ForceLotReflections();
    void EnableTreeReflections();
    void EnablePoolTerrainReflections();
    extern "C" void AdjustLotSkirtOffset();
    extern "C" void EnableCastawayStyleReflections();
}