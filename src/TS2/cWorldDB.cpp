#include "TS2/cWorldDB.h"
#include "common.h"

namespace nTSWorld
{
    bool cWorldDB::IsWaterVertex(int *cVertex)
    {
        using Func = bool(__thiscall *)(cWorldDB *, int *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0xE0);
        return vFunc(this, cVertex);
    }

    // Calls cWorldTerrain::WaterElevation, which loads the water elevation value into ST(0)
    void cWorldDB::WaterElevation(int x, int y)
    {
        using Func = void(__thiscall *)(cWorldDB *, int, int);
        auto vFunc = Common::GetVTableFn<Func>(this, 0xFC);
        vFunc(this, x, y);
    }

    float cWorldDB::MinX()
    {
        using Func = float(__thiscall *)(cWorldDB *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x12C);
        return vFunc(this);
    }

    float cWorldDB::MinY()
    {
        using Func = float(__thiscall *)(cWorldDB *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x130);
        return vFunc(this);
    }

    float cWorldDB::MaxX()
    {
        using Func = float(__thiscall *)(cWorldDB *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x134);
        return vFunc(this);
    }

    float cWorldDB::MaxY()
    {
        using Func = float(__thiscall *)(cWorldDB *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x138);
        return vFunc(this);
    }
}