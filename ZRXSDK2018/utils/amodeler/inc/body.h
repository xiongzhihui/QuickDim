#ifndef AECMODELER_INC_BODY_H
#define AECMODELER_INC_BODY_H

#pragma warning(push)
#pragma warning(disable : 4702) // unreachable code
#include <vector>
#pragma warning(pop)
#include "entity.h"
#include "transf3d.h"
#include "color.h"
#include "morphmap.h"
#include "enums.h"
#include "global.h"

AECMODELER_NAMESPACE_BEGIN

const Flag IPBF   = FLAG(0);  // Interval Present            Body Flag  
const Flag NEGBF  = FLAG(1);  // Negative                    Body Flag
const Flag DASHBF = FLAG(2);  // Display DASHed        lines Body Flag
const Flag WFBF   = FLAG(3);  // Display Wireframe           Body Flag
const Flag DAEBF  = FLAG(4);  // Display Approximating Edges Body Flag
const Flag DBEBF  = FLAG(5);  // Display Bridge        Edges Body Flag


class DllImpExp Body : public Entity
{
public:
    Body();
    Body(const Body&);
    ~Body();
    Body& operator =(const Body &);
    Body copy() const;
    void init(bool  deleteContents);
    bool isValid(int validityCheckingLevel = -1) const;
    Body boolOper(Body&, BoolOperType eType, bool  hideZeroSlopeEdges = true, TopologyChangeCallback* pCallBack = NULL, bool  keepInputBodiesWhenFails = keepInputBodiesWhenBooleanOperationsFail());
    Body operator + (const Body& );
    Body  operator - (const Body& );
    Body  operator * (const Body& );
    Body& operator +=(const Body& );
    Body& operator -=(const Body& );
    Body& operator *=(const Body& ); 
    Body& transform(const Transf3d&);
    Body operator -();
    static Body box (const Point3d& corner, const Vector3d& sizes);
    static Body sphere (const Point3d& center, double radius, int approx);
    static Body cylinder(const Line3d&axis, double radius, int approx);
    static Body cylinder(const Line3d&axis, const Vector3d& baseNormal,double radius, int approx);
    static Body cone(const Line3d&axis, double radius1, double radius2, int approx);
    static Body cone(const Line3d&axis, const Vector3d& baseNormal, double radius1, double radius2, int approx);
    static Body torus(const Line3d&axis, double majorRadius, double minorRadius, int majorApprox, int minorApprox);
    static Body pipe(const Line3d&axis, double outerRadius, double innerRadius, int approx);
    static Body pipe(const Line3d&axis, const Vector3d& baseNormal, double outerRadius, double innerRadius, int approx);
    static Body pipeConic(const Line3d&axis, double outerRadius1, double innerRadius1, double outerRadius2, double innerRadius2, int approx);
    static Body pipeConic(const Line3d&axis, const Vector3d& baseNormal, double outerRadius1, double innerRadius1, double outerRadius2, double innerRadius2, int approx);
    static Body tetrahedron (const Point3d& p1, const Point3d& p2, const Point3d& p3, const Point3d& p4);
    static Body reducingElbow(const Point3d& elbowCenter, const Point3d& endCenter1, const Point3d& endCenter2, double endRadius1, double endRadius2, int majorApprox, int minorApprox);
    static Body rectangleToCircleReducer(const Point3d& baseCorner, const Vector2d& baseSizes,const Circle3d& topCircle,int approx);
    static Body convexHull(const Point3d pts[], int numPoints);
    static Body extrusion (const Point3d plg[], PolygonVertexData* vertexData[],int numVertices,const Vector3d&plgNormal,const Vector3d&extrusionVector,const Point3d& scaleTwistFixedPt,double scaleFactor,double twistAngle = 0.0);
    static Body extrusion (const Point3d plg[], PolygonVertexData* vertexData[],int numVertices,const Vector3d&plgNormal,const Vector3d&extrusionVector);
    static Body extrusion (const Point3d plg[], PolygonVertexData* vertexData[],int numVertices,const Vector3d&plgNormal,const Vector3d&extrusionVector,const std::vector<void*>*attribs);
    static Body pyramid(const Point3d plg[], PolygonVertexData* vertexData[], int numVertices, const Vector3d&plgNormal,const Point3d& pyramidApex);
    static Body axisRevolution(const Point3d plg[], PolygonVertexData* vertexData[], int numVertices, const Vector3d& plgNormal, const Line3d& axis, double revolutionAngle, int approx, const Point3d& scaleTwistFixedPt, double scaleFactor, double twistAngle = 0.0);
    static Body axisRevolution(const Point3d plg[], PolygonVertexData* vertexData[], int numVertices, const Vector3d& plgNormal, const Line3d& axis, double revolutionAngle, int approx);
    static Body endpointRevolution(const Point3d plg[], PolygonVertexData* vertexData[], int numVertices, const Vector3d& plgNormal, double revolutionAngle, int approx);
    
    static Body extrusionAlongPath(const Body& startProfile,const Body& endProfile,const Point3d pathPlg[], PolygonVertexData* pathVertexData[],int pathNumVertices,bool pathIsClosed,bool checkBodyValidity = true, const Point3d& scaleTwistFixedPt = Point3d::kNull, double scaleFactor= 1.0, double twistAngle= 0.0,const MorphingMap& morphingMap= MorphingMap::kNull,bool calcluateMorphingMapAutomatically = false,std::vector<int>startProfileSignificantVertices= std::vector<int>(), std::vector<int>endProfileSignificantVertices = std::vector<int>());
    static Body skin (Body* profiles[], int numProfiles, bool isClosed,bool checkPlanarity,MorphingMap** morphingMaps = NULL,bool markInnerProfileEdgesAsApprox = false,bool ckeckInputProfiles= true);
    void hideDisplay(const Transf3d&projectionTransf,OutputPolylineCallback*,bool  = true, HiddenLineDrawingImprove = kNoDrawingImprove, HideIntegerTransform* = NULL);
    void setHiddenLineParams(HiddenLinesDisplay hiddenLinesDisplay = kHiddenLinesInvisible, bool displayApproxEdges = false, bool displayBridgeEdges = false);
    void triangulate(OutputTriangleCallback* pCallBack, TriangulationType type = kGenerateTriangles,bool  cacheTriangles= true) const;
    void save(SaveRestoreCallback* pCallBack) const;
    void save(FILE*)const;
    void save(const wchar_t* fileName) const;
    static Body restore(SaveRestoreCallback* pCallBack);
    static Body restore(FILE*);
    static Body restore(const wchar_t* fileName);
    bool  isNull() const;
    Vertex* vertexList() const;

    // Save to ACIS SAT text file. If colorsAlso is true, every face and edge 
    // receives a color-adesk-attrib
    //
    //void        saveToSat(SaveToSatCallback*,   bool colorsAlso = false) const;
    void        saveToSat(FILE*,                bool colorsAlso = false) const;
    void        saveToSat(const wchar_t* fileName, bool colorsAlso = false) const;

    void     setFaceList      (Face*    f) { mpFaceList    = f;    }
//     void     setSurfaceList   (Surface* s) { mpSurfaceList = s;    }
//     void     setCurveList     (Curve*   c) { mpCurveList   = c;    }
    void     setVertexList    (Vertex*  v) { mpVertexList  = v;    }

    Face*    faceList         () const     { return mpFaceList;    }
//     Surface* surfaceList      () const     { return mpSurfaceList; }
//     Curve*   curveList        () const     { return mpCurveList;   }

    void     addFace          (Face*   );
    void     addSurface       (Surface*);
    void     addCurve         (Curve*  );
    void     addVertex        (Vertex* );


    int      vertexCount  () const;
    int      edgeCount    () const;  
    int      faceCount    () const;
    int      surfaceCount () const;
    int      curveCount   () const;
    int      triangleCount() const;

    void triangulateAllFaces();

private:
    
    Face*      mpFaceList;     // Linear list of all faces
    //Surface*   mpSurfaceList;  // Linear list of all surfaces
    //Curve*     mpCurveList;    // Linear list of all curves
    Vertex*    mpVertexList;   // Linear list of all vertices
    Body*      mpNext;         // Next body, currently used only by hideDisplay()

    //Interval3d mInterval;      // Enclosing interval of the body

    TriangleCache* mpTriangleCache; 

};  // class Body

AECMODELER_NAMESPACE_END
#endif

