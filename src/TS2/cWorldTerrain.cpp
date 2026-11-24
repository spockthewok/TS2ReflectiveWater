#include "TS2/cWorldTerrain.h"
#include "common.h"

namespace nTSWorld
{
    float cWorldTerrain::WaterElevation(UINT x, UINT y)
    {
        using Func = float(__thiscall *)(cWorldTerrain *, UINT, UINT);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x30);
        return vFunc(this, x, y);
    }

    bool cWorldTerrain::IsPondVertex(UINT x, UINT y)
    {
        using Func = bool(__thiscall *)(cWorldTerrain *, UINT, UINT);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x38);
        return vFunc(this, x, y);
    }
}