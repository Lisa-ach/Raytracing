#include "Material.h"
#include <iostream>

Material::Material (){
    r_ = 0.0f ;
    g_ = 0.0f ;
    b_ = 0.0f ;
    shininess_ = 0.0f ;
}

Material::Material (float r, float g, float b, float shininess){
    r_ = r ;
    g_ = g ;
    b_ = b ;
    shininess_ = shininess ;
}

Material::Material (const Material & m){
    r_ = m.get_r() ;
    g_ = m.get_g() ;
    b_ = m.get_b() ;
    shininess_ = m.get_shininess() ;
}

Material & Material::operator= (const Material & m) {
    if (this != & m){
        r_ = m.get_r() ;
        g_ = m.get_g() ;
        b_ = m.get_b() ;
        shininess_ = m.get_shininess() ;
    }
    return *this ;
}

Material & Material::operator+= (const Material & m){
    *this= Material(r_ + m.get_r(), g_ + m.get_g(), b_ + m.get_b(), shininess_ + m.get_shininess()) ;
    return *this ;
}

Material & Material::operator-= (const Material & m){
    *this= Material(r_ - m.get_r(), g_ - m.get_g(), b_ - m.get_b(), shininess_ - m.get_shininess()) ;
    return *this ;
}

Material & Material::operator*= (const Material & m){
    *this= Material(r_ * m.get_r(), g_ * m.get_g(), b_ * m.get_b(), shininess_ * m.get_shininess()) ;
    return *this ;
}

Material & Material::operator/= (const Material & m){
    *this= Material(r_ / m.get_r(), g_ / m.get_g(), b_ / m.get_b(), shininess_ / m.get_shininess()) ;
    return *this ;
}

Material & Material::operator/=(const float v){
    float reciprocal_v = 1.0f / v ;
    *this = Material(r_ * reciprocal_v, g_ * reciprocal_v, b_ * reciprocal_v, shininess_);
    return *this ;
}

Material operator* (const Vector3f & v, const Material & m) {
    return(Material(v.get_x() * m.get_r(),v.get_y() * m.get_g(),v.get_z() * m.get_b(),0.0f)) ;
}

Material operator* (const Material & m,const Vector3f & v) {
    return(Material(v.get_x() * m.get_r(),v.get_y() * m.get_g(),v.get_z() * m.get_b(),0.0f)) ;
}

Material operator/ (const Material & m, const float v) {
    float reciprocal_v = 1.0f / v ;
    return Material(m.get_r() * reciprocal_v, m.get_g() * reciprocal_v, m.get_b() * reciprocal_v, m.get_shininess());
}

std::ostream & operator<< (std::ostream & st, const Material & m) {
    st << "RGB : "  << "(" << m.get_r() << "," << m.get_g() << "," << m.get_b() << ") ; " << "Shininess : " << m.get_shininess() ;
    return st ;
}