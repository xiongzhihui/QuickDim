#ifndef AECMODELER_INC_DXFOUT_H
#define AECMODELER_INC_DXFOUT_H
#include "callback.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp OutputToDxfFileCallback : public OutputPolylineCallback, 
                                          public OutputTriangleCallback
{
public:

    // The constructor opens the DXF file and writes the SECTION ENTITIES header
    //
    OutputToDxfFileCallback(const wchar_t* dxfFileName);

    // The destructor writes the ENDSEC and EOF groups and closes the file
    //
    ~OutputToDxfFileCallback();

    virtual void outputPolyline(Edge*             edgeArray [],
                                const Point3d     pointArray[], 
                                const double      bulgeArray[],
                                int               numPoints, 
                                bool              isClosed, 
                                bool              isVisible); 

    virtual void outputArc     (Edge*          edge,
                                const Point3d& center,
                                double         radius,
                                double         startAngle,
                                double         endAngle,
                                bool           isVisible);

    virtual void outputTriangle(Edge* edgeArray[], int arrayLength);

    virtual void outputTriStrip(Edge* edgeArray[], int arrayLength, 
                                bool firstTriangleIsCcw);

private:

    FILE* mpFile;

    // Write group code and group value
    //
    void g(int code, const char*    value) const;
    void g(int code, int            value) const;
    void g(int code, double         value) const;
    void g(int code, const Point2d& value) const;
    void g(int code, const Point3d& value) const;

}; // class OutputToDxfFileCallback



// Print the triangle to stdout
//
DllImpExp extern void printTriangle(Edge* edgeArray[], int numSides); 


AECMODELER_NAMESPACE_END
#endif

