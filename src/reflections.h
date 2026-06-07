#pragma once
#include "headers.h"

const DWORD OceanPlaneHeight_Exit = 0xA8098F;
const DWORD ConfigureOceanReflection_Exit = 0xA80AA2;
const DWORD RenderGroupManager = 0xE73960;

const char EnableReflections[] = {0xB0, 0x01};
const float lotSkirtOffset = 0.55;

namespace Reflections
{
    void ForceReflections();
    void EnableTreeReflections();
    extern "C" void AdjustLotSkirtOffset();
    extern "C" void EnableCastawayStyleReflections();
}