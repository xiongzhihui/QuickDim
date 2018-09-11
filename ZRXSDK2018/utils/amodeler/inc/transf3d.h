#ifndef AECMODELER_INC_TRANSF3D_H
#define AECMODELER_INC_TRANSF3D_H

#include "point3d.h"

class ZcGeMatrix3d;

AECMODELER_NAMESPACE_BEGIN

class DllImpExp Transf3d
{
public:

    // The constructor creates an identity transform.
    //
    Transf3d();  

    // The constructor creates a rigid motion transform from an origin and 
    // directions of x, y and z axes.
    //
    Transf3d(const Point3d&  origin, 
             const Vector3d& xDir, 
             const Vector3d& yDir, 
             const Vector3d& zDir);

    // The constructor creates a rigid motion transform from an origin and 
    // direction of x and y axis. If yDir is not perpendicular to xDir, yDir
    // will be adjusted.
    //
    Transf3d(const Point3d&  origin, 
             const Vector3d& xDir, 
             const Vector3d& yDir);

    // The constructor creates a rigid motion transform from an origin 
    // (axis.point) and the direction of the z axis (axis.vector). The 
    // directions of the x and y axes are determined according to the 
    // AutoCAD's arbitrary axis algorithm.
    //
    Transf3d(const Line3d& axis);

    // The constructor creates a rigid motion transform from an origin. The
    // x, y and z axis are aligned with the world x, y and z axis.
    //
    Transf3d(const Point3d& origin);

    double& operator ()(int i1, int i2)       { return c[i1][i2]; }
    double  operator ()(int i1, int i2) const { return c[i1][i2]; }

    // Transform points, vectors and other transforms
    //
    Point3d  operator *(const Point3d& ) const;
    Vector3d operator *(const Vector3d&) const;
    Line3d   operator *(const Line3d&  ) const;
    Transf3d operator *(const Transf3d&) const;

    void     getCoordSystem(Point3d&  origin,
                            Vector3d& xDir,
                            Vector3d& yDir,
                            Vector3d& zDir) const;

    Point3d  origin() const;
    Vector3d xDir  () const;
    Vector3d yDir  () const;
    Vector3d zDir  () const;
    
    // Create special transformations
    //
    static Transf3d translation(const Vector3d&);
    static Transf3d rotation   (const Line3d& axis, double angle);
    static Transf3d scaling    (const Point3d& fixedPt, double factor);
    static Transf3d scaling    (const Point3d& fixedPt, const Vector3d& xyzFactors);
    static Transf3d stretching (const Line3d& axis);
    //static Transf3d mirroring  (const Plane&);
    //static Transf3d projectOn  (const Plane& projPlane, const Vector3d& projDir = Vector3d::kNull);

    // The transformation maps points as follows:
    //
    // Point  src1             maps to point  dst1
    // Vector (src1,src2)      maps to vector (dst1,dst2)
    // Plane  (src1,src2,src3) maps to plane  (dst1,dst2,dst3)
    //
    static Transf3d align(const Point3d& src1,
                          const Point3d& src2,
                          const Point3d& src3,
                          const Point3d& dst1,
                          const Point3d& dst2,
                          const Point3d& dst3);

    // The transformation maps points and vectors as follows:
    //
    // Point  src1             maps to point  dst1
    // Vector src2             maps to vector dst2
    // Plane  (src1,src2,src3) maps to plane  (dst1,dst2,dst3)
    //
    static Transf3d align(const Point3d&  src1,
                          const Vector3d& src2,
                          const Vector3d& src3,
                          const Point3d&  dst1,
                          const Vector3d& dst2,
                          const Vector3d& dst3);

    static Transf3d align(const Point3d&  src1,
                          const Vector3d& src2,
                          const Point3d&  dst1,
                          const Vector3d& dst2);

    // Project a point, using the full 4x4 matrix, including the projective
    // part. Sets Transf3d::succeeded to false if the point couldn't be projected
    // by the perspective transform because it lied behind the view point.
    //
    Point3d project(const Point3d& p) const;

    enum ProjectionType { kParallelProjection, kPerspectiveProjection };

    // Create a general projection transformation (this is how to create
    // a projection transformation to be passed to the Body::hideDisplay() 
    // method).
    //
    Transf3d(ProjectionType  type, 
             const Point3d&  fromPt, 
             const Point3d&  toPt   = Point3d (0,0,0), 
             const Vector3d& upDir  = Vector3d(0,0,0));

    // Some ready to use projection transformations 
    //
    static const Transf3d kFrontView;
    static const Transf3d kBackView;
    static const Transf3d kTopView;
    static const Transf3d kBottomView;
    static const Transf3d kLeftView;
    static const Transf3d kRightView;
    static const Transf3d kIsometricView;
    static const Transf3d kDimetricView;

    Transf3d invert(bool isRigidMotion = true) const;

    bool     isValid                 () const;
    bool     isOrthogonal            () const;  // No shear
    bool     isEqualScalingOrthogonal() const;  // No shear, no nonequal scaling
    Vector3d stretchVector           () const;
    bool     isMirror                () const;
    bool     isPerspective           () const;
    bool     isIdentity              () const;

    static const Transf3d kIdentity;

    // Casts from AModeler::Transf3d to ZcGeMatrix3d
    //
    operator       ZcGeMatrix3d& ()       { return *((ZcGeMatrix3d*)this);       }
    operator const ZcGeMatrix3d& () const { return *((const ZcGeMatrix3d*)this); }

    // Cast from l-value ZcGeMatrix3d to l-value AModeler::Transf3d. This 
    // explicit cast function needs to be used only for l-values, e.g. when 
    // AModeler returns a Transf3d as an output argument but we want to capture 
    // it in an ZcGeMatrix3d. For non-l-values, the Transf3d(const ZcGeMatrix3d&) 
    // constructor will perform the cast automatically.
    //
    static Transf3d& cast(ZcGeMatrix3d& m) { return *(Transf3d*)&m; }

    Transf3d(const ZcGeMatrix3d& m)        { *this = *(Transf3d*)&m; }


    //void save   (SaveRestoreCallback*) const;
    //void restore(SaveRestoreCallback*);

    // Public data member
    //
    double c[4][4];

    enum Type { kRigidMotion, kEqualScalingOrtho, kNonOrtho, kProjection, kUnknown };

}; // class Transf3d



// Transform a distance by a transform. Notice that if the transform
// contains non-uniform scaling, this operation does not make sense
//
DllImpExp void operator *=(double& dist, const Transf3d&);  

inline Transf3d::Transf3d() 
{
    c[0][1] = c[0][2] = c[0][3] = c[1][0] = c[1][2] = c[1][3] = 
    c[2][0] = c[2][1] = c[2][3] = c[3][0] = c[3][1] = c[3][2] = 0.0;
    c[0][0] = c[1][1] = c[2][2] = c[3][3] = 1;
}


AECMODELER_NAMESPACE_END
#endif

