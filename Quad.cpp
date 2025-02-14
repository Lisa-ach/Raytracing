#include "Shape.h"
#include "Vector3f.h"
#include "Material.h"
#include "Quad.h"
#include <cmath>
#include <ostream>
#include <math.h>

Quad::Quad() {
    origin_ = Vector3f();
    width_ = Vector3f();
    height_ = Vector3f();
}

Quad::Quad(Material matter, Vector3f origin, Vector3f width, Vector3f height, bool miroir) : Shape(matter,miroir){
    origin_ = origin;
    width_ = width;
    height_ = height;
}

Quad::Quad(const Shape &s, Vector3f origin, Vector3f width, Vector3f height) : Shape(s){
    origin_ = origin;
    width_ = width;
    height_ = height;
}

Quad::Quad(const Quad &q) : Shape(q) {
    origin_ = q.get_origin();
    width_ = q.get_width();
    height_ = q.get_height();
}

std::ostream & operator << (std::ostream & st, const Quad & q) {
    st << "Quad : [ origin : " << q.get_origin() << ", width : " << q.get_width() << ", height : " << q.get_height() << " ]";
    return st ;
}

Vector3f Quad::boundMax() const {
    return origin_;
}

Vector3f Quad::boundMin() const {
    Vector3f res(origin_+height_+width_);
    Vector3f tmp(0.0,0.0,width_.get_x());
    res+=tmp;
    return res;
}

Vector3f Quad::get_center() const {
    Vector3f res(origin_);
    Vector3f tmp(width_.get_x()/2, height_.get_y()/2, width_.get_x()/2);
    res+=tmp;
    return res;
}

//Trouve la normale d'un point de la boite
Vector3f Quad::normal(const Vector3f P) const {
    Vector3f b0 = boundMin();
    Vector3f b1 = boundMax();
    Vector3f center = this-> get_center();

    //On initialise les paramètres que l'on va comparer

    float Px = P.get_x();
    float Py = P.get_y();
    float Pz = P.get_z();

    float B0x = b0.get_x();
    float B0y = b0.get_y();
    float B0z = b0.get_z();

    float B1x = b1.get_x();
    float B1y = b1.get_y();
    float B1z = b1.get_z();

    //On regarde alors les intersections avec les faces
    // Intersection avec la face avant
	if (Px > center.get_x() && (Px == B0x || Px == B1x)) {
		// Intersection avec les arêtes haute et basse
		if ((Py == B0y || Py == B1y) && (Pz != B0z && Pz != B1z) && Pz != center.get_z()) {
			return Vector3f(1, 1, 0) * P;
		}
		// Intersection avec les arêtes de droite et de gauche
		else if ((Py == B0z || Py == B1y) && (Pz != B0z && Pz != B1z) && Pz != center.get_z()) {
			return Vector3f(1, 0, 1) * P;
		}
		// Intersection avec les coins
		else if ((Py == B1y && Pz == B1z) || (Pz == B0z && Py == B1y) || (Pz == B1z && Py == B0y) || (Pz == B0z && Py == B0y)) {
			return Vector3f(1, 1, 1) * P;
		}
		// Intersection au milieu de la face
		else { return Vector3f(1, 0, 0) * P; }
	}
	// Intersection avec la face arrière
    else if (Px < center.get_x() && (Px == B0x || Px == B1x)) {
        // Intersection avec les arêtes 
        if ((Pz == B0z || Pz == B1z) && (Py != B0y && Py != B1y) && Py != center.get_y()) {
            return Vector3f(1, 0, 1) * P;
        }
        // Intersection avec les coins
        else if ((Px == B1x && Py == B1y) || (Px == B0x && Py == B1y) || (Px == B1x && Py == B0y) || (Px == B0x && Py == B0y)) {
            return Vector3f(1, 1, 1) * P;
        }
        // Intersection au milieu de la face
        else {
            return Vector3f(-1, 0, 0) * P;
        }
    }
	// Intersection avec la face gauche
    else if (Pz > center.get_z() && (Pz == B0z || Pz == B1z)) {
        // Intersection avec les arêtes haute et basse
        if ((Py == B0y || Py == B1y) && (Px != B0x && Px != B1x) && Py != center.get_y()) {
            return Vector3f(0, 1, 1) * P;
        }
        // Intersection avec les arêtes de droite et de gauche
        else if ((Px == B0x || Px == B1x) && (Py != B0y && Py != B1y) && Px != center.get_x()) {
            return Vector3f(1, 0, 1) * P;
        }
        // Intersection au milieu de la face
        else {
            return Vector3f(0, 0, 1) * P;
        }
    }

	// Intersection avec la face droite
    else if (Pz < center.get_z() && (Pz == B0z || Pz == B1z)) {
        // Intersection avec les arêtes haute et basse
        if ((Py == B0y || Py == B1y) && (Px != B0x && Px != B1x) && Py != center.get_y()) {
            return Vector3f(1, 1, 0) * P;
        }
        // Intersection avec les arêtes de droite et de gauche
        else if ((Px == B0x || Px == B1x) && (Py != B0y && Py != B1y) && Px != center.get_x()) {
            return Vector3f(1, 0, 1) * P;
        }
        // Intersection au milieu de la face
        else {
            return Vector3f(0, 0, -1) * P;
        }
    }

	// Intersection avec la face haute
    else if (Py > center.get_y() && (Py == B0y || Py == B1y)) {
        // Intersection avec les arêtes haute et basse
        if ((Px == B0x || Px == B1x) && (Pz != B0z && Pz != B1z) && Px != center.get_x()) {
            return Vector3f(1, 1, 0) * P;
        }
        // Intersection avec les arêtes de droite et de gauche
        else if ((Pz == B0z || Pz == B1z) && (Px != B0x && Px != B1x) && Pz != center.get_z()) {
            return Vector3f(0, 1, 1) * P;
        }
        // Intersection au milieu de la face
        else {
            return Vector3f(0, 1, 0) * P;
        }
    }

	// Intersection avec la face basse
    else if (Py < center.get_y() && (Py == B0y || Py == B1y)) {
        // Intersection avec les arêtes haute et basse
        if ((Px == B0x || Px == B1x) && (Pz != B0z && Pz != B1z) && Px != center.get_x()) {
            return Vector3f(1, 1, 0) * P;
        }
        // Intersection avec les arêtes de droite et de gauche
        else if ((Pz == B0z || Pz == B1z) && (Px != B0x && Px != B1x) && Pz != center.get_z()) {
            return Vector3f(1, 0, 1) * P;
        }
        // Intersection au milieu de la face
        else {
            return Vector3f(0, -1, 0) * P;
        }
    }

    return Vector3f();
}

int Quad::is_hit (Ray3f ray, Vector3f * P, Vector3f * N, float * t)
{ 
    Vector3f orig = ray.get_centre();
    Vector3f dir = ray.get_direction();

    //On récupère les points min (coin arrière inférieur droit) et max (coin avant supérieur gauche) du quad 
    Vector3f b0 = boundMin();
    Vector3f b1 = boundMax();

    float tx1, ty1, tz1, tx2, ty2, tz2;

    //On calcule les points d'intersections possibles 
    tx1 = (b0.get_x() - orig.get_x()) / dir.get_x();
    ty1 = (b0.get_y() - orig.get_y()) / dir.get_y();
    tz1 = (b0.get_z() - orig.get_z()) / dir.get_z();

    tx2 = (b1.get_x() - orig.get_x()) / dir.get_x();
    ty2 = (b1.get_y() - orig.get_y()) / dir.get_y();
    tz2 = (b1.get_z() - orig.get_z()) / dir.get_z();

    //On détermine les points le plus proche et le plus loin
    float tNear = std::max(std::min(tx1, tx2), std::max(std::min(ty1, ty2), std::min(tz1, tz2)));
    float tFar = std::min(std::max(tx1, tx2), std::min(std::max(ty1, ty2), std::max(tz1, tz2)));

    //Si une des conditions suivantes est respectée, il n'y a pas d'intersection
    if (tNear > tFar || tFar < 0) {
        return 0;
    }

    *t = tNear;

    *P = orig + *t*dir;
    //On détermine la normale, qui est unitaire dans le cas d'un quadrilatère

    *N = normal(*P);

    N->normalize();

    return 1;
}
