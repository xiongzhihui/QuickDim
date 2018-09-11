#ifndef AECMODELER_INC_VERTEX_H
#define AECMODELER_INC_VERTEX_H


#include "entity.h"
#include "point3d.h"

AECMODELER_NAMESPACE_BEGIN

// Global vertex flags
//
const Flag PICKVF         = FLAG(0);  // Pickable Vertex Flag (for vertex picking)
const Flag NONMANIFOLD_VF = FLAG(1);


class DllImpExp Vertex : public Entity
{
public:
    Vertex() : mpNext(NULL) {}
    Vertex(const Point3d&, Body*);
    ~Vertex();

    const Point3d& point     () const           { return mPoint; }
    Vertex*        next      () const           { return mpNext; }

    void           setPoint  (const Point3d& p) { mPoint  = p;   }
    void           setNext   (Vertex* v)        { mpNext  = v;   }
    void           transform (const Transf3d&); 
    void           modified  ();
    void               deleteVertexSurfaceData (){};

    void           print     (FILE* = NULL)         const;        // Not for public use
    void           save      (SaveRestoreCallback* pCallBack) const;        // Not for public use
    void           restore   (SaveRestoreCallback* pCallBack, int version); // Not for public use

    // Scratch data members (unioned to save space)
    //
    union
    {
        Vertex* vptr;
        int     n;
    };
    union
    {
        Edge*   eptr;
        Vertex* vptr1;
    };

private:

    Point3d            mPoint;            
    Vertex*            mpNext; 

}; // class Vertex


// Inlines (do not look beyond this point)

inline Vertex::~Vertex()
{
    deleteVertexSurfaceData();
}


AECMODELER_NAMESPACE_END
#endif
