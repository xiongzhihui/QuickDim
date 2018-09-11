#ifndef AECMODELER_INC_SURFACE_H
#define AECMODELER_INC_SURFACE_H

#include "entity.h"
#include "circle3d.h"
#include "transf3d.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp Surface : public Entity
{
public:

    Surface(Body* = NULL);
    
    // We support only these surface types
    //
    enum Type { kUnspecified, kCylinder, kCone, kSphere, kTorus };

    virtual Type     type     () const = NULL;
    virtual Surface* copy     () const = NULL;

    // The transform() method returns true if the surface was successfully 
    // transformed or false if it could not be transformed (e.g. a sphere 
    // cannot be stretched)
    //
    virtual bool     transform(const Transf3d&,
                               Transf3d::Type  /*transfType*/  = Transf3d::kUnknown,
                               const Vector3d& /*stretchVect*/ = Vector3d::kNull) = NULL;

    // Returns true if two surfaces are equal. The definition of what equal 
    // means is highly questionable
    //
    virtual bool     isEqual  (const Surface*) const = NULL;

    virtual bool containsPoint(const Point3d&) const = NULL;

    // The circle() method returns the equation of a circle which results from 
    // the intersection of the surface with the given plane. The Line3d is used 
    // to disambiguate between multiple intersections (e.g. torus-plane 
    // intersection produces two circles). The Line3d is an approximation of 
    // the circle we are interested in
    //
    virtual Circle3d circle   (const Plane&, const Line3d&) const = NULL;

    // The normal() method returns the outward-pointing unit normal vector to
    // the surface at the given point
    //
    virtual Vector3d normal   (const Point3d&) const = NULL;

    virtual void     print    (FILE* = NULL) const   = NULL;
    virtual void     save     (SaveRestoreCallback*) const;
    virtual void     restore  (SaveRestoreCallback*) {}

    Surface*         next     () const     { return mpNext; }
    void             setNext  (Surface* s) { mpNext = s;    }

    // Scratch data members
    //
    Surface* sptr;
    int      n;     // For print

private:

    Surface* mpNext;   // Next surface in the list of all surfaces of a body

}; // class Surface



class DllImpExp UnspecifiedSurface : public Surface
{
public:

    UnspecifiedSurface(Body* b = NULL) : Surface(b) {}
    
    virtual Type     type     () const { return kUnspecified; }
    virtual Surface* copy     () const { return new UnspecifiedSurface(*this); }
    virtual void     print    (FILE* = NULL) const;

    virtual bool     transform(const Transf3d&,
                               Transf3d::Type  /*transfType*/  = Transf3d::kUnknown,
                               const Vector3d& /*stretchVect*/ = Vector3d::kNull) 
    { return true; }

    virtual bool     isEqual  (const Surface* s) const; // return this == s;

    virtual bool containsPoint(const Point3d&) const { return false; }

    virtual Circle3d circle   (const Plane&, const Line3d&) const { return Circle3d();      }
    virtual Vector3d normal   (const Point3d&)              const { return Vector3d(0,0,0); }

}; // class UnspecifiedSurface



class DllImpExp RevolutionSurface : public Surface
{
public:

    RevolutionSurface();
    RevolutionSurface(const Line3d& axis, const Vector3d& startDir, Body* = NULL);

    // The axis of the revolution and the direction of the beginning of the
    // revolution (the 0.0-parameter). The two vectors are orthogonal and unit
    // length
    //
    Line3d           axis     () const { return mAxis;     } 
    Vector3d         startDir () const { return mStartDir; }

    virtual bool     transform(const Transf3d&,
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull);

    virtual bool     isEqual  (const Surface*) const;

    virtual void     save     (SaveRestoreCallback*) const;
    virtual void     restore  (SaveRestoreCallback*);

private:

    Line3d   mAxis;
    Vector3d mStartDir;

}; // class RevolutionSurface



class DllImpExp SphereSurface : public RevolutionSurface
{
public:

    SphereSurface() {}
    SphereSurface(const Point3d& origin, double radius, int approx, Body*); 

    // Return the sphere definiton data
    //
    Point3d          center   () const { return axis().point; }
    double           radius   () const { return mRadius;      }
    int              approx   () const { return mApprox;      }

    virtual Type     type     () const { return kSphere; }
    virtual Surface* copy     () const { return new SphereSurface(*this); }

    virtual bool     transform(const Transf3d&, 
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull);

    virtual bool     isEqual  (const Surface*) const;

    virtual bool containsPoint(const Point3d&) const; 

    virtual Circle3d circle   (const Plane&, const Line3d&) const;
    virtual Vector3d normal   (const Point3d&)              const;

    virtual void     print    (FILE* = NULL)          const;
    virtual void     save     (SaveRestoreCallback*)  const;
    virtual void     restore  (SaveRestoreCallback*);

private:

    double  mRadius;
    int     mApprox;

}; // class SphereSurface



class DllImpExp CylinderSurface : public RevolutionSurface
{
public:

    CylinderSurface() {}
    CylinderSurface(const Line3d& axis, double radius, int approx, Body*);
    CylinderSurface(const Line3d& axis, const Vector3d& startDir, double radius, int approx, Body*);

    // Return the cylinder definition data
    //
    double           radius   () const { return mRadius;  }
    int              approx   () const { return mApprox;  }

    virtual Type     type     () const { return kCylinder; }
    virtual Surface* copy     () const { return new CylinderSurface(*this); }

    virtual bool     transform(const Transf3d&, 
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull);

    virtual bool     isEqual  (const Surface*) const;

    virtual bool containsPoint(const Point3d&) const; 

    virtual Circle3d circle   (const Plane&, const Line3d&) const;
    virtual Vector3d normal   (const Point3d&)              const;

    virtual void     print    (FILE* = NULL)          const;
    virtual void     save     (SaveRestoreCallback*)  const;
    virtual void     restore  (SaveRestoreCallback*);

private:

    double mRadius;
    int    mApprox;

}; // class CylinderSurface



class DllImpExp ConeSurface : public RevolutionSurface
{
public:

    ConeSurface() {}
    ConeSurface(const Line3d& axis, double radius1, double radius2, int approx, Body*);

    // Return the cone definition data
    //
    double           radius   () const { return mRadius;   }
    double           tanAngle () const { return mTanAngle; }
    int              approx   () const { return mApprox;   }
    Point3d          apex     () const;

    virtual Type     type     () const { return kCone; }
    virtual Surface* copy     () const { return new ConeSurface(*this); }

    virtual bool     transform(const Transf3d&, 
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull);

    virtual bool     isEqual  (const Surface*) const;

    virtual bool containsPoint(const Point3d&) const; 

    virtual Circle3d circle   (const Plane&, const Line3d&) const;
    virtual Vector3d normal   (const Point3d&)              const;

    virtual void     print    (FILE* = NULL)          const;
    virtual void     save     (SaveRestoreCallback*)  const;
    virtual void     restore  (SaveRestoreCallback*);

private:

    double mRadius;
    double mTanAngle;
    int    mApprox;

}; // class ConeSurface



class DllImpExp TorusSurface : public RevolutionSurface
{
public:
    TorusSurface() {}
    TorusSurface(const Line3d& axis, 
                 double        majRadius, 
                 double        minRadius, 
                 int           majApprox, 
                 int           minApprox, 
                 Body*         b);

    // Return the torus definition data
    //
    Point3d          center     () const { return axis().point; }
    double           majorRadius() const { return mMajorRadius; }
    double           minorRadius() const { return mMinorRadius; }
    int              majorApprox() const { return mMajorApprox; }
    int              minorApprox() const { return mMinorApprox; }

    virtual Type     type       () const { return kTorus;   }
    virtual Surface* copy       () const { return new TorusSurface(*this); }

    virtual bool     transform  (const Transf3d&, 
                                 Transf3d::Type  transfType  = Transf3d::kUnknown,
                                 const Vector3d& stretchVect = Vector3d::kNull);

    virtual bool     isEqual    (const Surface*) const;

    virtual bool containsPoint(const Point3d&) const; 

    virtual Circle3d circle     (const Plane&, const Line3d&) const;
    virtual Vector3d normal     (const Point3d&)              const;

    virtual void     print      (FILE* = NULL)          const;
    virtual void     save       (SaveRestoreCallback*)  const;
    virtual void     restore    (SaveRestoreCallback*);

private:

    double mMajorRadius;
    double mMinorRadius;
    int    mMajorApprox;
    int    mMinorApprox;

}; // class TorusSurface


AECMODELER_NAMESPACE_END
#endif
