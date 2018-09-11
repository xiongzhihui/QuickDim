#ifndef AECMODELER_INC_EPSILON_H
#define AECMODELER_INC_EPSILON_H

AECMODELER_NAMESPACE_BEGIN

class Interval3d;

inline double epsAbs    () { return 1e-6;     }
inline double epsAbsSqrd() { return 1e-6; }

inline double epsNor    () { return 1e-6;     }
inline double epsNorSqrd() { return 1e-6; }

AECMODELER_NAMESPACE_END
#endif
