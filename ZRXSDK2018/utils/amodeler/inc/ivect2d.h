#ifndef AECMODELER_INC_IVEC2D_H
#define AECMODELER_INC_IVEC2D_H

#include "global.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp IntVector2d
{
public:

    // Note: No default constructor
    IntVector2d(int xx, int yy) : x(xx), y(yy) {}

    IntVector2d operator  +(IntVector2d v) const { return IntVector2d(x+v.x, y+v.y); }
    IntVector2d operator  -(IntVector2d v) const { return IntVector2d(x-v.x, y-v.y); }

    int         operator [](int index)     const { return (&x)[index]; }
    int&        operator [](int index)           { return (&x)[index]; }

    bool        operator ==(IntVector2d v) const { return x == v.x && y == v.y; }
    bool        operator !=(IntVector2d v) const { return !(*this == v); }

    void        operator +=(IntVector2d v)       { x += v.x; y += v.y; }
    void        operator -=(IntVector2d v)       { x -= v.x; y -= v.y; }
        
    // Public data members
    //
    int x, y;

};  // Class IntVector2d


AECMODELER_NAMESPACE_END
#endif
