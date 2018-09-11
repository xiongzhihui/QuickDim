#ifndef AECMODELER_INC_GLOBAL_H
#define AECMODELER_INC_GLOBAL_H

#ifdef AECMODELER_EXPORTS
#define DllImpExp __declspec(dllexport)
#else
#define DllImpExp __declspec(dllimport)
#endif


#define AECMODELER_NAMESPACE         AECModeler
#define AECMODELER_NAMESPACE_BEGIN   namespace AECModeler {
#define AECMODELER_NAMESPACE_END     }


#include <stdio.h>
#include <stdlib.h>
#include "errcodes.h"
#include "epsilon.h"
#include "float.h"
#include "flags.h"
#include "massert.h" 


AECMODELER_NAMESPACE_BEGIN

const double kPi = 3.14159265358979323846;      
const double kTwoPi = 6.28318530717958647692;    
const double kHalfPi = 1.57079632679489661923;
// 
const double kMaxReal = FLT_MAX ;  // A very big number, but not too big
const double kMinReal = FLT_MIN;
// DllImpExp extern const double kDeg2Rad;  // Degrees --> radians coefficient
const double kEpsZero = FLT_MIN;  // Really a very small value

//const int kTooBigInt = 10000000;    // Too big number of anything is 10 million


class Point2d;
class Vector2d;
class Point3d;
class Vector3d;
class IntPoint2d;
class IntVector2d;
class IntPoint3d;
class IntVector3d;
class Transf3d;
class Line3d;
class Circle3d;
class Plane;
class Interval1d;
class Interval2d;
class Interval3d;
class IntInterval1d;
class IntInterval2d;
class IntInterval3d;
class Entity;
class Body;
class Face;
class Edge;
class Vertex;
class Surface;
class CylinderSurface;
class ConeSurface;
class SphereSurface;
class TorusSurface;
class Curve;
class CircleCurve;
class PolygonVertexData;
class OutputPolylineCallback;
class OutputTriangleCallback;
class SaveRestoreCallback;
class TopologyChangeCallback;
class SaveToSatCallback;
class TriangleCache;
class Darray;
class MorphingMapElem;
class MorphingMap;
class VertexSurfaceData;
class HideIntegerTransform;


DllImpExp void setKeepInputBodiesWhenBooleanOperationsFail(bool yesNo);
DllImpExp bool keepInputBodiesWhenBooleanOperationsFail();

AECMODELER_NAMESPACE_END
#endif
