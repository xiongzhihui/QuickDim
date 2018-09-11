#ifndef AECMODELER_INC_EDGE_H
#define AECMODELER_INC_EDGE_H

#include "entity.h"
#include "color.h"
#include "circle3d.h"
#include "vertex.h"

AECMODELER_NAMESPACE_BEGIN


// Global edge flags
//
const Flag AEF    = FLAG(0);   // Approximating Edge Flag
const Flag BEF    = FLAG(1);   // Bridge        Edge Flag
const Flag PICKEF = FLAG(2);   // Pickable      Edge Flag (for edge picking)

const Flag IEF1    = FLAG(10);   // Internal usage1 Edge Flag
const Flag IEF2    = FLAG(11);   // Internal usage2 Edge Flag
const Flag IEF3    = FLAG(12);   // Internal usage2 Edge Flag

class DllImpExp Edge : public Entity
{
public:
    Edge();
    Edge(Vertex* pVertex, Face* pFace, Edge* prevEdge, Edge* partner, Curve* = NULL);
    
    Vertex* vertex        () const    { return mpVertex;  }
    Face*   face          () const    { return mpFace;    }
    Edge*   next          () const    { return mpNext;    }
    Edge*   prev          () const    { return mpPrev;    }
    Color   color         () const    { return mColor;    }
    Point3d point() const;



    void    setVertex     (Vertex* v) { mpVertex  = v;    }
    void    setFace       (Face*   f) { mpFace    = f;    }
    void    setNext       (Edge*   e) { mpNext    = e;    }
    void    setPrev       (Edge*   e) { mpPrev    = e;    }
    //void    setPartner    (Edge* par) { mpPartner = par;  }

    bool isBridge                   () const;
    bool isApprox                   () const;

    void save   (SaveRestoreCallback* pCallBack) const;  // Not for public use
    void restore(SaveRestoreCallback* pCallBack);        // Not for public use
private:
    Vertex*  mpVertex;
    Face*    mpFace;     // The owning face.
    Edge*    mpNext;     // The next edge in the loop of edges of a face.
    Edge*    mpPrev;     // The previous edge in the loop of edges of a face.
    Color    mColor;     // Edge color.

};  // class Edge

AECMODELER_NAMESPACE_END


#include "face.h"
AECMODELER_NAMESPACE_BEGIN


inline Edge::Edge() 
      : mpVertex(NULL),
        mpNext   (NULL), 
        mpPrev   (NULL), 
        mColor   (kColorInvisible)
{
}


inline Point3d Edge::point() const
{
    return mpVertex->point();
}


inline bool Edge::isBridge() const
{
    return isFlagOn(BEF);
}



inline bool Edge::isApprox() const
{
    return isFlagOn(AEF);
}

/*
inline void Edge::removePartner()
{
    Edge* e = this;

    do {
    } while ((e = e->partner())->partner() != this);

    e->setPartner(partner());
    setPartner(this);
}



inline void Edge::addAfter(Edge* prevEdge)
{
    MASSERT(prevEdge != NULL);

    setNext(prevEdge->next());
    setPrev(prevEdge);
    prevEdge->setNext(this);
    if (next() != NULL) {
        next()->setPrev(this);
    } else {
        FAIL;  // Not a cyclical loop of edges
    }
}


inline Vector3d Edge::unitVector() const 
{ 
    return (next()->point() - point()).normalize(); 
}



inline bool Edge::isManifold() const
{
    return partner()->partner() == this && partner() != this;
}



inline Plane Edge::plane() const
{
    return mpFace->plane();
}



inline Surface* Edge::surface() const
{
    return mpFace->surface();
}



inline Line3d Edge::line() const
{
    return Line3d(mpVertex->point(), vector());
}
*/

AECMODELER_NAMESPACE_END
#endif
