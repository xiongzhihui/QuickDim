#ifndef AECMODELER_INC_IPOINT2D_H
#define AECMODELER_INC_IPOINT2D_H

#include "ivect2d.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp IntPoint2d
{
public:

    IntPoint2d() {} // Note: No default constructor
    IntPoint2d(int xx, int yy) : x(xx), y(yy) {}

    IntPoint2d  operator  +(IntPoint2d  p) const { return IntPoint2d (x+p.x, y+p.y); }
    IntPoint2d  operator  +(IntVector2d v) const { return IntPoint2d (x+v.x, y+v.y); }
    IntVector2d operator  -(IntPoint2d  p) const { return IntVector2d(x-p.x, y-p.y); }
    IntPoint2d  operator  -(IntVector2d v) const { return IntPoint2d (x-v.x, y-v.y); }
    IntPoint2d  operator  -()              const { return IntPoint2d(-x, -y);        }

    int         operator [](int index)     const { return (&x)[index]; }
    int&        operator [](int index)           { return (&x)[index]; }

    bool        operator ==(IntPoint2d  p) const { return x == p.x && y == p.y; }
    bool        operator !=(IntPoint2d  p) const { return !(*this == p); }

    void        operator +=(IntPoint2d  p) { x += p.x; y += p.y; }
    void        operator +=(IntVector2d v) { x += v.x; y += v.y; }
    void        operator -=(IntPoint2d  p) { x -= p.x; y -= p.y; }
    void        operator -=(IntVector2d v) { x -= v.x; y -= v.y; }
        
    // Public data members
    //
    int x, y;

    static const IntPoint2d kNull;

};  // Class IntPoint2d


AECMODELER_NAMESPACE_END
#endif
