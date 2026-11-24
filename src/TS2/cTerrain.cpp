#include "TS2/cTerrain.h"
#include "TS2/base.h"
#include "TS2/cTSSGSystem.h"
#include "TS2/cWorldDB.h"
#include "TS2/cWorldTerrain.h"
#include "TS2/cWaterGeometryBuilder.h"

namespace nTSSG
{
    void cTerrain::SetWaterElevation(UINT x, UINT y, float elevation)
    {
        UINT minX = *reinterpret_cast<UINT *>(this + 0x7C);
        UINT minY = *reinterpret_cast<UINT *>(this + 0x80);
        UINT maxX = *reinterpret_cast<UINT *>(this + 0x84);
        UINT maxY = *reinterpret_cast<UINT *>(this + 0x88);

        if (x < minX || y < minY || x > maxX || y > maxY)
            return;

        cWaterGeometryBuilder *waterGeom = *reinterpret_cast<cWaterGeometryBuilder **>(this + 0x50);
        waterGeom->SetWaterElevation(x, y, elevation);

        nTSWorld::cWorldDB *worldDB = *reinterpret_cast<nTSWorld::cWorldDB **>(0x1479BE4);
        nTSWorld::cWorldTerrain *worldTerrain =
            *reinterpret_cast<nTSWorld::cWorldTerrain **>(worldDB + 0x58);

        // This method seems to get called for each vertex modified by the terrain tool
        // Unnecessary to repeatledly reconfigure reflection camera for non-pond verts
        if (!worldTerrain->IsPondVertex(x, y))
            return;

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