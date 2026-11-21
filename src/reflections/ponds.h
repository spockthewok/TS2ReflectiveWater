#pragma once

namespace Ponds
{
    extern "C" void InitPondCamera();
    extern "C" void DetachCameraOnShutdown();
    void FixVisibilityFilter();
    extern "C" void SetPlaneHeight();
    void UpdateCameraOnElevationChange();
}