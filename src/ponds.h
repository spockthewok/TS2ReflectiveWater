#pragma once
#include "hooking.h"
#include "TS2.h"

namespace Ponds
{
    extern "C" void InitPondCamera();
    extern "C" void DetachCameraOnShutdown();
    void FixVisibilityFilter();
    extern "C" void SetPlaneHeight();
    extern "C" void UpdateCameraOnElevationChange();
}