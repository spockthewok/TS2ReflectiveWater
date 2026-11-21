#define NOMINMAX
#include "reflections/ponds.h"
#include "hooking.h"
#include "TS2/base.h"
#include "TS2/cWorldDB.h"
#include "TS2/cTerrain.h"
#include <algorithm>
#include <array>
#include <cmath>

namespace
{
    constexpr DWORD Shutdown_Exit = 0xAE4886;
    constexpr DWORD Initialize_Exit = 0xAE63CF;
    constexpr DWORD ConfigureReflectionCamera_Exit = 0xB62653;
}

// Repurposes the unused floor reflection system for pond water
// Not compatible with TS2BetaFloors
namespace Ponds
{
    // cFloor::Initialize
    // Attaches reflection camera for cFloor object at level 0
    void __declspec(naked) InitPondCamera()
    {
        __asm {
            mov ecx,ebx
            call [eax+0xC]
            cmp ebp,0x0 // EBP = current level
            jne LAB_Exit
            mov [esi+0x80],0x1 // Set var required for camera
            pushad
            mov edx,[esi]
            push 0x1
            mov ecx,esi
            call [edx+0x48] // cFloor::SetReflectionState
            popad
        LAB_Exit:
            jmp Initialize_Exit
        }
    }

    // cFloor::Shutdown
    // Detaches camera as part of object destruction when exiting a lot
    void __declspec(naked) DetachCameraOnShutdown()
    {
        __asm {
            cmp [esi+0x80],0x0
            je LAB_Exit
            pushad
            mov edx,[esi]
            push 0x0
            mov ecx,esi
            call [edx+0x48] // cFloor::SetReflectionState
            popad
            mov [esi+0x80],0x0
        LAB_Exit:
            mov ecx,[esi+0x84]
            jmp Shutdown_Exit
        }
    }

    // cFloorReflectionVisibilityQueryFilter::TestNode
    // Patches out height range checks in visibility filter that cause reflection ghosting
    // It's possible to fix this by subtracting 0.75 from lower bound for certain node types
    // This is much simpler and achieves the same result
    void FixVisibilityFilter()
    {
        Hooking::Nop((0x762256 + Module::base), 22);
    }

    static float GetWaterElevation(nTSWorld::cWorldDB *worldDB)
    {
        std::array<int, 3> cVertex = {0, 0, 0};
        int minX = static_cast<int>(worldDB->MinX());
        int minY = static_cast<int>(worldDB->MinY());
        int maxX = static_cast<int>(worldDB->MaxX());
        int maxY = static_cast<int>(worldDB->MaxY());
        float elevation = -std::numeric_limits<float>::infinity(); // For the sake of std::max

        for (int y = minY; y <= maxY; ++y)
        {
            for (int x = minX; x <= maxX; ++x)
            {
                cVertex[0] = x;
                cVertex[1] = y;

                if (worldDB->IsWaterVertex(cVertex.data()))
                {
                    float currElevation = worldDB->WaterElevation(x, y);
                    elevation = std::max(elevation, currElevation);
                }
            }
        }

        if (std::isinf(elevation))
            return worldDB->WaterElevation(cVertex[0], cVertex[1]); // Defaults to -0.5 if no water

        return elevation;
    }

    // (anonymous_namespace)::ConfigureReflectionCamera
    // Iterates through tiles in lot searching for pond water
    // Sets reflection plane height to elevation of water
    void __declspec(naked) SetPlaneHeight()
    {
        __asm {
            mov esi,dword ptr ds:[0x1479BE4]
            push esi
            call GetWaterElevation
            add esp,0x4
            fstp [esp+0x48]
            jmp ConfigureReflectionCamera_Exit
        }
    }

    // The dummy param only exists to maintain the expected stack layout
    static void __fastcall SetWaterElevationHook(nTSSG::cTerrain *terrain, void *dummy,
                                                 UINT x, UINT y, float elevation)
    {
        terrain->SetWaterElevation(x, y, elevation);
    }

    // cTerrain::SetWaterElevation
    // Replaces method with our own that updates reflection camera when player uses terrain tools
    // Ensures reflection matches changes to water elevation
    void UpdateCameraOnElevationChange()
    {
        Hooking::MakeJMP((0x6E1060 + Module::base), (DWORD)SetWaterElevationHook, 7);
    }
}