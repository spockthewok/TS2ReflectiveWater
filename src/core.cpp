#include "core.h"
#include "config.h"
#include "hooking.h"
#include "TS2/base.h"
#include "reflections/lots.h"
#include "reflections/ocean.h"
#include "reflections/props.h"
#include "reflections/skyboxes.h"
#include "reflections/terrain.h"
#include "reflections/hood.h"
#include "reflections/ponds.h"

namespace Core
{
    static void InjectPatches()
    {
        // Ocean
        if (Config::oceanReflections)
        {
            Ocean::ForceLotReflections();
            Hooking::MakeJMP((0x680989 + Module::base), (DWORD)Ocean::AdjustLotSkirtOffset, 6);
            Hooking::MakeJMP((0x6809D3 + Module::base), (DWORD)Ocean::EnableCastawayStyleReflections, 6);
        }

        // Props
        if (Config::treeReflections)
            Props::EnableTreeReflections();
        if (Config::bridgeReflections)
            Hooking::MakeJMP((0x6D508C + Module::base), (DWORD)Props::EnableBridgeReflections, 5);

        // Lots
        if (Config::wallReflections)
            Hooking::MakeJMP((0x6771C5 + Module::base), (DWORD)Lots::EnableWallReflections, 6);
        if (Config::floorReflections)
            Hooking::MakeJMP((0x6E562F + Module::base), (DWORD)Lots::EnableFloorReflections, 5);
        if (Config::ceilingReflections)
            Hooking::MakeJMP((0x6E59A2 + Module::base), (DWORD)Lots::EnableCeilingReflections, 5);

        // Terrain
        if (Config::poolTerrainReflections)
            Terrain::EnablePoolTerrainReflections();
        if (Config::lotTerrainReflections)
            Hooking::MakeJMP((0x6E1A61 + Module::base), (DWORD)Terrain::EnableLotTerrainReflections, 5);

        // Skyboxes
        if (Config::fixSkyboxReflections)
        {
            Hooking::MakeJMP((0x3F54D3 + Module::base), (DWORD)Skyboxes::UpdateWeatherReflections, 6);
            Hooking::MakeJMP((0x6A55ED + Module::base), (DWORD)Skyboxes::ReplaceEnvCubeSelection, 5);
        }

        // Neighbourhood
        if (Config::betterNHoodReflections)
            Hooking::MakeJMP((0x6DA9A0 + Module::base), (DWORD)Hood::EnableHoodFullSceneReflections, 5);

        // Ponds
        if (Config::pondReflections)
        {
            Hooking::MakeJMP((0x6E63CA + Module::base), (DWORD)Ponds::InitPondCamera, 5);
            Hooking::MakeJMP((0x6E4880 + Module::base), (DWORD)Ponds::DetachCameraOnShutdown, 6);
            Ponds::FixVisibilityFilter();
            Hooking::MakeJMP((0x7625DA + Module::base), (DWORD)Ponds::SetPlaneHeight, 6);
            Ponds::UpdateCameraOnElevationChange();
        }
    }

    void Init()
    {
        Module::base = reinterpret_cast<DWORD>(GetModuleHandleA(NULL));

        Config::Init();
        InjectPatches();
    }
}