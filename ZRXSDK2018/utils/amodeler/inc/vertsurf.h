#ifndef AECMODELER_INC_VERTSURF_H
#define AECMODELER_INC_VERTSURF_H

#include "entity.h"
#include "vector3d.h"

AECMODELER_NAMESPACE_BEGIN


class DllImpExp VertexSurfaceData : public Entity
{
public:
    VertexSurfaceData() : mpSurface(NULL), mpNext(NULL), mNormal(0,0,0) {}

    VertexSurfaceData(const Edge*);

    Surface*           surface() const                  { return mpSurface; }
    VertexSurfaceData* next   () const                  { return mpNext;    }
    const Vector3d&    normal () const                  { return mNormal;   }

    void               setNext   (VertexSurfaceData* pVsd) { mpNext = pVsd; }
    void               setSurface(Surface*           s)    { mpSurface = s; }
    void               transform (const Transf3d&    t)    { mNormal  *= t; }


    void            print     (FILE* = NULL)         const; // Not for public use
    void            save      (SaveRestoreCallback*) const; // Not for public use
    void            restore   (SaveRestoreCallback*);       // Not for public use

private:

    Surface*           mpSurface; 
    VertexSurfaceData* mpNext;  
    Vector3d           mNormal;  // Direction of the surface normal at the vertex
//  Point2d            mParamPoint;

}; // class VertexSurfaceData


AECMODELER_NAMESPACE_END
#endif
