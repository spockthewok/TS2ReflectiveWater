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
            Ocean::EnhanceOceanReflections();

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
            Skyboxes::FixSkyboxReflections();

        // Neighbourhood
        if (Config::betterNHoodReflections)
            Hooking::MakeJMP((0x6DA9A0 + Module::base), (DWORD)Hood::EnableHoodFullSceneReflections, 5);

        // Ponds
        if (Config::pondReflections)
            Ponds::EnablePondReflections();
    }

    void Init()
    {
        Module::base = reinterpret_cast<DWORD>(GetModuleHandleA(NULL));

        Config::Init();
        InjectPatches();
    }
}