#include "Shape.h"
#include "Material.h"
#include <iostream>

Shape::Shape(){
    matter_ = Material() ;
    miroir_ = false ;
}

Shape::Shape (Material matter, bool miroir){
    matter_ = matter ;
    miroir_ = miroir ;
}

std::ostream & operator << (std::ostream & st, const Shape & s) {
    st << "Shape :" << "[ " << s.get_matter() << ", "<< s.get_miroir() <<" ]";
    return st ;
}