#ifndef AECMODELER_INC_CALLBACK_H
#define AECMODELER_INC_CALLBACK_H

#include "global.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp OutputPolylineCallback
{
public:

    virtual ~OutputPolylineCallback() {}

    virtual void outputPolyline(Edge*          edgeArray [],
                                const Point3d  pointArray[],
                                const double   bulgeArray[],
                                int            numPoints,
                                bool           isClosed,
                                bool           isVisible) = NULL;

    virtual void outputArc     (Edge*          edge,
                                const Point3d& center,
                                double         radius,
                                double         startAngle,
                                double         endAngle,
                                bool           isVisible) = NULL;

}; // class OutputPolylineCallback



class DllImpExp OutputTriangleCallback
{
public:

    virtual ~OutputTriangleCallback() {}

    virtual void outputTriangle(Edge* edgeArray[], int arrayLength) = NULL;

    enum { kMaxTriStripLength = 200 };

    virtual void outputTriStrip(Edge* edgeArray[], 
                                int   arrayLength,
                                bool  firstTriangleIsCcw) = NULL;

}; // class OutputTriangleCallback



class DllImpExp SaveRestoreCallback
{
public:

    virtual ~SaveRestoreCallback() {}

    virtual void saveBytes   (const void* buffer, int requiredLength) = NULL;
    virtual void restoreBytes(void*       buffer, int requiredLength) = NULL;

}; // class SaveRestoreCallback


class DllImpExp TopologyChangeCallback
{
public:

    virtual ~TopologyChangeCallback() {}
};

AECMODELER_NAMESPACE_END
#endif

