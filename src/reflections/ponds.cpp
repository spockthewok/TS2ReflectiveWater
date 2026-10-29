#include "reflections/ponds.h"
#include "hooking.h"
#include "TS2/base.h"
#include "TS2/cWorldDB.h"
#include <array>

namespace
{
    const DWORD SetWaterElevation_Exit = 0xAE1095;
    const DWORD Shutdown_Exit = 0xAE4886;
    const DWORD Initialize_Exit = 0xAE63CF;
    const DWORD ConfigureReflectionCamera_Exit_1 = 0xB62653;
    const DWORD ConfigureReflectionCamera_Exit_2 = 0xB626FE;
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
        Hooking::Nop((BYTE *)0xB62256, 22);
    }

    // We only really care about water elevation calculated by cWorldDB::IsWaterVertex
    // If no pond water is found, elevation will be -0.5
    static void FindPondWater(nTSWorld::cWorldDB *worldDB)
    {
        int maxX = static_cast<int>(worldDB->MaxX());
        int maxY = static_cast<int>(worldDB->MaxY());
        std::array<int, 3> cVertex = {0, 0, 0};

        for (int y = 0; y <= maxY; ++y)
        {
            for (int x = 0; x <= maxX; ++x)
            {
                cVertex[0] = x;
                cVertex[1] = y;

                if (worldDB->IsWaterVertex(cVertex.data()))
                    return;
            }
        }
    }

    // (anonymous_namespace)::ConfigureReflectionCamera
    // Iterates through tiles in lot searching for pond water
    // Sets reflection plane height to elevation of water
    void __declspec(naked) SetPlaneHeight()
    {
        __asm {
            push esi
            call FindPondWater
            add esp,0x4
            fld [esp-0x44] // Water elevation calculated by cWorldDB::IsWaterVertex
            fstp [esp+0x48]
            jmp ConfigureReflectionCamera_Exit_1
        }
    }

    // (anonymous_namespace)::ConfigureReflectionCamera
    // Extends floor viewer node config so ponds are as reflective as ocean
    void __declspec(naked) ConfigureViewer()
    {
        __asm {
            push 0x7 // 7 = kRenderTypePoolReflection
            lea eax,[esp+0x2C]
            push eax
            push esi
            mov ecx,edi
            call [edx+0x194]
            mov edx,[edi]
            push 0x2 // 2 = kRenderTypeReflection
            mov ecx,edi
            call [edx+0x184]
            mov edx,[edi]
            push 0x1
            mov ecx,edi
            call [edx+0x1EC]
            mov edx,[edi]
            push 0x123AF80 // "lotSkirtReflectionSkybox"
            push 0x0
            mov ecx,edi
            call [edx+0x1F0]
            mov edx,[edi]
            push -0x1
            mov ecx,edi
            call [edx+0x140]
            mov edx,[edi]
            push -0x1
            mov ecx,edi
            call [edx+0x138]
            jmp ConfigureReflectionCamera_Exit_2
        }
    }

    // cTerrain::SetWaterElevation
    // Updates reflection camera when player uses terrain tools
    // Ensures reflection matches changes to water elevation
    void __declspec(naked) UpdateCameraOnElevationChange()
    {
        __asm {
            call cWaterGeometryBuilder::SetWaterElevation
            mov eax,dword ptr ds:[0x1478F10] // nTSSG::cTSSGSystem
            mov edx,[eax]
            mov ecx,eax
            call [edx+0x98] // cTSSGSystem::FloorManager
            test eax,eax
            jz LAB_Exit
            mov edx,[eax]
            push 0x0 // Level of cFloor object we want from manager
            mov ecx,eax
            call [edx+0x4C] // cFloorManager::Floor
            test eax,eax
            jz LAB_Exit
            push eax
            call cFloor::ConfigureReflectionCamera
            add esp,0x4
        LAB_Exit:
            jmp SetWaterElevation_Exit
        }
    }
}