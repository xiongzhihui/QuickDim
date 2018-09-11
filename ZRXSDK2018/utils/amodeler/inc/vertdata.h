#ifndef AECMODELER_INC_VERTDATA_H
#define AECMODELER_INC_VERTDATA_H

#include "circle3d.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp PolygonVertexData
{
public:

    enum Type { kArc3d, kArcByRadius, kArcByBulge, kFilletByRadius, kUnspecifiedCurve };

    PolygonVertexData(Type);                                         // kUnspecifiedCurve
    PolygonVertexData(Type, const Circle3d&, int apprx);             // kArc3d
    PolygonVertexData(Type, double rad, bool isCenLeft, int apprx);  // kArcByRadius
    PolygonVertexData(Type, double bulgeOrRadius, int apprx);        // kArcByBulge or kFilletByRadius

    bool isArc() const 
    { 
        return type == kArc3d || type == kArcByRadius || type == kArcByBulge || type == kFilletByRadius; 
    }

public: // data

    Type     type;
    Circle3d circle;
    int      approx;
    bool     isCenterLeft;
    double   bulge;
    Curve*   curve;
    Surface* surface;

}; // class PolygonVertexData



// Deletes the VertexData objects the vertexDataArray points to and sets the
// pointers to NULL. If alsoDeleteArray is true, it also deletes the array,
// otherwise it does not
//
DllImpExp void deleteVertexData(PolygonVertexData* vertexDataArray[], int arrayLength, bool alsoDeleteArray);


AECMODELER_NAMESPACE_END
#endif
