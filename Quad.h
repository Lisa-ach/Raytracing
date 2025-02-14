#ifndef QUAD_H
#define QUAD_H

#include "Shape.h"
#include "Vector3f.h"
#include "Material.h"
#include "Ray3f.h"
#include <cmath>
#include "Sdl.h"
#include <ostream>
#include <iostream>


/**
 * @brief La classe qui définit les Quad dans la scène
 * 
 * Elle hérite de la classe @see Shape et définit les formes rectangulaires dans la scène
*/
class Quad : public Shape {
    private :
        /**
         * @brief L'origine du Quad
         * 
         * On définit l'origine du quad comme le point au coin avant supérieur gauche
         * 
         * @see Vector3f
        */
        Vector3f origin_ ;
        /**
         * @brief La largeur du Quad
         * 
         * C'est la valeur de l'élément x de width_ qui définit la valeur de la largeur, les autres
         * éléments étant à 0. On considére la largeur comme étant égale à la profondeur du Quad
         * 
         * @see Vector3f
        */
        Vector3f width_ ;
        /**
         * @brief La hauteur du Quad
         * 
         * C'est la valeur de l'élément y de height_ qui définit la valeur de la hauteur, les autres
         * éléments étant à 0
         * 
         * @see Vector3f
        */
        Vector3f height_ ;
    public :

        /**
         * @brief Constructeur par défaut
         * 
         * Crée une instance de la classe Quad avec origin_, width_ et height_ les vecteurs par défaut de
         * @see Vector3f
        */
        Quad() ; 
        /**
         * @brief Constructeur paramétré en prenant compte des attributs de la classe mère
         * 
         * Crée une instance de la classe Quad en définissant les paramètres de la classe fille ainsi 
         * que ceux de la classe mère Shape
         * 
         * @param matter : le matériel de la classe mère Shape
         * @param origin : l'origine du Quad
         * @param width : la largeur du Quad
         * @param height : la hauteur du Quad
         * @param miroir : le booléen qui permet de déterminer si Shape est miroir ou non, par défaut
         * il est mis à false
         * 
         * @see Shape
        */
        Quad (Material matter, Vector3f origin, Vector3f width, Vector3f height, bool miroir=false);
        /**
         * @brief Constructeur paramétré avec un Shape en entrée
         * 
         * Crée une instance de la classe Quad en définissant les paramètres de la classe fille et en 
         * prenant la référence vers un Shape déjà instancié
         * 
         * @param s : référence vers un Shape
         * @param origin : l'origine du Quad
         * @param width : la largeur du Quad
         * @param height : la hauteur du Quad
         * 
         * @see Shape
        */
        Quad (const Shape &s, Vector3f origin, Vector3f width, Vector3f height);
        /**
         * @brief Constructeur de copie
         * 
         * Crée une instance de Quad en copiant les attributs du Quad donné un entrée
         * 
         * @param q : une référence vers le Quad dont on veut faire la copie
         */
        Quad (const Quad &q);

        /**
         * @brief Getter de l'attribut origin_
         * 
         * @return L'attribut origin_ de la classe
        */
        Vector3f get_origin() const {return origin_ ;} ;
        /**
         * @brief Getter de l'attribut width_
         * 
         * @return L'attribut width_ de la classe
        */
        Vector3f get_width() const {return width_ ;} ;
        /**
         * @brief Getter de l'attribut height_
         * 
         * @return L'attribut height_ de la classe
        */
        Vector3f get_height() const {return height_ ;} ;

        /**
         * @brief Setter de l'attribut origin_
         * 
         * @param origin : l'origine que l'on veut donner au Quad
        */
        void set_origin(Vector3f origin){ origin_ = origin ;} ;
        /**
         * @brief Setter de l'attribut width_
         * 
         * @param width : la largeur que l'on veut donner au Quad
        */
        void set_width(Vector3f width){ width_ = width ;} ;
        /**
         * @brief Setter de l'attribut height_
         * 
         * @param height : la hauteur que l'on veut donner au Quad
        */
        void set_height(Vector3f height){ height_ = height ;} ;
        
        /**
         * @brief Donne la limite minimale des bordures du Quad
         * 
         * On définit la limite minimale comme l'origine du Quad
         * 
         * @return Le vecteur correspondant au point de la limite minimale
         * @see Vector3f
        */
        Vector3f boundMin() const;
        /**
         * @brief Donne la limite maximale des bordures du Quad
         * 
         * On définit la limite maximale comme le point à l'inverse de l'origine dans le Quad,
         * soit le point au coin arrière inférieur droit
         * 
         * @return Le vecteur correspondant au point de la limite maximale
         * @see Vector3f
        */
        Vector3f boundMax() const;

        /**
         * @brief Vérifie si le rayon intersecte le Quad
         * 
         * La fonction permet aussi de récupérer le point P d'intersection du rayon, la normale N
         * à ce point et la valeur de t à ce point.
         * Une fonction du même nom existe aussi pour les sphères
         * @see Sphere
         * 
         * @param ray : le rayon avec lequel on veut voir s'il y a intersection
         * @param P : pointeur vers le point d'intersection entre le rayon et le Quad
         * @param N : pointeur vers la normale associé au point P
         * @param t : pointeur vers la valeur de t au point P
         * @see Vector3f, Ray3f
         * 
         * @return 1 s'il y a intersection, 0 sinon
        */
        int is_hit (Ray3f ray, Vector3f * P, Vector3f * N, float * t) ;

        /**
         * @brief Donne le centre du Quad
         * 
         * On définit le centre d'un Quad comme son centre gravitationnel
         * 
         * @return le vecteur du point correspondant au centre du Quad
         * @see Vector3f
        */
        Vector3f get_center() const;

        /**
         * @brief Donne la normale au point donné en entrée
         * 
         * La normale pour un Quad étant plus compliqué à trouver que pour une sphère, puisqu'elle implique
         * de nombreuses comparaison, on fait une fonction qui fait toutes ces comparaisons, plutôt que 
         * de surcharger la fonction is_hit
         * 
         * @param P : le point P dont on cherche la normale
         * 
         * @return le vecteur correspondant à la normale du point P
         * @see Vector3f
        */
        Vector3f normal(const Vector3f P) const;

} ;

/**
 * @brief L'opérateur << pour afficher les informations du Quad
 * 
 * Affiche les informations du Quad donné sous le format suivant : 
 * Quad : [origin : origin_, width : width_, height : height_]
 * 
 * @param st : le flux sur lequel on veut afficher le Quad
 * @param c : référence du Quad dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream & operator << (std::ostream & st, const Quad & c) ;

#endif