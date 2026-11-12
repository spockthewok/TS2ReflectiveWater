#include "TS2/cWaterGeometryBuilder.h"

namespace nTSSG
{
    void cWaterGeometryBuilder::SetWaterElevation(UINT x, UINT y, float elevation)
    {
        using SetWaterElevationFn = void(__thiscall *)(cWaterGeometryBuilder *, UINT, UINT, float);
        SetWaterElevationFn Func = reinterpret_cast<SetWaterElevationFn>(0xB7C130);
        Func(this, x, y, elevation);
    }
}