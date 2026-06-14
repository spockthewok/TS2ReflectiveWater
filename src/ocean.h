#pragma once
#include "headers.h"
#include "hooking.h"
#include "shared.h"

const DWORD ConfigureOceanReflection_Exit_1 = 0xA8098F;
const DWORD ConfigureOceanReflection_Exit_2 = 0xA80AA2;

const float lotSkirtOffset = 0.45;

namespace Ocean
{
    void ForceLotReflections();
    extern "C" void AdjustLotSkirtOffset();
    extern "C" void EnableCastawayStyleReflections();
}