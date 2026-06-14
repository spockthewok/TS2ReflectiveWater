#include "core.h"

namespace Core
{
    void InjectPatches()
    {
        // Ocean
        Ocean::ForceLotReflections();
        Hooking::MakeJMP((BYTE *)0xA80989, (DWORD)Ocean::AdjustLotSkirtOffset, 6);
        Hooking::MakeJMP((BYTE *)0xA809D3, (DWORD)Ocean::EnableCastawayStyleReflections, 6);
        // Props
        Props::EnableTreeReflections();
        // Lots
        Hooking::MakeJMP((BYTE *)0xA771C5, (DWORD)Lots::EnableWallReflections, 6);
        Hooking::MakeJMP((BYTE *)0xAE562F, (DWORD)Lots::EnableFloorReflections, 5);
        Hooking::MakeJMP((BYTE *)0xAE59A2, (DWORD)Lots::EnableCeilingReflections, 5);
        // Terrain
        Terrain::EnablePoolTerrainReflections();
        Hooking::MakeJMP((BYTE *)0xAE1A61, (DWORD)Terrain::EnableLotTerrainReflections, 5);
        // Skyboxes
        Hooking::MakeJMP((BYTE *)0x7F54D3, (DWORD)Skyboxes::GetPrecipitationType, 6);
        Hooking::MakeJMP((BYTE *)0xAA55ED, (DWORD)Skyboxes::HandleTimeOfDayReflections, 5);
    }
}