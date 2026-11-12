#pragma once

namespace nTSWorld
{
    class cWorldDB
    {
    public:
        bool IsWaterVertex(int *cVertex);
        float WaterElevation(int x, int y);
        float MinX();
        float MinY();
        float MaxX();
        float MaxY();
    };
}