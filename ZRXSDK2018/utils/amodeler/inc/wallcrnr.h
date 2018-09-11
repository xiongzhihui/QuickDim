#ifndef AECMODELER_INC_WALLCRNR_H
#define AECMODELER_INC_WALLCRNR_H

#include "global.h"

AECMODELER_NAMESPACE_BEGIN


DllImpExp Body createWallCornerBody(
                    const Point2d& pt1,     // Start of wall 1
                    const Point2d& pt2,     // End of wall 1, start of wall 2
                    const Point2d& pt3,     // End of wall 2
                    bool           materialToTheLeft,
                    double         width1,  // Wall 1 width
                    double         width2,  // Wall 2 width
                    double         height,  // Wall height
                    Color          matingFacesColor,
                    Plane&         matingPlane1,
                    Plane&         matingPlane2,
                    bool&          wall1NeedsToBeSectioned,
                    bool&          wall2NeedsToBeSectioned);

AECMODELER_NAMESPACE_END
#endif

