#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3f.h"
#include <cmath>
#include <ostream>

/**
 * @brief La classe Camera permet de représenter la caméra de la scène
 * 
 * Cette classe permet d'avoir un point de départ sur lequel se porter lors du calcul des rayons.
 * Elle représente le spectateur de la scène.
*/

class Camera {
    private :
        /**
         * @brief Position de la caméra dans le plan
         * @see Vector3f
        */
        Vector3f position_ ;
        /**
         * @brief Direction vers laquelle la caméra pointe
         * @see Vector3f
        */
        Vector3f direction_ ;
    public :
        /**
         * @brief Constructeur par défaut
         * 
         * Crée une instance de la classe Camera avec position_ et direction_ les vecteurs par défaut
         * @see Vector3f
        */
        Camera() ;

        /**
         * @brief Constructeur paramétré
         * 
         * Crée une instance de la classe Camera à partir des paramètres donnés
         * 
         * @param position : la position voulue  de la caméra
         * @param direction : la direction voulue de la caméra
         * 
         * @see Vector3f
        */
        Camera (Vector3f position, Vector3f direction);

        /**
         * @brief Getter de l'attribut position_
         * 
         * @return L'attribut position_ de la classe
        */
        Vector3f get_position() const {return position_ ;} ;
        /**
         * @brief Getter de l'attribut direction_
         * 
         * @return L'attribut direction_ de la classe
        */
        Vector3f get_direction() const {return direction_ ;} ;

        /**
         * @brief Setter de l'attribut position_
         * 
         * @param position : la position que l'on veut donner à la caméra
        */
        void set_position(Vector3f position){ position_ = position ;} ;
        /**
         * @brief Setter de l'attribut direction_
         * 
         * @param direction : la direction que l'on veut donner à la caméra
        */
        void set_direction(Vector3f direction){ direction_ = direction ;} ;

} ;

/**
 * @brief L'opérateur << pour afficher les informations de la caméra
 * 
 * Affiche les informations de la caméra donnée sous le format suivant : 
 * Position : position_, direction : direction_
 * 
 * @param st : le flux sur lequel on veut afficher la caméra
 * @param c : référence de la caméra dont on veut afficher les informations
 * 
 * @return la référence vers le flux modifié
*/
std::ostream & operator << (std::ostream & st, const Camera & c) ;


#endif