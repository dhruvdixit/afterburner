#include "QA.h"
class TProfile;
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<TProfile*>+;
#pragma link C++ class vector<TProfile*>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<TProfile*>::iterator;
#pragma link C++ operators vector<TProfile*>::const_iterator;
#pragma link C++ operators vector<TProfile*>::reverse_iterator;
#endif
#endif
