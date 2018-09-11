#ifndef AECMODELER_INC_POINT3D_H
#define AECMODELER_INC_POINT3D_H

#include "vector3d.h"
#include "ipoint3d.h"
#include "point2d.h"

class ZcGePoint3d;

AECMODELER_NAMESPACE_BEGIN


class DllImpExp Point3d
{
public:

    Point3d() {}  // Note: No default constructor
    Point3d(double xx, double yy, double zz) : x(xx), y(yy), z(zz)       {}
    //Point3d(IntPoint3d ip)                   : x(ip.x), y(ip.y), z(ip.z) {}
    //Point3d(Point2d     p)                   : x(p.x), y(p.y), z(0)      {}

    Point3d  operator  +(Point3d  p) const { return Point3d (x+p.x, y+p.y, z+p.z); }
    Point3d  operator  +(Vector3d v) const { return Point3d (x+v.x, y+v.y, z+v.z); }
    Vector3d operator  -(Point3d  p) const { return Vector3d(x-p.x, y-p.y, z-p.z); }
    Point3d  operator  -(Vector3d v) const { return Point3d (x-v.x, y-v.y, z-v.z); }
    Point3d  operator  -()           const { return Point3d(-x, -y, -z);           }

    Point3d  operator  *(double scalar) const { return Point3d(x*scalar, y*scalar, z*scalar); }
    Point3d  operator  /(double scalar) const { return Point3d(x/scalar, y/scalar, z/scalar); }

    double   operator  %(Vector3d v) const { return x*v.x+y*v.y+z*v.z; }
    
    double   operator [](int index) const { return (&x)[index]; }
    double&  operator [](int index)       { return (&x)[index]; }

    double   length     ()          const { return sqrt(x*x+y*y+z*z);       }
    double   lengthSqrd ()          const { return x*x+y*y+z*z;             }
    double   lengthRect ()          const { return fabs(x)+fabs(y)+fabs(z); }

    double   dist       (Point3d p) const { return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)+(z-p.z)*(z-p.z)); }
    double   distSqrd   (Point3d p) const { return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)+(z-p.z)*(z-p.z);       }
    double   distRect   (Point3d p) const { return fabs(x-p.x)+fabs(y-p.y)+fabs(z-p.z);    }

    bool     isEqual    (Point3d p, double epsSqrd = epsAbsSqrd()) const { return (distSqrd(p) <= epsSqrd); }
    bool     isEqualRect(Point3d p, double epsRect = epsAbs    ()) const { return (distRect(p) <= epsRect); }

    void     operator +=(Point3d     p) { x += p.x; y += p.y; z += p.z; }
    //void     operator +=(Vector3d    v) { x += v.x; y += v.y; z += v.z; }
    void     operator -=(Point3d     p) { x -= p.x; y -= p.y; z -= p.z; }
    //void     operator -=(Vector3d    v) { x -= v.x; y -= v.y; z -= v.z; }
    void     operator *=(double scalar) { x *= scalar; y *= scalar; z *= scalar; }
    void     operator /=(double scalar) { x /= scalar; y /= scalar; z /= scalar; }
        
    //void     operator *=(const Transf3d&);
    
    //Point3d  project    (const Transf3d&) const;

    // Returns true iff this point (that is assumed to lie on the line defined
    // by the two points p1, p2) is between the two given points or is 
    // coincident with one of the points
    //
    bool     isBetween  (const Point3d& p1, const Point3d& p2) const;

    bool     isValid    () const { return fabs(x) < kMaxReal && fabs(y) < kMaxReal && fabs(z) < kMaxReal; }

    //Point2d  toPoint2d  ()               const { return *((Point2d*)this);                 }
    //Point2d  toPoint2d  (int i1, int i2) const { return Point2d((*this)[i1], (*this)[i2]); }
    //Point2d  toPoint2d  (int dropCoord ) const; 
   // Vector3d toVector3d ()               const { return *(Vector3d*)this;                  }

    // Casts from ZMODELER::Point3d to ZcGePoint3d
    //
    operator       ZcGePoint3d& ()       { return *((ZcGePoint3d*)this);       }
    operator const ZcGePoint3d& () const { return *((const ZcGePoint3d*)this); }

    // Cast from l-value ZcGePoint3d to l-value ZMODELER::Point3d. This 
    // explicit cast function needs to be used only for l-values, e.g. when 
    // ZMODELER returns a Point3d as an output argument but we want to capture 
    // it in an ZcGePoint3d. For non-l-values, the Point3d(const ZcGePoint3d&) 
    // constructor will perform the cast automatically.
    //
    static Point3d& cast(ZcGePoint3d& p) { return *(Point3d*)&p; }
    
    Point3d(const ZcGePoint3d& p)        { *this = *(Point3d*)&p; }

    // Public data members
    //
    double x, y, z;

    static const Point3d kNull;

}; // class Point3d

inline Point3d operator *(double scalar, Point3d p) 
{ 
    return Point3d(scalar*p.x, scalar*p.y, scalar*p.z); 
}



inline double det(Point3d a, Point3d b, Point3d c)
{
    return (a.x * (b.y*c.z - b.z*c.y) +
            a.y * (b.z*c.x - b.x*c.z) +
            a.z * (b.x*c.y - b.y*c.x));
} 




//DllImpExp bool areCoplanar(Point3d, Point3d, Point3d, Point3d);


AECMODELER_NAMESPACE_END
#endif
