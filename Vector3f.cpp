#include "Vector3f.h"
#include <iostream>

Vector3f::Vector3f (){
    x_ = 0.0f ;
    y_ = 0.0f ;
    z_ = 0.0f ;
}

Vector3f::Vector3f (float x, float y, float z){
    x_ = x ;
    y_ = y ;
    z_ = z ;
}

Vector3f::Vector3f (float x){
    x_ = x ;
    y_ = x ;
    z_ = x ;
}

Vector3f::Vector3f (const Vector3f & v){
    x_ = v.get_x() ;
    y_ = v.get_y() ;
    z_ = v.get_z() ;
}

Vector3f & Vector3f::operator= (const Vector3f & v) {
    if (this != & v){
        x_ = v.get_x() ;
        y_ = v.get_y() ;
        z_ = v.get_z() ;
    }
    return *this ;
}

Vector3f & Vector3f::operator+= (const Vector3f & v){
    *this= Vector3f(x_ + v.get_x(), y_ + v.get_y(), z_ + v.get_z()) ;
    return *this ;
}

Vector3f & Vector3f::operator-= (const Vector3f & v){
    *this= Vector3f(x_ - v.get_x(), y_ - v.get_y(), z_ - v.get_z()) ;
    return *this ;
}

Vector3f & Vector3f::operator*= (const Vector3f & v){
    *this= Vector3f(x_ * v.get_x(), y_ * v.get_y(), z_ * v.get_z()) ;
    return *this ;
}

float Vector3f::dot (const Vector3f & v){
    return (x_ * v.get_x() + y_ * v.get_y() + z_ * v.get_z()) ;
}

Vector3f & Vector3f::operator/= (const Vector3f & v){
    *this= Vector3f(x_ / v.get_x(), y_ / v.get_y(), z_ / v.get_z()) ;
    return *this ;
}

void Vector3f::normalize() {
    float longu = longueur();
    if (longu != 0.0f) {
        x_ /= longu;
        y_ /= longu;
        z_ /= longu;
    }
}

Vector3f Vector3f::get_normalised(){
    Vector3f v(x_,y_,z_) ;
    float longu = v.longueur();
    if (longu != 0.0f) {
        v.set_x(v.get_x()/ longu);
        v.set_y(v.get_y()/ longu);
        v.set_z(v.get_z()/ longu);
    }
    return v ;
}

bool operator== (const Vector3f & v1, const Vector3f & v2) {
    return (v1.get_x() == v2.get_x() && v1.get_y() == v2.get_y() && v1.get_z() == v2.get_z());
}

Vector3f operator+ (const Vector3f & v1, const Vector3f & v2) {
    Vector3f v(v1) ;
    v+=v2 ;
    return v ;
}

Vector3f operator- (const Vector3f & v1, const Vector3f & v2) {
    Vector3f v(v1) ;
    v-=v2 ;
    return v ; 
}

Vector3f operator* (const Vector3f & v1, const Vector3f & v2) {
    Vector3f v(v1) ;
    v*=v2 ;
    return v ; 
}

Vector3f operator* (const float v1, const Vector3f & v2) {
    return (Vector3f (v1) * v2) ;
}

Vector3f operator/ (const Vector3f & v1, const Vector3f & v2) {
    Vector3f v(v1) ;
    v/=v2 ;
    return v ; 
}

float dot (const Vector3f & v1, const Vector3f & v2){
    return (v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y() + v1.get_z() * v2.get_z()) ;
}

Vector3f cross (const Vector3f & v1, const Vector3f & v2){
    return (Vector3f(v1.get_y() * v2.get_z() - v1.get_z() * v2.get_y(), 
    v1.get_z() * v2.get_x() - v1.get_x() * v2.get_z(),
    v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x())) ;
}

std::ostream & operator<< (std::ostream & st, const Vector3f & v) {
    st << "(" << v.get_x() << "," << v.get_y() << "," << v.get_z() << ")" ;
    return st ;
}


