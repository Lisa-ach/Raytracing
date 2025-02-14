#include "Ray3f.h"
#include "Vector3f.h"

Ray3f::Ray3f() {
    centre_ = Vector3f() ;
    direction_ = Vector3f() ;
}
        
Ray3f::Ray3f (Vector3f centre, Vector3f direction){
    centre_ = centre ;
    direction_ = direction ;
}

std::ostream & operator << (std::ostream & st, const Ray3f & r) {
    st << "Centre :  " << r.get_centre() << ", direction : " << r.get_direction();
    return st;
}
