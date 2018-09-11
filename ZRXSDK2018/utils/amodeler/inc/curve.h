#ifndef ZMODELER_INC_CURVE_H
#define ZMODELER_INC_CURVE_H

#include "entity.h"
#include "circle3d.h"
#include "transf3d.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp Curve : public Entity
{
public:
    Curve(Body* = NULL);

    // We support these curve types
    //
    enum Type { kUnspecified, kCircle };

    virtual Type     type     () const = NULL;
    virtual Curve*   copy     () const = NULL;
    virtual bool     transform(const Transf3d&,
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull) = NULL;

    virtual void     print    (FILE* = NULL)         const = NULL;
    virtual void     save     (SaveRestoreCallback*) const;
    virtual void     restore  (SaveRestoreCallback*)       {}

    Curve*           next     () const     { return mpNext; }
    void             setNext  (Curve* c)   { mpNext = c;    }

    // Scratch data members
    //
    Curve* cptr;
    int    n;     // For print

private:

    Curve* mpNext;   // Next curve in the list of all curves of a body

}; // class Curve



class DllImpExp UnspecifiedCurve : public Curve
{
public:

    UnspecifiedCurve(Body* b = NULL) : Curve(b) {}
    
    virtual Type     type     () const { return kUnspecified; }
    virtual Curve*   copy     () const { return new UnspecifiedCurve(*this); }
    virtual void     print    (FILE* = NULL) const;

    virtual bool     transform(const Transf3d&,
                               Transf3d::Type  /*transfType*/  = Transf3d::kUnknown,
                               const Vector3d& /*stretchVect*/ = Vector3d::kNull) 
    { return true; }

}; // class UnspecifiedCurve



class DllImpExp CircleCurve : public Curve
{
public:

    CircleCurve() {}
    CircleCurve(const Circle3d&, int approx, Body*); 

    // Return circle definiton data
    //
    const Transf3d&  transf   () const { return mTransf;          }
    Point3d          origin   () const { return mTransf.origin(); }
    Line3d           axis     () const;  
    double           radius   () const { return mRadius; }
    int              approx   () const { return mApprox; }
    Circle3d         circle   () const { return Circle3d(axis(), mRadius); }

    virtual Type     type     () const { return kCircle; }
    virtual Curve*   copy     () const { return new CircleCurve(*this); }

    virtual bool     transform(const Transf3d&, 
                               Transf3d::Type  transfType  = Transf3d::kUnknown,
                               const Vector3d& stretchVect = Vector3d::kNull);

    virtual void     print    (FILE* = NULL)          const;
    virtual void     save     (SaveRestoreCallback*)  const;
    virtual void     restore  (SaveRestoreCallback*);

private:

    Transf3d mTransf;
    double   mRadius;
    int      mApprox;

}; // class CircleCurve



AECMODELER_NAMESPACE_END
#endif
