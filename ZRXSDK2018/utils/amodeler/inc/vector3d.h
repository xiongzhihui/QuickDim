#ifndef AECMODELER_INC_VECTOR3D_H
#define AECMODELER_INC_VECTOR3D_H

#include <math.h>
#include "vector2d.h"
class ZcGeVector3d;

AECMODELER_NAMESPACE_BEGIN


class DllImpExp Vector3d
{
public:

    Vector3d() {} // Note: No default constructor
    Vector3d(double xx, double yy, double zz) : x(xx),   y(yy),   z(zz)   {}
    //Vector3d(Vector2d     v)                  : x(v.x),  y(v.y),  z(0)    {}
    //Vector3d(IntVector3d iv)                  : x(iv.x), y(iv.y), z(iv.z) {}

    Vector3d operator + (Vector3d v)    const { return Vector3d(x+v.x, y+v.y, z+v.z); }
    Vector3d operator - (Vector3d v)    const { return Vector3d(x-v.x, y-v.y, z-v.z); }
    double   operator % (Vector3d v)    const { return x*v.x+y*v.y+z*v.z;             }
    Vector3d operator * (Vector3d v)    const; // Cross product
    Vector3d operator - ()              const { return Vector3d(-x, -y, -z);          }

    Vector3d operator * (double scalar) const { return Vector3d(x*scalar, y*scalar, z*scalar); }
    Vector3d operator / (double scalar) const { return Vector3d(x/scalar, y/scalar, z/scalar); }

    double   operator [](int index)     const { return (&x)[index]; }
    double&  operator [](int index)           { return (&x)[index]; }

    double   length     ()              const { return sqrt(x*x+y*y+z*z);       }
    double   lengthSqrd ()              const { return x*x+y*y+z*z;             }
    double   lengthRect ()              const { return fabs(x)+fabs(y)+fabs(z); }

    Vector3d normalize  () const;

    double   dist       (Vector3d v)    const { return (*this-v).length();     }
    double   distSqrd   (Vector3d v)    const { return (*this-v).lengthSqrd(); }
    double   distRect   (Vector3d v)    const { return (*this-v).lengthRect(); }

    bool     isEqual    (Vector3d v, double epsSqrd = epsNorSqrd()) const { return (distSqrd(v) <= epsSqrd); }
    bool     isEqualRect(Vector3d v, double epsRect = epsNor()    ) const { return (distRect(v) <= epsRect); }

    double   angle      (const Vector3d&) const;

    void     operator +=(Vector3d    v) { x += v.x; y += v.y; z += v.z; }
    void     operator -=(Vector3d    v) { x -= v.x; y -= v.y; z -= v.z; }
    void     operator *=(double scalar) { x *= scalar; y *= scalar; z *= scalar; }
    void     operator /=(double scalar) { x /= scalar; y /= scalar; z /= scalar; }

    Vector3d perpend() const;

    void     operator *=(const Transf3d&);

    bool     isNull     (double epsSqrd = epsNorSqrd()) const { return lengthSqrd() <= epsSqrd; }
    bool     isParallel (const Vector3d&, double epsNorSqrd = epsNorSqrd()) const;
    bool     isParallelNorm(const Vector3d&, double epsNorSqrd = epsNorSqrd()) const; // For normalized vectors
    bool     isPerpend  (const Vector3d&, double epsNor = epsNor()) const;
    bool     isExactNull() const { return x == 0 && y == 0 && z == 0; }

    void     orthoPlane (int& i1, int& i2)          const;
    void     orthoPlane (int& i1, int& i2, int& i3) const;

    int      dominantDirection() const;

    //const Vector2d& toVector2d ()               const { return *((Vector2d*)this);             }
    //Vector2d        toVector2d (int i1, int i2) const { return Vector2d((*this)[i1], (*this)[i2]); }
    //Vector2d        toVector2d (int dropCoord ) const; 

    // Casts from ZModeler::Vector3d to ZcGeVector3d
    //
    operator       ZcGeVector3d& ()       { return *((ZcGeVector3d*)this);       }
    operator const ZcGeVector3d& () const { return *((const ZcGeVector3d*)this); }

    // Cast from l-value ZcGeVector3d to l-value ZModeler::Vector3d. This 
    // explicit cast function needs to be used only for l-values, e.g. when 
    // ZModeler returns a Vector3d but we want to capture it in an ZcGeVector3d.
    // For non-l-values, the Vector3d(const ZcGeVector3d&) constructor will 
    // perform the cast automatically.
    //
    static Vector3d& cast(ZcGeVector3d& v) { return *(Vector3d*)&v; }

    Vector3d(const ZcGeVector3d& v)        { *this = *(Vector3d*)&v; }

    static Vector3d random();
    
    // Public data members
    //
    double x, y, z;

    static const Vector3d kNull;
    static const Vector3d kXDir;
    static const Vector3d kYDir;
    static const Vector3d kZDir;

}; // class Vector3d


inline Vector3d operator *(double scalar, Vector3d v) 
{ 
    return Vector3d(scalar*v.x, scalar*v.y, scalar*v.z); 
}



inline Vector3d Vector3d::operator *(Vector3d v) const
{
    return Vector3d(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

inline double det(Vector3d a, Vector3d b, Vector3d c)
{
    return (a.x * (b.y*c.z - b.z*c.y) +
            a.y * (b.z*c.x - b.x*c.z) +
            a.z * (b.x*c.y - b.y*c.x));
} 

AECMODELER_NAMESPACE_END
#endif
