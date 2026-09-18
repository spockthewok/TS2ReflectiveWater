#pragma once
#include "hooking.h"
#include "TS2.h"
#include "config.h"

namespace Ocean
{
    void ForceLotReflections();
    extern "C" void AdjustLotSkirtOffset();
    extern "C" void EnableCastawayStyleReflections();
}