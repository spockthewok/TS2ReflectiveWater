#pragma once
#include "headers.h"

namespace nTSWorld
{
    class cWorldTerrain
    {
    public:
        float WaterElevation(UINT x, UINT y);
        bool IsPondVertex(UINT x, UINT y);
    };
}