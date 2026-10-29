#pragma once

namespace Config
{
    extern bool oceanReflections;
    extern float oceanReflectionOffset;
    extern bool treeReflections;
    extern bool bridgeReflections;
    extern bool wallReflections;
    extern bool floorReflections;
    extern bool ceilingReflections;
    extern bool poolTerrainReflections;
    extern bool lotTerrainReflections;
    extern bool fixSkyboxReflections;
    extern bool betterNHoodReflections;
    extern bool pondReflections;

    void Init();
}