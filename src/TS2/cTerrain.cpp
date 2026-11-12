#include "TS2/cTerrain.h"
#include "TS2/base.h"
#include "TS2/cTSSGSystem.h"
#include "TS2/cWaterGeometryBuilder.h"

namespace nTSSG
{
    void cTerrain::SetWaterElevation(UINT x, UINT y, float elevation)
    {
        UINT minX = *reinterpret_cast<UINT *>(this + 0x7C);
        UINT minY = *reinterpret_cast<UINT *>(this + 0x80);
        UINT maxX = *reinterpret_cast<UINT *>(this + 0x84);
        UINT maxY = *reinterpret_cast<UINT *>(this + 0x88);

        if (minX <= x && minY <= y && x <= maxX && y <= maxY)
        {
            cWaterGeometryBuilder *waterGeomBuilder =
                *reinterpret_cast<cWaterGeometryBuilder **>(this + 0x50);

            waterGeomBuilder->SetWaterElevation(x, y, elevation);

            cTSSGSystem *system = *reinterpret_cast<cTSSGSystem **>(0x1478F10);
            cFloorManager *floorMgr = system->FloorManager();

            if (floorMgr)
            {
                cFloor *floor = floorMgr->Floor(0);

                if (floor)
                    ConfigureReflectionCamera(floor);
            }
        }
    }
}