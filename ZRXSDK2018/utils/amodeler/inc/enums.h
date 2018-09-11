#ifndef AECMODELER_INC_ENUMS_H
#define AECMODELER_INC_ENUMS_H

AECMODELER_NAMESPACE_BEGIN

enum BoolOperType
{
    kBoolOperUnite,
    kBoolOperSubtract,
    kBoolOperIntersect
};

enum BodyInterferenceType
{
    kBodiesDoNotInterfere,
    kBodiesTouch,
    kBodiesInterfere
};

enum PointInBodyLocation
{
    kPointOutsideBody,
    kPointAtVertex,
    kPointOnEdge,
    kPointInFace,
    kPointInsideBody
};

enum HiddenLinesDisplay
{
    kHiddenLinesInvisible,
    kHiddenLinesDashed,
    kHiddenLinesVisible
};

enum HiddenLineDrawingImprove
{
    kNoDrawingImprove,
    kConnectDrawingImprove,
    kArcReconstructDrawingImprove
};

enum TriangulationType
{
    kGenerateTriangles,
    kGenerateQuadrilaterals,
    kGenerateTriStrips,
    kGenerateTriStripsPerSurface
};

enum RayBodyIntersection
{
    kRayDoesNotIntersect,
    kRayPointAtVertex,
    kRayPointOnEdge,
    kRayPointInFace,
    kRayIntersectsVertex,
    kRayIntersectsEdge,
    kRayIntersectsFace
};


AECMODELER_NAMESPACE_END
#endif

