#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Vector3f.h"
#include "Material.h"
#include "Sdl.h"
#include "Ray3f.h"
#include <cmath>
#include <ostream>


/**
 * @brief La classe qui définit les sphères dans la scène
 * 
 * Elle hérite de la classe Shape
*/
class Sphere : public Shape{
    private :
        /**
         * @brief L'origine de la sphère
         * @see Vector3f
        */
        Vector3f origin_ ;
        /**
         * @brief Le rayon de la sphère
        */
        float radius_ ;
    public :

        /**
         * @brief Constructeur par défaut
         * 
         * Crée une instance de la classe Sphere avec origin_ comme la valeur par défaut de Vector3f et radius_ à 0
         * @see Vector3f
        */
        Sphere() ;
        /**
         * @brief Constructeur paramétré en prenant compte des attributs de la classe mère
         * 
         * Crée une instance de la classe Sphere en définissant les paramètres de la classe fille ainsi 
         * que ceux de la classe mère Shape
         * 
         * @param matter : le matériel de la classe mère Shape
         * @param origin : l'origine de la sphère
         * @param radius : rayon de la sphère
         * @param miroir : le booléen qui permet de déterminer si Shape est miroir ou non, par défaut
         * il est mis à false
         * 
         * @see Shape
        */
        Sphere (Material matter, Vector3f origin, float radius, bool miroir=false);
        /**
         * @brief Constructeur paramétré avec un Shape en entrée
         * 
         * Crée une instance de la classe Sphere en définissant les paramètres de la classe fille et en 
         * prenant la référence vers un Shape déjà instancié
         * 
         * @param s : référence vers un Shape
         * @param origin : l'origine de la sphère
         * @param radius : rayon de la sphère
         * 
         * @see Shape
        */
        Sphere (const Shape &s, Vector3f origin, float radius);
        /**
         * @brief Constructeur de copie
         * 
         * Crée une instance de Sphere en copiant les attributs de la sphère donné un entrée
         * 
         * @param s : une référence vers la sphère dont on veut faire la copie
         */
        Sphere (const Sphere &s); 

        /**
         * @brief Getter de l'attribut origin_
         * 
         * @return L'attribut origin_ de la classe
        */
        Vector3f get_origin() const {return origin_ ;} ;
        /**
         * @brief Getter de l'attribut radius_
         * 
         * @return L'attribut radius_ de la classe
        */
        float get_radius() const {return radius_ ;} ;

        /**
         * @brief Setter de l'attribut origin_
         * 
         * @param origin : l'origine que l'on veut donner à la sphère
        */
        void set_origin(Vector3f origin){ origin_ = origin ;} ;
        /**
         * @brief Setter de l'attribut radius_
         * 
         * @param radius : le rayon que l'on veut donner à la sphère
        */
        void set_radius(float radius){ radius_ = radius ;} ;

        /**
         * @brief Vérifie si le rayon intersecte la sphère
         * 
         * La fonction permet aussi de récupérer le point P d'intersection du rayon, la normale N
         * à ce point et la valeur de t à ce point.
         * Une fonction du même nom existe aussi pour les Quad
         * @see Quad
         * 
         * @param ray : le rayon avec lequel on veut voir s'il y a intersection
         * @param P : pointeur vers le point d'intersection entre le rayon et la sphère
         * @param N : pointeur vers la normale associé au point P
         * @param t : pointeur vers la valeur de t au point P
         * @see Vector3f, Ray3f
         * 
         * @return 1 s'il y a intersection, 0 sinon
        */
        int is_hit (Ray3f ray,Vector3f * P, Vector3f * N, float * t) ;
} ;

/**
 * @brief L'opérateur << pour afficher les informations de le sphère
 * 
 * Affiche les informations du Quad donné sous le format suivant : 
 * Quad : [origin : origin_, radius : radius_]
 * 
 * @param st : le flux sur lequel on veut afficher la sphère
 * @param c : référence de la sphère dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream & operator << (std::ostream & st, const Sphere & c) ;

#endif