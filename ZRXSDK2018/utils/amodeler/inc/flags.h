#ifndef AECMODELER_INC_FLAGS_H
#define AECMODELER_INC_FLAGS_H

AECMODELER_NAMESPACE_BEGIN


typedef unsigned Flag;


Flag inline FLAG(unsigned int i) { return (1 << i); }


// Flag set 'a' is subset of flag set 'b'
//
inline int isSubset(Flag a, Flag b) { return ((a & b) == a); }


enum OnOff { kOff, kOn };


AECMODELER_NAMESPACE_END
#endif

