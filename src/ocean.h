#pragma once
#include "hooking.h"
#include "TS2.h"

namespace Ocean
{
    void ForceLotReflections();
    extern "C" void AdjustLotSkirtOffset();
    extern "C" void EnableCastawayStyleReflections();
}