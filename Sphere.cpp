#include "Shape.h"
#include "Vector3f.h"
#include "Material.h"
#include "Sphere.h"
#include "Sdl.h"
#include <cmath>
#include <ostream>

Sphere::Sphere() {
    origin_ = Vector3f();
    radius_ = 0.;
}

Sphere::Sphere(Material matter, Vector3f origin, float radius, bool miroir) : Shape(matter,miroir){
    origin_ = origin;
    radius_ = radius;
}

Sphere::Sphere(const Shape &s, Vector3f origin, float radius) : Shape(s){
    origin_ = origin;
    radius_ = radius;
}

Sphere::Sphere(const Sphere &s) : Shape(s) {
    origin_ = s.get_origin();
    radius_ = s.get_radius();
}

int Sphere::is_hit (Ray3f ray, Vector3f * P, Vector3f * N, float * t) {

    // On résout le polynôme de second degré qui représente l'intersection
    // entre un rayon et une sphère

    Vector3f oc = ray.get_centre() - origin_ ;

	// float a = dot(ray.get_direction(),ray.get_direction()) ;
    float a = 1 ; // car ray.get_direction() unitaire
	float b = 2.0 * dot(ray.get_direction(),oc) ;
	float c = dot(oc,oc) - radius_ * radius_ ;

    // Calcul du discriminant
	float discriminant = b*b - 4 * a * c;

    // Si discriminant négatif, pas de solution réelle, donc pas de solution
    if (discriminant < 0.0f){
        return 0 ;
    }
    // Si discriminant positif, solution réelle
    float t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    float t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    // Si t2 négatif (donc t1 aussi), intersection derrière
    if (t2 < 0.0f){
        return 0 ;
    }
    // Intersection ok,
    // On récupère aussi la normale à la sphère et le point d'intersection
    // Le plus proche -> utile au modèle d'éclairage lamberien
    else {
        if (t1 > 0.0f){
            *t = t1 ;
        }
        else {
            *t = t2 ;
        }

        *P = ray.get_centre() + *t*ray.get_direction() ;
        *N = (*P - origin_) ;
        N->normalize() ;

        return 1 ;
    }
}

std::ostream & operator << (std::ostream & st, const Sphere & s) {
    st << "Sphere : [ origin : " << s.get_origin() << ", radius : " << s.get_radius() << " ]";
    return st ;
}
