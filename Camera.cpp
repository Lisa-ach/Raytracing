#include "Camera.h"
#include "Vector3f.h"

Camera::Camera() {
    position_ = Vector3f() ;
    direction_ = Vector3f() ;
}
        
Camera::Camera (Vector3f position, Vector3f direction){
    position_ = position ;
    direction_ = direction ;
}

std::ostream & operator << (std::ostream & st, const Camera & r) {
    st << "Position :  " << r.get_position() << ", direction : " << r.get_direction();
    return st;
}