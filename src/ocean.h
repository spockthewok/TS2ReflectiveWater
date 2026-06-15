#pragma once
#include "headers.h"
#include "hooking.h"
#include "shared.h"

namespace Ocean
{
    void ForceLotReflections();
    extern "C" void AdjustLotSkirtOffset();
    extern "C" void EnableCastawayStyleReflections();
}