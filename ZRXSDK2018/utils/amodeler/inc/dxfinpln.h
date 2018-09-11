#ifndef AECMODELER_INC_DXFINPLN_H
#define AECMODELER_INC_DXFINPLN_H

#include "global.h"

AECMODELER_NAMESPACE_BEGIN


DllImpExp void dxfPolylineToAugmentedPolygon(FILE*                pInputDxfFile,
                                             int                  approx,
                                             Point3d*&            plg,
                                             PolygonVertexData**& vertexData,
                                             int&                 numVertices,
                                             Vector3d&            plgNormal);

AECMODELER_NAMESPACE_END
#endif

